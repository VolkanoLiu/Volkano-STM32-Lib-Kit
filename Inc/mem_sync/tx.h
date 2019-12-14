#ifndef __MEM_SYNC_TX_H
#define __MEM_SYNC_TX_H

#include "stm32f4xx_hal.h"
#include "taskmanage.h"

static uint8_t tx_signal[2] = {0b01100110, 0b01010100};

typedef enum {
  TX_FREE = 0,
  TX_READY,
  TX_START,
  TX_BUSY,
} TX_stateTypedef;

typedef struct {
  // SPI handle
  SPI_HandleTypeDef* p_hspi;
  uint8_t* dataAddress;
  uint32_t size;
  TX_stateTypedef state;
  //  当前计数
  uint8_t count;
} memSync_TX_taskTypedef;

void memSync_TX_taskTypedef_Init(memSync_TX_taskTypedef* memSync_TX_task,
    SPI_HandleTypeDef* p_hspi,
    uint8_t* dataAddress,
    uint32_t size);

void memSync_TX_update(memSync_TX_taskTypedef* memSync_TX_task);

#endif