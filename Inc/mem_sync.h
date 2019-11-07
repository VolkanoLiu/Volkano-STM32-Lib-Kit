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

typedef enum {
  FREE = 0,
  TX_READY,
  RX_READY,
  TX_START,
  TX_BUSY,
  RX_BUSY,
  TX_FINISH,
  RX_FINISH
} transfState_Typedef;

typedef struct {
  protocol_Typedef protocol;
  direction_Typedef direction;
  uint32_t mem_addr;
  uint32_t data_length;
  uint32_t sync_period;
  transfState_Typedef transfState;
} memSyncTask_Typedef;

void memSyncTaskInit(memSyncTask_Typedef *memSyncTask,
    protocol_Typedef protocol,
    direction_Typedef direction,
    uint32_t mem_addr,
    uint32_t data_length,
    uint32_t sync_period);

// TX functions
static uint8_t ready_to_send_signal[2] = {0b11001100, 0b11110011};
void sync_mem_TX(memSyncTask_Typedef *memSyncTask);

// RX functions

void sync_mem_RX(memSyncTask_Typedef *memSyncTask);

// void send_data(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size);

SPI_HandleTypeDef *m_hspi_addr;

void set_SPI_Handle(SPI_HandleTypeDef *_addr);

#endif