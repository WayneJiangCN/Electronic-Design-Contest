/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#define LED_Pin GPIO_PIN_3
#define LED_GPIO_Port GPIOE
#define KEY_row3_Pin GPIO_PIN_1
#define KEY_row3_GPIO_Port GPIOF
#define KEY_row2_Pin GPIO_PIN_3
#define KEY_row2_GPIO_Port GPIOF
#define KEY1_Pin GPIO_PIN_8
#define KEY1_GPIO_Port GPIOF
#define KEY1_EXTI_IRQn EXTI9_5_IRQn
#define KEY0_Pin GPIO_PIN_9
#define KEY0_GPIO_Port GPIOF
#define KEY0_EXTI_IRQn EXTI9_5_IRQn
#define SDIO2_Pin GPIO_PIN_5
#define SDIO2_GPIO_Port GPIOA
#define SCLK_Pin GPIO_PIN_7
#define SCLK_GPIO_Port GPIOA
#define SDIO1_Pin GPIO_PIN_4
#define SDIO1_GPIO_Port GPIOC
#define SDIO0_Pin GPIO_PIN_5
#define SDIO0_GPIO_Port GPIOC
#define CS_Pin GPIO_PIN_0
#define CS_GPIO_Port GPIOB
#define PS3_Pin GPIO_PIN_1
#define PS3_GPIO_Port GPIOB
#define UPDATE_Pin GPIO_PIN_11
#define UPDATE_GPIO_Port GPIOF
#define KEY_row1_Pin GPIO_PIN_13
#define KEY_row1_GPIO_Port GPIOF
#define KEY_row0_Pin GPIO_PIN_15
#define KEY_row0_GPIO_Port GPIOF
#define KEY_col3_Pin GPIO_PIN_1
#define KEY_col3_GPIO_Port GPIOG
#define KEY_col2_Pin GPIO_PIN_8
#define KEY_col2_GPIO_Port GPIOE
#define KEY_col1_Pin GPIO_PIN_11
#define KEY_col1_GPIO_Port GPIOE
#define KEY_col0_Pin GPIO_PIN_15
#define KEY_col0_GPIO_Port GPIOE
#define Reset_Pin GPIO_PIN_12
#define Reset_GPIO_Port GPIOD
#define PS2_Pin GPIO_PIN_13
#define PS2_GPIO_Port GPIOD
#define AD9959_PWR_Pin GPIO_PIN_3
#define AD9959_PWR_GPIO_Port GPIOG
#define PS1_Pin GPIO_PIN_4
#define PS1_GPIO_Port GPIOG
#define PS0_Pin GPIO_PIN_5
#define PS0_GPIO_Port GPIOG
#define SDIO3_Pin GPIO_PIN_15
#define SDIO3_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
