#ifndef __DRV8825_H
#define __DRV8825_H

#include "stm32f4xx_hal.h"

typedef struct {
  GPIO_TypeDef *GPIOx; 
  uint16_t GPIO_Pin;
} DRV8825_GPIO_Typedef;

#define GPIO DRV8825_GPIO_Typedef

typedef struct {
  GPIO STEP;
  GPIO NRE;
  GPIO NSLE;
  GPIO NEN;
  TIM_HandleTypeDef* htim;
  uint16_t dutyCycle;
} DRV8825_Controller_Typedef;

void DRV8825_ControllerInit(DRV8825_Controller_Typedef *DRV8825_Controller,
                            GPIO_TypeDef *STEP_GPIOx, uint16_t STEP_GPIO_Pin,
                            GPIO_TypeDef *NRE_GPIOx, uint16_t NRE_GPIO_Pin,
                            GPIO_TypeDef *NSLE_GPIOx, uint16_t NSLE_GPIO_Pin,
                            GPIO_TypeDef *NEN_GPIOx, uint16_t NEN_GPIO_Pin,
                            TIM_HandleTypeDef *htim,
                            uint16_t dutyCycle);
void DRV8825_EnableStepper(DRV8825_Controller_Typedef *DRV8825_Controller);
void DRV8825_DisableStepper(DRV8825_Controller_Typedef *DRV8825_Controller);
void DRV8825_SetDutyCycle(DRV8825_Controller_Typedef *DRV8825_Controller, uint16_t dutyCycle);

#undef GPIO
#endif