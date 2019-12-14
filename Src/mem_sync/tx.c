#include "mem_sync/tx.h"

void memSync_TX_taskTypedef_Init(memSync_TX_taskTypedef* mS_TX_task,
    SPI_HandleTypeDef* p_hspi,
    uint8_t* dataAddress,
    uint32_t size)
{
  mS_TX_task->p_hspi = p_hspi;
  mS_TX_task->dataAddress = dataAddress;
  mS_TX_task->size = size;
  mS_TX_task->state = TX_FREE;
  mS_TX_task->count = 0;
} 

void memSync_TX_update(memSync_TX_taskTypedef* mS_TX_task)
{
  switch (mS_TX_task->state) {
  case TX_FREE:
    HAL_SPI_Transmit(mS_TX_task->p_hspi, tx_signal, 1, 100);
    mS_TX_task->state = TX_READY;
    break;

  case TX_READY:
    HAL_SPI_Transmit(mS_TX_task->p_hspi, tx_signal + 1, 1, 100);
    mS_TX_task->state = TX_START;
    break;

  case TX_START:
    HAL_SPI_Transmit_DMA(mS_TX_task->p_hspi, mS_TX_task->dataAddress, mS_TX_task->size);
    mS_TX_task->state = TX_BUSY;
    break;

  case TX_BUSY:
    if(mS_TX_task->p_hspi->Instance->SR & SPI_SR_TXE)
    {
      mS_TX_task->state = TX_FREE;
    }
    break;

  default:
    break;
  }
  mS_TX_task->count++;
}