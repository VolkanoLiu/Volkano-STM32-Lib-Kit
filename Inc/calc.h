#ifndef __CALC_H
#define __CALC_H

#include "stm32f4xx_hal.h"
#include "stdio.h"
#include "stdlib.h"

#define ARM_MATH_CM4
#include "arm_math.h"

uint8_t calc_finished_flag;
void set_calc_finished_flag();
void reset_calc_finished_flag();
uint8_t get_calc_finished_flag();

// 数据的类型：数字还是运算符
typedef enum {
  NUM= 0,
  FLOAT64,
  OP
} DATA_TYPE;

// 运算符定义

#define OP_NOT_A_OP 0x00
#define OP_LEFT     0x01
#define OP_RIGHT    0x02
#define OP_MINUS    0x03
#define OP_PLUS     0x04
#define OP_DIVIDE   0x05
#define OP_TIMES    0x06

// 数据和数据类型结构体定义
typedef struct {
  int32_t data_integer;
  float64_t data_double;
  DATA_TYPE type;
} data_datatype_Typedef;

// 数据栈和输出列表
typedef struct {
  data_datatype_Typedef mem_stack[256];
  uint8_t stack_tail;
  data_datatype_Typedef mem_list[256];
  uint8_t list_tail;
} calc_Typedef;

void calc_Typedef_Init(calc_Typedef *calc);

uint8_t isStackEmpty(calc_Typedef *calc);
uint8_t isStackFull(calc_Typedef *calc);
void stack_push(calc_Typedef *calc, int32_t data_integer, DATA_TYPE type);
data_datatype_Typedef stack_pop(calc_Typedef *calc);

uint8_t isListEmpty(calc_Typedef *calc);
uint8_t isListFull(calc_Typedef *calc);
void list_add_integer(calc_Typedef *calc, int32_t data_integer, DATA_TYPE type);
void list_add_double(calc_Typedef *calc, float64_t data_double);
void list_del(calc_Typedef *calc);

uint32_t isOperator(char *p_c);
uint32_t isNum(char *p_c);

void calc(char *string);

#endif