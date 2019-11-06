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
    HAL_SPI_Transmit_DMA(m_hspi_addr, ready_to_send_signal, 1);
    memSyncTask->transfState = TX_READY;
    break;
  
  case TX_READY:
    HAL_SPI_Transmit_DMA(m_hspi_addr, ready_to_send_signal + 1, 1);
    memSyncTask->transfState = TX_START;
    break;

  case TX_START:
    HAL_SPI_Transmit_DMA(m_hspi_addr, memSyncTask->mem_addr, memSyncTask->data_length);
    break;

  case TX_BUSY:
    // do nothing
    break;

  case TX_FINISH:
    memSyncTask->transfState = FREE;
    break;

  default:
    break;
  }
}

