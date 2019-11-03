#include "matrix_key.h"
#include "main.h"

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
    keyScanAll((matrix_key.keyGroup_row) + row);
  }
}