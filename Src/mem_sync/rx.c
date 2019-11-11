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
  mS_RX_task->state = FREE;
}

void memSync_RX_update(memSync_RX_taskTypedef *mS_RX_task)
{
  // todo
  mS_RX_task->DC_buffer = (mS_RX_task->DC_buffer << 1) | HAL_GPIO_ReadPin(mS_RX_task->GPIOx, mS_RX_task->GPIO_Pin);
  // todo
}