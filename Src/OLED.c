#include "OLED.h"

#ifndef OLED_USE_DMA

// 通过SPI发送指令
void SH1106_SPI_trans(SPI_HandleTypeDef *hspi, uint8_t data)
{
  HAL_SPI_Transmit(hspi, data, 1, 10);
}

// 设置SPI句柄
void SetSPIHandle(SPI_HandleTypeDef *hspi)
{
  hspi_addr = hspi;
}

// 设置数据/控制GPIO
void Set_DC_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  DC_GPIO = GPIOx;
  DC_GPIO_Pin = GPIO_Pin;
}

// 设置Reset GPIO
void Set_RS_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  RS_GPIO = GPIOx;
  RS_GPIO_Pin = GPIO_Pin;
}

// 向12864显示屏写入字节
void SH1106_WR_Byte(uint8_t dat, uint8_t cmd)
{
  HAL_GPIO_WritePin(DC_GPIO, DC_GPIO_Pin, cmd);
  HAL_SPI_Transmit(hspi_addr, &dat, 1, 10);
}

// 初始化显示屏
void SH1106_Init()
{
  HAL_GPIO_WritePin(RS_GPIO, RS_GPIO_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(RS_GPIO, RS_GPIO_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  SH1106_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
  SH1106_WR_Byte(0x02, OLED_CMD); //---set low column address
  SH1106_WR_Byte(0x10, OLED_CMD); //---set high column address
  SH1106_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  SH1106_WR_Byte(0x81, OLED_CMD); //--set contrast control register
  SH1106_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
  SH1106_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  SH1106_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  SH1106_WR_Byte(0xA6, OLED_CMD); //--set normal display
  SH1106_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
  SH1106_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
  SH1106_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  SH1106_WR_Byte(0x00, OLED_CMD); //-not offset
  SH1106_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
  SH1106_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
  SH1106_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
  SH1106_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  SH1106_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
  SH1106_WR_Byte(0x12, OLED_CMD);
  SH1106_WR_Byte(0xDB, OLED_CMD); //--set vcomh
  SH1106_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
  SH1106_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
  SH1106_WR_Byte(0x02, OLED_CMD); //
  SH1106_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
  SH1106_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
  SH1106_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
  SH1106_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
  SH1106_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
}

//
void SH1106_Set_Pos(uint8_t x, uint8_t y)
{
  SH1106_WR_Byte(0xb0 + y, OLED_CMD);
  SH1106_WR_Byte(((x & 0xf0) >> 4) | 0x10, OLED_CMD);
  SH1106_WR_Byte((x & 0x0f) | 0x01, OLED_CMD);
}

void drawPixel(uint8_t x, uint8_t y)
{
  // todo
}

void setCursorPos_byte(uint8_t x, uint8_t y)
{
  SH1106_WR_Byte(0xb0 + y, OLED_CMD);                            //设置页地址（0~7）
  SH1106_WR_Byte((x + 0x02) & (0x0F), OLED_CMD);                 //设置列低4位地址
  SH1106_WR_Byte(0x10 | (((x + 0x02) & (0xF0)) >> 4), OLED_CMD); //设置列高4位地址
}

void setCursorPos_charMode(uint8_t x, uint8_t y)
{
  charCursor.x = x;
  charCursor.y = y;
  setCursorPos_byte(x * 6, y);
}

void draw8bit(uint8_t data)
{
  SH1106_WR_Byte(data, OLED_DATA);
}

void printChar_8x6_charMode(char c)
{
  for (uint8_t col = 0; col < 6; col++) {
    SH1106_WR_Byte(ascii_8x6[c - ' '][col], OLED_DATA);
  }
  if (charCursor.x == 20) {
    charCursor.x = 0;
    if (charCursor.y == 7) {
      charCursor.y = 0;
    } else {
      charCursor.y++;
    }
    setCursorPos_charMode(0, charCursor.y);
  } else {
    charCursor.x++;
  }
}

// 测试显示屏函数
void test()
{
  uint8_t i, n;
  for (i = 0; i < 8; i++) {
    SH1106_WR_Byte(0xb0 + i, OLED_CMD); //设置页地址（0~7）
    SH1106_WR_Byte(0x02, OLED_CMD);     //设置显示位置—列低地址
    SH1106_WR_Byte(0x10, OLED_CMD);     //设置显示位置—列高地址
    for (n = 0; n < 128; n++)
      SH1106_WR_Byte(0x00, OLED_DATA);
  } //更新显示
  setCursorPos_charMode(0, 0);
  for (int k = 0; k < 95; k++) {
    printChar_8x6_charMode(k + ' ');
  }
}

#else  /* OLED_USE_DMA */

#include "main.h"

void SetSPIHandle(SPI_HandleTypeDef *hspi)
{
  hspi_addr = hspi;
}

// 设置数据/控制GPIO
void Set_DC_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  DC_GPIO = GPIOx;
  DC_GPIO_Pin = GPIO_Pin;
}

// 设置Reset GPIO
void Set_RS_GPIO(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  RS_GPIO = GPIOx;
  RS_GPIO_Pin = GPIO_Pin;
}

void OLED_SPI_Transmit_DMA(SPI_HandleTypeDef *hspi, uint8_t *pData, uint16_t Size, uint8_t cmd)
{
  HAL_GPIO_WritePin(DC_GPIO, DC_GPIO_Pin, cmd);
  HAL_SPI_Transmit_DMA(hspi, pData, Size);
}

void SH1106_WR_Byte(uint8_t dat, uint8_t cmd)
{
  OLED_SPI_Transmit_DMA(hspi_addr, &dat, 1, cmd);
}

void SH1106_Init()
{
  HAL_GPIO_WritePin(RS_GPIO, RS_GPIO_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(RS_GPIO, RS_GPIO_Pin, GPIO_PIN_SET);
  HAL_Delay(100);

  SH1106_WR_Byte(0xAE, OLED_CMD); //--turn off oled panel
  SH1106_WR_Byte(0x02, OLED_CMD); //---set low column address
  SH1106_WR_Byte(0x10, OLED_CMD); //---set high column address
  SH1106_WR_Byte(0x40, OLED_CMD); //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
  SH1106_WR_Byte(0x81, OLED_CMD); //--set contrast control register
  SH1106_WR_Byte(0xCF, OLED_CMD); // Set SEG Output Current Brightness
  SH1106_WR_Byte(0xA1, OLED_CMD); //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
  SH1106_WR_Byte(0xC8, OLED_CMD); //Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
  SH1106_WR_Byte(0xA6, OLED_CMD); //--set normal display
  SH1106_WR_Byte(0xA8, OLED_CMD); //--set multiplex ratio(1 to 64)
  SH1106_WR_Byte(0x3f, OLED_CMD); //--1/64 duty
  SH1106_WR_Byte(0xD3, OLED_CMD); //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
  SH1106_WR_Byte(0x00, OLED_CMD); //-not offset
  SH1106_WR_Byte(0xd5, OLED_CMD); //--set display clock divide ratio/oscillator frequency
  SH1106_WR_Byte(0x80, OLED_CMD); //--set divide ratio, Set Clock as 100 Frames/Sec
  SH1106_WR_Byte(0xD9, OLED_CMD); //--set pre-charge period
  SH1106_WR_Byte(0xF1, OLED_CMD); //Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
  SH1106_WR_Byte(0xDA, OLED_CMD); //--set com pins hardware configuration
  SH1106_WR_Byte(0x12, OLED_CMD);
  SH1106_WR_Byte(0xDB, OLED_CMD); //--set vcomh
  SH1106_WR_Byte(0x40, OLED_CMD); //Set VCOM Deselect Level
  SH1106_WR_Byte(0x20, OLED_CMD); //-Set Page Addressing Mode (0x00/0x01/0x02)
  SH1106_WR_Byte(0x02, OLED_CMD); //
  SH1106_WR_Byte(0x8D, OLED_CMD); //--set Charge Pump enable/disable
  SH1106_WR_Byte(0x14, OLED_CMD); //--set(0x10) disable
  SH1106_WR_Byte(0xA4, OLED_CMD); // Disable Entire Display On (0xa4/0xa5)
  SH1106_WR_Byte(0xA6, OLED_CMD); // Disable Inverse Display On (0xa6/a7)
  SH1106_WR_Byte(0xAF, OLED_CMD); //--turn on oled panel
}

  static uint8_t FLUSH_PARTITION_CHOOSE = 0;
  static uint8_t CURRENT_PAGE = 0;
  static uint8_t ADDRESS[3];

void flushScreen()
{
  for (uint8_t page = 0; page < 8; page++) {
    SH1106_WR_Byte(0xb0 + page, OLED_CMD); //设置页地址（0~7）
    SH1106_WR_Byte(0x02, OLED_CMD);        //设置显示位置—列低地址
    SH1106_WR_Byte(0x10, OLED_CMD);        //设置显示位置—列高地址
    OLED_SPI_Transmit_DMA(hspi_addr, &GRAM[0 + 128 * page], 128, OLED_DATA);
    HAL_Delay(1);
  }
}

void drawChar(char c)
{
  for (uint8_t x = 0; x < 6; x++) {
    GRAM[128 * char_pos.y + 6 * char_pos.x + x] = ascii_8x6[c - ' '][x];
  }
  if (char_pos.x == 20) {
    char_pos.x = 0;
    char_pos.y = char_pos.y == 7 ? 0 : char_pos.y + 1;
  }
}

void drawString(char *s)
{
  char_pos.x = 0;
  char_pos.y = 0;
  char* current_char = s;
  while(&current_char!='\0')
  {
    drawChar(&current_char);
    current_char++;
  }
}

#endif /* OLED_USE_DMA */