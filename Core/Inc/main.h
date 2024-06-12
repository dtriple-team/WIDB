/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32u5xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "st7789.h"
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
#define LCD_PWR_Pin GPIO_PIN_0
#define LCD_PWR_GPIO_Port GPIOD
#define LCD_DC_Pin GPIO_PIN_1
#define LCD_DC_GPIO_Port GPIOE
#define SS_MFIO_Pin GPIO_PIN_4
#define SS_MFIO_GPIO_Port GPIOD
#define SS_RSTN_Pin GPIO_PIN_5
#define SS_RSTN_GPIO_Port GPIOD
#define LCD_RS_Pin GPIO_PIN_1
#define LCD_RS_GPIO_Port GPIOD
#define TP_RESET_Pin GPIO_PIN_2
#define TP_RESET_GPIO_Port GPIOD
#define WiFi_PWR_Pin GPIO_PIN_10
#define WiFi_PWR_GPIO_Port GPIOD
#define WiFi_RESET_Pin GPIO_PIN_9
#define WiFi_RESET_GPIO_Port GPIOD
#define LCD_SS_Pin GPIO_PIN_12
#define LCD_SS_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
