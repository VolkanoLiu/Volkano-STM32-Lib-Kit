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

#endif