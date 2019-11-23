#include "matrix_key.h"
#include "main.h"
#include "usart.h"
#include "calc.h"

/**
  * @brief 初始化矩阵键盘
  * @param matrix 按键矩阵结构体
  * @param key 按键二维数组，用于存放按键的相关参数
  * @param SingleHit_callback 单击事件回调函数数组
  * @param DoubleHit_callback 双击事件回调函数数组
  * @param row GPIO的行（引脚为输出）
  * @param col GPIO的列（引脚为输入）
  */
void matrixInit(matrix_key_Typedef *matrix,
    FSMKey_Typedef key[MATRIX_ROW][MATRIX_COL],
    void (*SingleHit_callback[MATRIX_ROW][MATRIX_COL])(void),
    void (*DoubleHit_callback[MATRIX_ROW][MATRIX_COL])(void),
    GPIO_struct_Typedef *row,
    GPIO_struct_Typedef *col)
{
  for(uint8_t row_num = 0; row_num < MATRIX_ROW; row_num++) {
    keyGroupInit(matrix->keyGroup_row + row_num);
    for(uint8_t col_num = 0; col_num < MATRIX_COL; col_num++) {
      keyInit(matrix->keyGroup_row + row_num,
          &key[row_num][col_num],
          (col + col_num)->GPIOx,
          (col + col_num)->GPIO_Pin,
          SingleHit_callback[row_num][col_num],
          DoubleHit_callback[row_num][col_num],
          0);
    }
  }
}

void scanMatrix()
{
  for(uint32_t row = 0; row < MATRIX_ROW; row++)
  {
    switch (row)
    {
    case 0:
      HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
      break;
    
    case 1:
      HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
      break;

    case 2:
      HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
      break;

    case 3:
      HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
      break;
    
    default:
      break;
    }
    keyScanAll((matrix_key.keyGroup_row) + row);
    HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
  }
}

// 以下函数仅用于测试按键与屏幕
void addChar(char c)
{
  if(string_tail < 126){
    str[string_tail] = c;
    str[string_tail + 1] = '\0';
    string_tail++;
  }
}
void delChar()
{
  if(string_tail>0){
    str[string_tail - 1] = '\0';
    string_tail--;
  }
}

void print_1(){
  addChar('1');
  set_clearScreen_flag();
}
void print_2(){
  addChar('2');
  set_clearScreen_flag();
}
void print_3(){
  addChar('3');
  set_clearScreen_flag();
}
void print_4(){
  addChar('4');
  set_clearScreen_flag();
}
void print_5(){
  addChar('5');
  set_clearScreen_flag();
}
void print_6(){
  addChar('6');
  set_clearScreen_flag();
}
void print_7(){
  addChar('7');
  set_clearScreen_flag();
}
void print_8(){
  addChar('8');
  set_clearScreen_flag();
}
void print_9(){
  addChar('9');
  set_clearScreen_flag();
}
void print_0(){
  addChar('0');
  set_clearScreen_flag();
}
void print_plus(){
  if (str[string_tail - 1] != '?') {
    addChar('+');
  } else {
    str[string_tail - 1] = '(';
  }
  set_clearScreen_flag();
}
void print_minus(){
  if (str[string_tail - 1] != '?') {
    addChar('-');
  } else {
    str[string_tail - 1] = ')';
  }
  set_clearScreen_flag();
}
void print_times(){
  if (str[string_tail - 1] != '?') {
    addChar('*');
  } else {
    str[string_tail - 1] = '.';
  }
  set_clearScreen_flag();
}
void print_divide(){
  addChar('/');
  set_clearScreen_flag();
}
void equal()
{
  if (get_calc_finished_flag()) {
    *getStr() = '\0';
    string_tail = 0;
    set_clearScreen_flag();
    reset_calc_finished_flag();
  } else {
    calc(&str);
    set_clearScreen_flag();
  }
}
void print_shift(){
  if (str[string_tail - 1] != '?') {
    addChar('?');
  } else {
    if(string_tail > 1) {
      str[string_tail - 2] = '\0';
      string_tail = string_tail - 2;
    }
  }
  set_clearScreen_flag();
}

void firstTest(void (*SingleHit_callback[4][4])(void),
    void (*DoubleHit_callback[4][4])(void),
    GPIO_struct_Typedef row[4],
    GPIO_struct_Typedef col[4])
{
  SingleHit_callback[0][0]=print_1;
  SingleHit_callback[0][1]=print_2;
  SingleHit_callback[0][2]=print_3;
  SingleHit_callback[0][3]=print_plus;
  SingleHit_callback[1][0]=print_4;
  SingleHit_callback[1][1]=print_5;
  SingleHit_callback[1][2]=print_6;
  SingleHit_callback[1][3]=print_minus;
  SingleHit_callback[2][0]=print_7;
  SingleHit_callback[2][1]=print_8;
  SingleHit_callback[2][2]=print_9;
  SingleHit_callback[2][3]=print_times;
  SingleHit_callback[3][0]=equal;
  SingleHit_callback[3][1]=print_0;
  SingleHit_callback[3][2]=print_shift;
  SingleHit_callback[3][3]=print_divide;
  row[0].GPIOx=ROW0_GPIO_Port;row[0].GPIO_Pin=ROW0_Pin;
  row[1].GPIOx=ROW1_GPIO_Port;row[1].GPIO_Pin=ROW1_Pin;
  row[2].GPIOx=ROW2_GPIO_Port;row[2].GPIO_Pin=ROW2_Pin;
  row[3].GPIOx=ROW3_GPIO_Port;row[3].GPIO_Pin=ROW3_Pin;
  col[0].GPIOx=COL0_GPIO_Port;col[0].GPIO_Pin=COL0_Pin;
  col[1].GPIOx=COL1_GPIO_Port;col[1].GPIO_Pin=COL1_Pin;
  col[2].GPIOx=COL2_GPIO_Port;col[2].GPIO_Pin=COL2_Pin;
  col[3].GPIOx=COL3_GPIO_Port;col[3].GPIO_Pin=COL3_Pin;
}

char* getStr()
{
  return str;
}