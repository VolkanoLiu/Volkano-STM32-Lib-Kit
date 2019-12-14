#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx_hal.h"
#include "ASCII.h"

#define OLED_USE_DMA

// SH1106 defines BEGIN
#define OLED_CMD 0
#define OLED_DATA 1

//SH1106 defines END

//SH1106 functions BEGIN

void SetSPIHandle(SPI_HandleTypeDef *hspi);
void Set_DC_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_RS_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void OLED_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint8_t cmd);
void SH1106_WR_Byte(uint8_t dat, uint8_t cmd);
void SH1106_Init();
void flushScreen();
void drawPixel(uint8_t x, uint8_t y, uint8_t color);
void drawChar(char* c, uint8_t reverse);
void setCharCursor(uint8_t x, uint8_t y);
void drawString(char *s, uint8_t reverse);
void clearScreen();
void set_clearScreen_flag();
void reset_clearScreen_flag();
uint8_t get_clearScreen_flag();

// experimental functions:
void drawChar_up(char* c, uint8_t reverse);
void drawString_up(char *s, uint8_t reverse);

uint8_t* get_GRAMaddr();

//SH1106 functions END

//SH1106 parameters BEGIN

static uint8_t GRAM[1024] = {};
static uint8_t clearScreen_flag  = 0;

SPI_HandleTypeDef *hspi_addr;
GPIO_TypeDef *DC_GPIO, *RS_GPIO;
uint16_t *DC_GPIO_Pin, *RS_GPIO_Pin;
typedef struct {
  uint8_t x;
  uint8_t y;
} pos_Typedef;

pos_Typedef char_pos;
pos_Typedef pixel_pos;

//SH1106 parameters END

// functions to be removed:
void draw_uint8_t(uint8_t *num);
void draw_uint16_t(uint16_t *num);

#endif /* __OLED_H */