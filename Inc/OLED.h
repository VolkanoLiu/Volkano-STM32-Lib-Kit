/*
 * Reference: https://github.com/Tamakichi/Adafruit_SH1106_STM32/blob/master/Adafruit_SH1106_STM32.cpp
 */
#ifndef __OLED_H
#define __OLED_H
#endif

#include "stm32f4xx_hal.h"

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
void test();

// TODO functions
void drawPixel(uint8_t x, uint8_t y);
void printChar(uint8_t x, uint8_t y, char c);
void printString_8x6(char* string, uint8_t string_length);

//SH1106 functions END

//SH1106 parameters BEGIN
SPI_HandleTypeDef *hspi_addr;
GPIO_TypeDef *DC_GPIO, *RS_GPIO;
uint16_t *DC_GPIO_Pin, *RS_GPIO_Pin;
//SH1106 parameters END