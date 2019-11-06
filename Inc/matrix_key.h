#ifndef __MATRIX_KEY_H
#define __MATRIX_KEY_H

#include "stm32f4xx_hal.h"
#include "keypress_process.h"
#include "OLED.h"

// 定义矩阵键盘的行和列
#define MATRIX_ROW 4
#define MATRIX_COL 4

// GPIO引脚结构体定义
typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} GPIO_struct_Typedef;

// 矩阵键盘结构提定义
typedef struct {
  KeyGroup_Typedef keyGroup_row[4];
} matrix_key_Typedef;

matrix_key_Typedef matrix_key;

// 初始化矩阵键盘
void matrixInit(matrix_key_Typedef *matrix,
    FSMKey_Typedef key[MATRIX_ROW][MATRIX_COL],
    void (*SingleHit_callback[MATRIX_ROW][MATRIX_COL])(void),
    void (*DoubleHit_callback[MATRIX_ROW][MATRIX_COL])(void),
    GPIO_struct_Typedef row[MATRIX_ROW],
    GPIO_struct_Typedef col[MATRIX_COL]);

// 扫描矩阵键盘
void scanMatrix();

// 以下函数仅用于测试按键与屏幕
static char str[127];
static uint8_t string_tail;
void firstTest(void (*SingleHit_callback[4][4])(void), void (*DoubleHit_callback[4][4])(void), GPIO_struct_Typedef row[4], GPIO_struct_Typedef col[4]);
char* getStr();

#endif