/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"

/* USER CODE BEGIN 0 */
#define samples 200
uint32_t aCC_Strobe_Buffer[2] = {20, 0};
uint32_t aCC_Landing_Buffer1[samples] = {
		20,20,20,20,20,20,20,20,20,20,
		25,25,25,25,25,25,25,25,25,25,
		30,30,30,30,30,30,30,30,30,30,
		35,35,35,35,35,35,35,35,35,35,
		40,40,40,40,40,40,40,40,40,40,
		50,50,50,50,50,50,50,50,50,50,
		60,60,60,60,60,60,60,60,60,60,
		70,70,70,70,70,70,70,70,70,70,
		75,75,75,75,75,75,75,75,75,75,
		80,80,80,80,80,80,80,80,80,80,
		80,80,80,80,80,80,80,80,80,80,
		75,75,75,75,75,75,75,75,75,75,
		70,70,70,70,70,70,70,70,70,70,
		60,60,60,60,60,60,60,60,60,60,
		50,50,50,50,50,50,50,50,50,50,
		40,40,40,40,40,40,40,40,40,40,
		35,35,35,35,35,35,35,35,35,35,
		30,30,30,30,30,30,30,30,30,30,
		25,25,25,25,25,25,25,25,25,25,
		20,20,20,20,20,20,20,20,20,20,
};

uint32_t aCC_Landing_Buffer2[samples] = {
		80,80,80,80,80,80,80,80,80,80,
		75,75,75,75,75,75,75,75,75,75,
		70,70,70,70,70,70,70,70,70,70,
		60,60,60,60,60,60,60,60,60,60,
		50,50,50,50,50,50,50,50,50,50,
		40,40,40,40,40,40,40,40,40,40,
		35,35,35,35,35,35,35,35,35,35,
		30,30,30,30,30,30,30,30,30,30,
		25,25,25,25,25,25,25,25,25,25,
		20,20,20,20,20,20,20,20,20,20,
		20,20,20,20,20,20,20,20,20,20,
		25,25,25,25,25,25,25,25,25,25,
		30,30,30,30,30,30,30,30,30,30,
		35,35,35,35,35,35,35,35,35,35,
		40,40,40,40,40,40,40,40,40,40,
		50,50,50,50,50,50,50,50,50,50,
		60,60,60,60,60,60,60,60,60,60,
		70,70,70,70,70,70,70,70,70,70,
		75,75,75,75,75,75,75,75,75,75,
		80,80,80,80,80,80,80,80,80,80,
};
/* USER CODE END 0 */

TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
DMA_HandleTypeDef hdma_tim4_ch1;
DMA_HandleTypeDef hdma_tim4_ch2;

/* TIM3 init function */
void MX_TIM3_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7200;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 100;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 10;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim3);

}
/* TIM4 init function */
void MX_TIM4_Init(void)
{
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 7200;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 50;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  /* Landing lights intensity */
  sConfigOC.Pulse = 100;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.Pulse = 20;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim4);

  HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_1, aCC_Landing_Buffer1, samples);
  HAL_TIM_PWM_Start_DMA(&htim4, TIM_CHANNEL_2, aCC_Landing_Buffer2, samples);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspInit 0 */

  /* USER CODE END TIM3_MspInit 0 */
    /* TIM3 clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
  /* USER CODE BEGIN TIM3_MspInit 1 */

  /* USER CODE END TIM3_MspInit 1 */
  }
  else if(tim_pwmHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspInit 0 */

  /* USER CODE END TIM4_MspInit 0 */
    /* TIM4 clock enable */
    __HAL_RCC_TIM4_CLK_ENABLE();

    /* TIM4 DMA Init */
    /* TIM4_CH1 Init */
    hdma_tim4_ch1.Instance = DMA1_Channel1;
    hdma_tim4_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim4_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim4_ch1.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim4_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim4_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim4_ch1.Init.Mode = DMA_CIRCULAR;
    hdma_tim4_ch1.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim4_ch1) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_pwmHandle,hdma[TIM_DMA_ID_CC1],hdma_tim4_ch1);

    /* TIM4_CH2 Init */
    hdma_tim4_ch2.Instance = DMA1_Channel4;
    hdma_tim4_ch2.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_tim4_ch2.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_tim4_ch2.Init.MemInc = DMA_MINC_ENABLE;
    hdma_tim4_ch2.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
    hdma_tim4_ch2.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
    hdma_tim4_ch2.Init.Mode = DMA_CIRCULAR;
    hdma_tim4_ch2.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_tim4_ch2) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(tim_pwmHandle,hdma[TIM_DMA_ID_CC2],hdma_tim4_ch2);

  /* USER CODE BEGIN TIM4_MspInit 1 */

  /* USER CODE END TIM4_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspPostInit 0 */

  /* USER CODE END TIM3_MspPostInit 0 */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM3 GPIO Configuration
    PA6     ------> TIM3_CH1
    PA7     ------> TIM3_CH2
    */
    GPIO_InitStruct.Pin = STROBE_Pin|BEACON_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM3_MspPostInit 1 */

  /* USER CODE END TIM3_MspPostInit 1 */
  }
  else if(timHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspPostInit 0 */

  /* USER CODE END TIM4_MspPostInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**TIM4 GPIO Configuration
    PB6     ------> TIM4_CH1
    PB7     ------> TIM4_CH2
    PB8     ------> TIM4_CH3
    PB9     ------> TIM4_CH4
    */
    GPIO_InitStruct.Pin = LANDING_RIGHT_Pin|LANDING_LEFT_Pin|NAVIGATION_Pin|LOGO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM4_MspPostInit 1 */

  /* USER CODE END TIM4_MspPostInit 1 */
  }

}

void HAL_TIM_PWM_MspDeInit(TIM_HandleTypeDef* tim_pwmHandle)
{

  if(tim_pwmHandle->Instance==TIM3)
  {
  /* USER CODE BEGIN TIM3_MspDeInit 0 */

  /* USER CODE END TIM3_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM3_CLK_DISABLE();
  /* USER CODE BEGIN TIM3_MspDeInit 1 */

  /* USER CODE END TIM3_MspDeInit 1 */
  }
  else if(tim_pwmHandle->Instance==TIM4)
  {
  /* USER CODE BEGIN TIM4_MspDeInit 0 */

  /* USER CODE END TIM4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM4_CLK_DISABLE();

    /* TIM4 DMA DeInit */
    HAL_DMA_DeInit(tim_pwmHandle->hdma[TIM_DMA_ID_CC1]);
    HAL_DMA_DeInit(tim_pwmHandle->hdma[TIM_DMA_ID_CC2]);
  /* USER CODE BEGIN TIM4_MspDeInit 1 */

  /* USER CODE END TIM4_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
