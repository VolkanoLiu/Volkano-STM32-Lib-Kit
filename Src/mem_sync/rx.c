#include "mem_sync/rx.h"

void memSync_RX_taskTypedef_Init(memSync_RX_taskTypedef* mS_RX_task,
    SPI_HandleTypeDef* p_hspi,
    GPIO_TypeDef *GPIOx,
    uint16_t GPIO_Pin,
    uint8_t* dataAddress,
    uint32_t size)
{
  mS_RX_task->p_hspi = p_hspi;
  mS_RX_task->GPIOx = GPIOx;
  mS_RX_task->GPIO_Pin = GPIO_Pin;
  mS_RX_task->dataAddress = dataAddress;
  mS_RX_task->size = size;
  mS_RX_task->RX_buffer = 0;
  mS_RX_task->DC_buffer = 0xFF;
  mS_RX_task->state = RX_FREE;
}

void memSync_RX_update(memSync_RX_taskTypedef *mS_RX_task)
{
  mS_RX_task->DC_buffer = (mS_RX_task->DC_buffer << 1) | HAL_GPIO_ReadPin(mS_RX_task->GPIOx, mS_RX_task->GPIO_Pin);
  if((mS_RX_task->DC_buffer & 0x0F) == 0b00001100) {
    switch (mS_RX_task->state) {
    case RX_FREE:
      HAL_SPI_Receive(mS_RX_task->p_hspi, &(mS_RX_task->RX_buffer), 1, 10);
      if(mS_RX_task->RX_buffer == rx_signal[0]) {
        mS_RX_task->state = RX_READY;
      }
      break;

    case RX_READY:
      HAL_SPI_Receive(mS_RX_task->p_hspi, &(mS_RX_task->RX_buffer), 1, 10);
      if(mS_RX_task->RX_buffer == rx_signal[1]) {
        mS_RX_task->state = RX_START;
      } else {
        mS_RX_task->state = RX_FREE;
      }
      break;

    case RX_START:
      HAL_SPI_Receive_DMA(mS_RX_task->p_hspi, mS_RX_task->dataAddress, mS_RX_task->size);
      mS_RX_task->state = RX_BUSY;
      break;

    case RX_BUSY:
      if(!(mS_RX_task->p_hspi->Instance->SR & SPI_SR_RXNE)) {
        mS_RX_task->state = RX_FREE;
      }
      break;

    default:
      break;
    }
  }
}