/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os2.h"
#include "adc.h"
#include "mdf.h"
#include "crc.h"
#include "gpdma.h"
#include "i2c.h"
#include "icache.h"
#include "lptim.h"
#include "usart.h"
#include "memorymap.h"
#include "octospi.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "app_touchgfx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
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
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */
extern "C" {
    int _write(int file, uint8_t *p, int len);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern "C" int _write(int file, uint8_t *p, int len)
{
    HAL_UART_Transmit(&huart4, p, len, 10);
    return len;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

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
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_I2C3_Init();
  MX_I2C4_Init();
  MX_OCTOSPI1_Init();
  MX_SPI1_Init();
  MX_UART4_Init();
  MX_USART1_UART_Init();
  MX_USART3_UART_Init();
  MX_ADC1_Init();
  MX_LPTIM1_Init();
  MX_LPTIM2_Init();
  MX_LPTIM4_Init();
  MX_TIM1_Init();
  MX_LPUART1_UART_Init();
  MX_TIM8_Init();
  MX_ADF1_Init();
  MX_ICACHE_Init();
  MX_CRC_Init();
  MX_TIM15_Init();
  MX_TIM4_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM5_Init();
  MX_RTC_Init();
  MX_TIM17_Init();
  MX_TouchGFX_Init();
  /* Call PreOsInit function */
  MX_TouchGFX_PreOSInit();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim15);
  HAL_TIM_Base_Start_IT(&htim4);
  HAL_TIM_Base_Start_IT(&htim17);
//  HAL_DAC_Start(&hdac1, DAC_CHANNEL_2);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_MSI|RCC_OSCILLATORTYPE_MSIK;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_0;
  RCC_OscInitStruct.LSIDiv = RCC_LSI_DIV1;
  RCC_OscInitStruct.MSIKClockRange = RCC_MSIKRANGE_4;
  RCC_OscInitStruct.MSIKState = RCC_MSIK_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLMBOOST = RCC_PLLMBOOST_DIV4;
  RCC_OscInitStruct.PLL.PLLM = 3;
  RCC_OscInitStruct.PLL.PLLN = 10;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 1;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLLVCIRANGE_1;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_PCLK3;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the force of MSIK in stop mode
  */
  __HAL_RCC_MSIKSTOP_ENABLE();
}

/* USER CODE BEGIN 4 */

extern uint8_t ssRunFlag;
extern void read_ppg();

uint8_t secTime = 0;

uint8_t occurred_imuInterrupt = 0;
uint8_t occurred_PMICBUTTInterrupt = 0;
uint8_t occurred_touchInterrupt = 0;
uint8_t occured_HOMEBTNInterrupt = 0;
uint8_t occurred_PMICBATTChargingInterrupt = 0;
//uint8_t TP_INT = 0;

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == MAG_INT_Pin){
  }
  else if(GPIO_Pin == IMU_INT_Pin){
	  occurred_imuInterrupt = 1;
  }
  else if(GPIO_Pin == PRESS_INT_Pin){
  }
  else if(GPIO_Pin == TP_INT_Pin){
	  occurred_touchInterrupt = 1;
//	  TP_INT = 1;
  }
  else if(GPIO_Pin == PMIC_CHARG_INT_Pin){
	  occurred_PMICBATTChargingInterrupt = 1;
  }
}
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
  if(GPIO_Pin == SOS_BTN_INT_Pin){
	  occurred_PMICBUTTInterrupt = 1;
  }
  else if(GPIO_Pin == HOME_BTN_Pin){
	  occured_HOMEBTNInterrupt = 1;
  }
}

uint8_t RTC_CallBack_Check = 0;
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
	// CatM1?�� ?���????? ?��?�� ?���????? X (?���????? ?��보�?? 받아?���????? ?��?? 경우) => return;
	extern uint8_t time_check;
	if(time_check != 1){
		return;
	}

    extern uint8_t backendStopModeEnterFlag;
	backendStopModeEnterFlag = 0;

    // ?��?�� 5�????? ?��?�� ?��?��
    Set_RTC_Alarm();

    // ?��?�� 발생 ?�� ?��?��?�� 코드
	//	 CatM1, GNSS, PPG 기능 ?��?�� (run backend function)
	//	 enter stop mode
    RTC_CallBack_Check = 1; // TIM start ?��?�� PPG ?��?���????? �??????�� => clock 복구 ?��?��?�� ?��?�� ?��?���????? flag ?��?��

////    extern bool StopModeState;
////    if(StopModeState == true){
////    	osDelay(2000);
////    }
//
//    // PPG 기능 ?��?��
//	extern void ssBegin(uint8_t);
//	extern void ssRead_setting();
//	extern void ssPause_setting();
//	extern uint8_t spo2Flag;
//	extern uint8_t hrFlag;
////	ssRunFlag = 0;
////	osDelay(100);
////	ssBegin(0x00);
////	ssRead_setting();
////	spo2Flag = 1;
////	hrFlag = 1;
////	ssRunFlag = 1;
//
//    if(rtcAlarmEventCount % 2 == 0){
//    	// CatM1, GNSS 기능 ?��?��
//    }
//    rtcAlarmEventCount++;
//
//    osDelay(60*1000);
//
//    // off PPG
////	ssRunFlag = 0;
////	osDelay(100);
////    ssBegin(0x05);
////	ssPause_setting();
////	ssRunFlag = 1;
//	// enter stop mode
//    backendStopModeEnterFlag = 1;

    return;
}

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM2 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM2) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM4)
  {
	  if(ssRunFlag == 1)
	  {
		  read_ppg();
	  }
  }
  if(htim->Instance == TIM17)
  {
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	secTime++;
	if(secTime%60 == 0){
		secTime = 0;
	}
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
