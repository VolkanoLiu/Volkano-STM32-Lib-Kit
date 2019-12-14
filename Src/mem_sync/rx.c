#include "mem_sync/rx.h"

void memSync_RX_taskTypedef_Init(memSync_RX_taskTypedef* mS_RX_task,
    SPI_HandleTypeDef* p_hspi,
    uint8_t* dataAddress,
    uint32_t size)
{
  mS_RX_task->p_hspi = p_hspi;
  mS_RX_task->dataAddress = dataAddress;
  mS_RX_task->size = size;
  mS_RX_task->RX_buffer = 0;
  mS_RX_task->state = RX_FREE;
}

void memSync_RX_update(memSync_RX_taskTypedef *mS_RX_task)
{
 //
}