#ifndef __MATRIX_KEY_H
#define __MATRIX_KEY_H

#include "stm32f4xx_hal.h"
#include "keypress_process.h"
#include "OLED.h"

#define MATRIX_ROW 4
#define MATRIX_COL 4

typedef struct {
  GPIO_TypeDef *GPIOx;
  uint16_t GPIO_Pin;
} GPIO_struct_Typedef;

// FSMKey_Typedef one_key[4][4];

typedef struct {
  KeyGroup_Typedef keyGroup_row[4];
} matrix_key_Typedef;

matrix_key_Typedef matrix_key;

void matrixInit(matrix_key_Typedef *matrix,
    FSMKey_Typedef key[4][4],
    void (*SingleHit_callback[4][4])(void),
    void (*DoubleHit_callback[4][4])(void),
    GPIO_struct_Typedef row[4],
    GPIO_struct_Typedef col[4]);

void scanMatrix();

static char str[127];
static uint8_t string_tail;
void firstTest(void (*SingleHit_callback[4][4])(void), void (*DoubleHit_callback[4][4])(void), GPIO_struct_Typedef row[4], GPIO_struct_Typedef col[4]);
char* getStr();

#endif