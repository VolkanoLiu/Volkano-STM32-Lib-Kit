#include "matrix_key.h"
#include "main.h"
#include "usart.h"

void matrixInit(matrix_key_Typedef *matrix,
    FSMKey_Typedef key[4][4],
    void (*SingleHit_callback[4][4])(void),
    void (*DoubleHit_callback[4][4])(void),
    GPIO_struct_Typedef *row,
    GPIO_struct_Typedef *col)
{
  for(uint8_t row_num = 0; row_num < 4; row_num++) {
    keyGroupInit(matrix->keyGroup_row + row_num);
    for(uint8_t col_num = 0; col_num < 4; col_num++) {
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
  for(uint32_t row = 0; row < 4; row++)
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

void print1(){
  addChar('1');
}
void print2(){
  addChar('2');
}
void print3(){
  addChar('3');
}
void print4(){
  addChar('4');
}
void print5(){
  addChar('5');
}
void print6(){
  addChar('6');
}
void print7(){
  addChar('7');
}
void print8(){
  addChar('8');
}
void print9(){
  addChar('9');
}
void print0(){
  addChar('0');
}
void yes(){
  char LF[3] = "\r\n";
  HAL_USART_Transmit(&husart1, &LF, 3, 100);
  HAL_USART_Transmit(&husart1, str, string_tail, 100);
  set_clearScreen_flag();
}
void no(){
  delChar();
}

void firstTest(void (*SingleHit_callback[4][4])(void), void (*DoubleHit_callback[4][4])(void), GPIO_struct_Typedef row[4], GPIO_struct_Typedef col[4])
{
  SingleHit_callback[0][0]=print1;
  SingleHit_callback[0][1]=print2;
  SingleHit_callback[0][2]=print3;
  SingleHit_callback[1][0]=print4;
  SingleHit_callback[1][1]=print5;
  SingleHit_callback[1][2]=print6;
  SingleHit_callback[2][0]=print7;
  SingleHit_callback[2][1]=print8;
  SingleHit_callback[2][2]=print9;
  SingleHit_callback[3][0]=yes;
  SingleHit_callback[3][1]=print0;
  SingleHit_callback[3][2]=no;
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