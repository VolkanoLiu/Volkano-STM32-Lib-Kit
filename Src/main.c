/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "OLED.h"
#include "matrix_key.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// 定义前台任务队列
taskList_Typedef foregroundTaskList;
taskList_Typedef backgroundTaskList;

// FSMKey_Typedef key[4][4];

// static void (*SingleHit_callback[4][4])(void);
// static void (*DoubleHit_callback[4][4])(void);

memSyncTask_Typedef memSyncTask;

void send()
{
  sync_mem_TX(&memSyncTask);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  // FSMKey_Typedef key[4][4];

  // GPIO_struct_Typedef row[4];
  // GPIO_struct_Typedef col[4];

  
  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_USART1_Init();
  MX_GPIO_Init();
  MX_TIM6_Init();
  
  /* USER CODE BEGIN 2 */
  // uint8_t a = 0;
  // HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
  // a = HAL_GPIO_ReadPin(COL0_GPIO_Port, COL0_Pin);
  // HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
  taskListInit(&htim6, &foregroundTaskList, foregroundTaskManager);
  taskListInit(&htim6, &backgroundTaskList, backgroundTaskManager);
  memSyncTaskInit(&memSyncTask, SPI, TX, get_GRAMaddr(), 1024, 20);
  memSync_set_SPI_Handle(&hspi1);

  #ifdef OLED_USE_DMA
  // SetSPIHandle(&hspi1);
  // Set_DC_GPIO(OLED_DC_GPIO_Port, OLED_DC_Pin);
  // Set_RS_GPIO(OLED_RST_GPIO_Port, OLED_RST_Pin);
  // SH1106_Init();

  // firstTest(SingleHit_callback, DoubleHit_callback, row, col);
  // matrixInit(&matrix_key, key, SingleHit_callback, DoubleHit_callback, row, col);
  
  // taskElement_Typedef flushScreen_Task;
  // taskElement_Typedef scanMatrix_Task;
  taskElement_Typedef send_Task;
  backgroundTaskInit(&send_Task, &backgroundTaskList, 10, send);
  // backgroundTaskInit(&flushScreen_Task, &backgroundTaskList, 10, flushScreen);
  
  // foregroundTaskInit(&scanMatrix_Task, &foregroundTaskList, 10, scanMatrix);
  // HAL_TIM_Base_Stop_IT(&htim6);
  HAL_TIM_Base_Start_IT(&htim6);
  drawString("SPI RX Test", 0);
  // SPI mem sync Init;
  
  
  #endif
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    backgroundTaskManager(&backgroundTaskList);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

// callback functions

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM6) {
    foregroundTaskManager(&foregroundTaskList);
  }
}

uint8_t buffer;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == SPI2_CS1_Pin) {
    if (HAL_GPIO_ReadPin(SPI2_CS1_GPIO_Port, SPI2_CS1_Pin) == 0) {
      sync_mem_RX(&memSyncTask);
    } else {
      HAL_SPI_DMAStop(&hspi2);
    }
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
  }
}

// 测试外部中断和SPI接收的回调函数
// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {
//   if (GPIO_Pin == SPI2_CS1_Pin) {
//     if (HAL_GPIO_ReadPin(SPI2_CS1_GPIO_Port, SPI2_CS1_Pin) == 0) {
//       HAL_SPI_Receive_DMA(&hspi2, &buffer, 1);
//       clearScreen();
//       setCharCursor(0, 0);
//       drawString_up(" Volkano's SPI test: ", 1);
//       setCharCursor(0, 1);
//       drawString("RX:", 0);
//       print_uint8_t(&buffer);
//       setCharCursor(0, 2);
//       drawString("DMA status:", 0);
//       switch (hspi2.hdmatx->State) {
//       case HAL_DMA_STATE_RESET:
//         drawString("RESET", 0);
//         break;

//       case HAL_DMA_STATE_READY:
//         drawString("READY", 0);
//         break;

//       case HAL_DMA_STATE_BUSY:
//         drawString("BUSY", 0);
//         break;

//       case HAL_DMA_STATE_TIMEOUT:
//         drawString("TIMEOUT", 0);
//         break;

//       case HAL_DMA_STATE_ERROR:
//         drawString("ERROR", 0);
//         break;

//       case HAL_DMA_STATE_ABORT:
//         drawString("ABORT", 0);
//         break;

//       default:
//         break;
//       }
//       // HAL_SPI_Receive_IT(&hspi2, &buffer, 1);
//     } else {
//       HAL_SPI_DMAStop(&hspi2);
//     }
//     __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
//   }
// }

void HAL_SPI_RxCpltCallback (SPI_HandleTypeDef * hspi)
{
  // if(hspi == &hspi2) {
  //     HAL_SPI_Receive_IT(&hspi2, &buffer, 1);
  // }
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
