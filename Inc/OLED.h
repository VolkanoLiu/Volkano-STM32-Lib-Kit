#ifndef __OLED_H
#define __OLED_H

#include "stm32f4xx_hal.h"
#include "ASCII.h"

#define OLED_USE_DMA

#ifndef OLED_USE_DMA
// SH1106 defines BEGIN
#define OLED_CMD 0
#define OLED_DATA 1
//SH1106 defines END

//SH1106 functions BEGIN
void SH1106_SPI_trans(SPI_HandleTypeDef *hspi, uint8_t data);
void SetSPIHandle(SPI_HandleTypeDef *hspi);
void Set_DC_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_RS_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void SH1106_WR_Byte(uint8_t dat, uint8_t cmd);
void SH1106_Init();
void SH1106_Set_Pos(uint8_t x, uint8_t y);
void drawPixel(uint8_t x, uint8_t y);
void setCursorPos_byte(uint8_t x, uint8_t y);
void setCursorPos_charMode(uint8_t x, uint8_t y);
void printChar_8x6_charMode(char c);
void draw8bit(uint8_t data);

void test();

// TODO functions

void printString_8x6_char(char *string, uint8_t string_length);

//SH1106 functions END

//SH1106 parameters BEGIN

SPI_HandleTypeDef *hspi_addr;
GPIO_TypeDef *DC_GPIO, *RS_GPIO;
uint16_t *DC_GPIO_Pin, *RS_GPIO_Pin;

typedef struct {
  uint8_t x;
  uint8_t y;
} cursorPos;

cursorPos byteCursor;
cursorPos charCursor; // Cursor position(x, y), x ranged from 0 to 20, y ranged from 0 to 7

//SH1106 parameters END

#else  /* OLED_USE_DMA */

// SH1106 defines BEGIN
#define OLED_CMD 0
#define OLED_DATA 1

static volatile uint8_t GRAM[1024] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 2, 3, 4, 5,};
//SH1106 defines END

//SH1106 functions BEGIN

void SetSPIHandle(SPI_HandleTypeDef *hspi);
void Set_DC_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_RS_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void OLED_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint8_t cmd);
void SH1106_WR_Byte(uint8_t dat, uint8_t cmd);
void SH1106_Init();
void flushScreen();
void drawPixel(uint8_t x, uint8_t y);

//SH1106 functions END

//SH1106 parameters BEGIN

SPI_HandleTypeDef *hspi_addr;
GPIO_TypeDef *DC_GPIO, *RS_GPIO;
uint16_t *DC_GPIO_Pin, *RS_GPIO_Pin;

//SH1106 parameters END

#endif /* OLED_USE_DMA */

#endif /* __OLED_H */