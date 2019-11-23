/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "taskmanage.h"
#include "OLED.h"
#include "keypress_process.h"
#include "matrix_key.h"
#include "calc.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define ROW0_Pin GPIO_PIN_1
#define ROW0_GPIO_Port GPIOF
#define ROW1_Pin GPIO_PIN_3
#define ROW1_GPIO_Port GPIOF
#define ROW3_Pin GPIO_PIN_4
#define ROW3_GPIO_Port GPIOF
#define ROW2_Pin GPIO_PIN_5
#define ROW2_GPIO_Port GPIOF
#define SPI2_CS1_Pin GPIO_PIN_13
#define SPI2_CS1_GPIO_Port GPIOF
#define OLED_DC_Pin GPIO_PIN_8
#define OLED_DC_GPIO_Port GPIOD
#define OLED_RST_Pin GPIO_PIN_9
#define OLED_RST_GPIO_Port GPIOD
#define COL0_Pin GPIO_PIN_2
#define COL0_GPIO_Port GPIOG
#define COL1_Pin GPIO_PIN_4
#define COL1_GPIO_Port GPIOG
#define COL2_Pin GPIO_PIN_6
#define COL2_GPIO_Port GPIOG
#define COL3_Pin GPIO_PIN_8
#define COL3_GPIO_Port GPIOG
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
