#include "mem_sync.h"
#include "main.h"

void memSyncTaskInit(memSyncTask_Typedef *memSyncTask,
    protocol_Typedef protocol,
    direction_Typedef direction,
    uint32_t mem_addr,
    uint32_t data_length,
    uint32_t sync_period)
{
  memSyncTask->protocol = protocol;
  HAL_GPIO_WritePin(memSyncTask->CS_GPIOx, memSyncTask->CS_GPIO_Pin, GPIO_PIN_SET);
  memSyncTask->direction = direction;
  memSyncTask->mem_addr = mem_addr;
  memSyncTask->data_length = data_length;
  memSyncTask->sync_period = sync_period;
  memSyncTask->transfState = FREE;
}

void sync_mem_TX(memSyncTask_Typedef *memSyncTask)
{
  switch (memSyncTask->transfState)
  {
  case FREE:
    SPI_Transmit_TX(m_hspi_addr, ready_to_send_signal, 1, memSyncTask);
    memSyncTask->transfState = TX_READY;
    break;
  
  case TX_READY:
    SPI_Transmit_TX(m_hspi_addr, ready_to_send_signal + 1, 1, memSyncTask);
    memSyncTask->transfState = TX_START;
    break;

  case TX_START:
    SPI_Transmit_TX(m_hspi_addr, memSyncTask->mem_addr, memSyncTask->data_length, memSyncTask);
    memSyncTask->transfState = TX_BUSY;
    break;

  case TX_BUSY:
    if(m_hspi_addr->hdmarx->State != HAL_DMA_STATE_BUSY) {
      memSyncTask->transfState = TX_FINISH;
    }
    break;

  case TX_FINISH:
    memSyncTask->transfState = FREE;
    break;

  default:
    break;
  }
}

void SPI_Transmit_TX(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, memSyncTask_Typedef *memSyncTask)
{
  HAL_GPIO_WritePin(memSyncTask->CS_GPIOx, memSyncTask->CS_GPIO_Pin, GPIO_PIN_RESET);
  HAL_SPI_Transmit_DMA(hspi, pData, Size);
  HAL_GPIO_WritePin(memSyncTask->CS_GPIOx, memSyncTask->CS_GPIO_Pin, GPIO_PIN_SET);
}

void sync_mem_RX(memSyncTask_Typedef *memSyncTask)
{
  uint8_t buffer;
  switch (memSyncTask->transfState) {
  case FREE:
    SPI_Transmit_RX(hspi_addr, &buffer, 1);
    if(buffer = ready_to_send_signal[0]) {
      memSyncTask->transfState = RX_READY;
    }
    break;

  case RX_READY:
    SPI_Transmit_RX(hspi_addr, &buffer, 1);
    if(buffer = ready_to_send_signal[1]) {
      memSyncTask->transfState = RX_START;
    } else {
      memSyncTask->transfState = FREE;
    }
    break;

  case RX_START:
    SPI_Transmit_RX(hspi_addr, memSyncTask->mem_addr, memSyncTask->data_length);
    memSyncTask->transfState = RX_BUSY;
    break;

  case RX_BUSY:
    if(m_hspi_addr->hdmarx->State != HAL_DMA_STATE_BUSY) {
      memSyncTask->transfState = RX_FINISH;
    }
    break;

  case RX_FINISH:
    memSyncTask->transfState = RX_FINISH;
    break;

  default:
    break;
  }
}

void SPI_Transmit_RX(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size)
{
  HAL_SPI_Transmit_DMA(hspi, pData, Size);
}

void memSync_set_SPI_Handle(SPI_HandleTypeDef *_addr)
{
  m_hspi_addr = _addr;
}
