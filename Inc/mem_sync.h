#ifndef __MEM_SYNC_H
#define __MEM_SYNC_H

/**
  * 简介：通过各种通讯协议同步两台单片机之间的内存
  * 
  * 作者：VolkanoLiu
  * 
  */

#include "stm32f4xx_hal.h"
#include "taskmanage.h"

typedef enum {
  SPI = 0,
  UART,
  CAN,
  I2C,
  USB_OTG
} protocol_Typedef;

typedef enum {
  TX=0,
  RX
} direction_Typedef;

typedef struct {
  protocol_Typedef protocol;
  direction_Typedef direction;
  uint32_t mem_addr;
  uint32_t data_length;
  uint32_t sync_period;
} memSyncTask_Typedef;

void memSyncTaskInit(memSyncTask_Typedef *memSyncTask,
    direction_Typedef direction,
    uint32_t mem_addr,
    uint32_t data_length,
    uint32_t sync_period);

#endif