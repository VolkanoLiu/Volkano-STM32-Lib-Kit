#include "DRV8825.h"

#define DRV8825_Controller DC

void DRV8825_ControllerInit(DRV8825_Controller_Typedef *DRV8825_Controller,
                            GPIO_TypeDef *STEP_GPIOx, uint16_t STEP_GPIO_Pin,
                            GPIO_TypeDef *NRE_GPIOx, uint16_t NRE_GPIO_Pin,
                            GPIO_TypeDef *NSLE_GPIOx, uint16_t NSLE_GPIO_Pin,
                            GPIO_TypeDef *NEN_GPIOx, uint16_t NEN_GPIO_Pin,
                            TIM_HandleTypeDef *htim,
                            uint16_t dutyCycle)
{
  HAL_GPIO_WritePin(NRE_GPIOx, NRE_GPIO_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(NSLE_GPIOx, NSLE_GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(NEN_GPIOx, NEN_GPIO_Pin, GPIO_PIN_SET);
  DC->STEP.GPIOx = STEP_GPIOx;
  DC->STEP.GPIO_Pin = STEP_GPIO_Pin;
  DC->NRE.GPIOx = NRE_GPIOx;
  DC->NRE.GPIO_Pin = NRE_GPIO_Pin;
  DC->NSLE.GPIOx = NSLE_GPIOx;
  DC->NSLE.GPIO_Pin = NSLE_GPIO_Pin;
  DC->NEN.GPIOx = NEN_GPIOx;
  DC->NEN.GPIO_Pin = NEN_GPIO_Pin;
  DC->htim = htim;
  DC->dutyCycle = dutyCycle;
  __HAL_TIM_SET_COMPARE(DC->htim, TIM_CHANNEL_1, DC->dutyCycle);
}

void DRV8825_EnableStepper(DRV8825_Controller_Typedef *DRV8825_Controller)
{
  HAL_GPIO_WritePin(DC->NRE.GPIOx, DC->NRE.GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(DC->NSLE.GPIOx, DC->NSLE.GPIO_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(DC->NEN.GPIOx, DC->NEN.GPIO_Pin, GPIO_PIN_RESET);
  HAL_TIM_PWM_Start(DC->htim, TIM_CHANNEL_1);
}

void DRV8825_DisableStepper(DRV8825_Controller_Typedef *DRV8825_Controller);
void DRV8825_SetDutyCycle(DRV8825_Controller_Typedef *DRV8825_Controller, uint16_t dutyCycle);

#undef DC
