/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <pmic.h>
#include <smartsensor.h>

#include "tim.h"
#include "app_touchgfx.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>
#include "BG770A-GL.h"
#include "NORA-W10.h"
#include "mems.h"
extern "C" {
	#include "stm32wb5mmg.h"
	#include "stm32wb_at_ble.h"
}
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
/* USER CODE BEGIN Variables */
struct ssDataEx_format lcd_ssDataEx;
uint8_t screenOnTime = 0;
uint8_t brightness_count = 0;

/* USER CODE END Variables */
/* Definitions for initTask */
osThreadId_t initTaskHandle;
const osThreadAttr_t initTask_attributes = {
  .name = "initTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for lcdTask */
osThreadId_t lcdTaskHandle;
const osThreadAttr_t lcdTask_attributes = {
  .name = "lcdTask",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for ppmTask */
osThreadId_t ppmTaskHandle;
const osThreadAttr_t ppmTask_attributes = {
  .name = "ppmTask",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for wpmTask */
osThreadId_t wpmTaskHandle;
const osThreadAttr_t wpmTask_attributes = {
  .name = "wpmTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for spmTask */
osThreadId_t spmTaskHandle;
const osThreadAttr_t spmTask_attributes = {
  .name = "spmTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for secTimerTask */
osThreadId_t secTimerTaskHandle;
const osThreadAttr_t secTimerTask_attributes = {
  .name = "secTimerTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityHigh
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void touchgfxSignalVSync(void);
uint8_t ssRunFlag = 0;
uint8_t initFlag = 0;
uint8_t pmicInitFlag = 0;

double test_mag_data[15] = {0,};
uint8_t set_bLevel = 15;

/* USER CODE END FunctionPrototypes */

void StartInitTask(void *argument);
void StartlcdTask(void *argument);
void StartPPMTask(void *argument);
void StartWPMTask(void *argument);
void StartSPMTask(void *argument);
void StartSecTimerTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of initTask */
  initTaskHandle = osThreadNew(StartInitTask, NULL, &initTask_attributes);

  /* creation of lcdTask */
  lcdTaskHandle = osThreadNew(StartlcdTask, NULL, &lcdTask_attributes);

  /* creation of ppmTask */
  ppmTaskHandle = osThreadNew(StartPPMTask, NULL, &ppmTask_attributes);

  /* creation of wpmTask */
  wpmTaskHandle = osThreadNew(StartWPMTask, NULL, &wpmTask_attributes);

  /* creation of spmTask */
  spmTaskHandle = osThreadNew(StartSPMTask, NULL, &spmTask_attributes);

  /* creation of secTimerTask */
  secTimerTaskHandle = osThreadNew(StartSecTimerTask, NULL, &secTimerTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartInitTask */
/**
* @brief Function implementing the initTask thread.
* @param argument: Not used
* @retval None
*/
stm32wb_at_BLE_ADV_DATA_t param_BLE_DATA;
/* USER CODE END Header_StartInitTask */
void StartInitTask(void *argument)
{
  /* USER CODE BEGIN initTask */
//	// I2C test code
//	for(;;){
//		uint8_t arr[3] = {0,};
//			arr[0] = 0xD6; // acc
//			arr[1] = 0xBA; // pressure
//			arr[2] = 0x3C; // magnet
////		for (uint8_t i=0; i<3; i++)
////		{
////		  uint8_t err = HAL_I2C_IsDeviceReady(&hi2c1, arr[i], 1, 1);
////		  err = 0;
////		}
//		uint8_t err = HAL_I2C_IsDeviceReady(&hi2c1, arr[1], 1, 1);
//
//		osDelay(5);
//	}

	// PMIC init
	pmic_init();
	pmicInitFlag = 1;

	// Smart Sensor Hub init
	ssInit();
	ssBegin();
	ssRead_setting();
	ssRunFlag = 1;

	init_iis2mdc();
	init_ism330dhcx();
	init_lps22hh();

	// CatM1 init
	bg770a_gl_init();

	// BLE init
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
//	HAL_Delay(30000);
	stm32wb5mmg_init();
	stm32wb5mmg_adv_setting(&param_BLE_DATA);

	// WiFi-BLE init
	nora_w10_init();

	initFlag = 1;

	// finish Task
	vTaskDelete(NULL);
  /* USER CODE END initTask */
}

/* USER CODE BEGIN Header_StartlcdTask */
/**
* @brief Function implementing the lcdTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartlcdTask */
void StartlcdTask(void *argument)
{
  /* USER CODE BEGIN lcdTask */
	while(!pmicInitFlag);
	ST7789_gpio_setting();
	ST7789_brightness_setting(16);
	ST7789_Init();

	touchgfxSignalVSync();
	MX_TouchGFX_Process();

	vTaskDelete(NULL);
  /* USER CODE END lcdTask */
}

/* USER CODE BEGIN Header_StartPPMTask */
/**
* @brief Function implementing the ppmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartPPMTask */
void StartPPMTask(void *argument)
{
  /* USER CODE BEGIN ppmTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000);
    if(initFlag){
    	stm32wb5mmg_adv(&param_BLE_DATA);
    }
  }
  /* USER CODE END ppmTask */
}

/* USER CODE BEGIN Header_StartWPMTask */
/**
* @brief Function implementing the wpmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartWPMTask */
void StartWPMTask(void *argument)
{
  /* USER CODE BEGIN wpmTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(10000);
    if(initFlag){
    }
  }
  /* USER CODE END wpmTask */
}

/* USER CODE BEGIN Header_StartSPMTask */
/**
* @brief Function implementing the spmTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSPMTask */
void StartSPMTask(void *argument)
{
  /* USER CODE BEGIN spmTask */
	// using parameter init (default val)
	uint8_t now_bLevel = 15;
	uint8_t bLevelCtrlTimCount = 0;

  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
    if(initFlag){
    	// read sensor
    	double magnetX, magnetY, magnetZ, iisTemp;
    	read_iis2mdc(&magnetX, &magnetY, &magnetZ, &iisTemp);

    	uint16_t gyroSensi = 125;
    	uint8_t accSensi = 2;
    	double ismTemp, gyroX, gyroY, gyroZ, accX, accY, accZ;
		read_ism330dhcx(gyroSensi, accSensi, &ismTemp, &gyroX, &gyroY, &gyroZ, &accX, &accY, &accZ);

		double pressure, lpsTemp;
		read_lps22hh(&pressure, &lpsTemp);

    	test_mag_data[0] = magnetX/10; 	// mgauss -> uT
    	test_mag_data[1] = magnetY/10; 	// mgauss -> uT
    	test_mag_data[2] = magnetZ/10; 	// mgauss -> uT
    	test_mag_data[3] = iisTemp;		// degC

    	test_mag_data[4] = 0;

    	test_mag_data[5] = ismTemp;		// degC
		test_mag_data[6] = gyroX/1000; 	// mdeg/s -> deg/s
		test_mag_data[7] = gyroY/1000; 	// mdeg/s -> deg/s
    	test_mag_data[8] = gyroZ/1000; 	// mdeg/s -> deg/s
		test_mag_data[9] = accX/1000;  	// mg -> g
		test_mag_data[10] = accY/1000; 	// mg -> g
		test_mag_data[11] = accZ/1000; 	// mg -> g

		test_mag_data[12] = 0;

		test_mag_data[13] = pressure; 	// hPa
		test_mag_data[14] = lpsTemp;  	// degC

//		if(bLevelCtrlTimCount*100 > 300){ // bright ctrl add delay
			bLevelCtrlTimCount = 0;
			// change parameter val
			if(now_bLevel != set_bLevel){
				now_bLevel = set_bLevel;
				ST7789_brightness_setting(now_bLevel);
			}
//		}
//		bLevelCtrlTimCount++;
    }
  }
  /* USER CODE END spmTask */
}

/* USER CODE BEGIN Header_StartSecTimerTask */
/**
* @brief Function implementing the secTimerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSecTimerTask */
void StartSecTimerTask(void *argument)
{
  /* USER CODE BEGIN secTimerTask */
	screenOnTime = 20; // default screen on time;
  /* Infinite loop */
  for(;;)
  {
    osDelay(1000*5);

    // turn off LCD backlight
    if(brightness_count == 0){
    	ST7789_brightness_setting(set_bLevel);
    }

    if(brightness_count > screenOnTime/5){
    	ST7789_brightness_setting(0);
    }
    else{
        brightness_count++;
    }
  }
  /* USER CODE END secTimerTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

uint16_t ssHr = 0;
uint16_t ssSpo2 = 0;
uint32_t ssWalk = 0;

void read_ppg()
{
	uint8_t data[76+1] = {0,}; // +1: status byte
	if(-1 == ssRead(data, sizeof(data))){
		osDelay(100);
		return;
	}

	struct ssDataEx_format* ssDataEx = (ssDataEx_format*)malloc(sizeof(struct ssDataEx_format));
	rxDataSplit(data, ssDataEx); // return struct format

	if(ssDataEx->readStatus != 0){
		// err status check
		return;
	}

	memcpy(&lcd_ssDataEx, ssDataEx, sizeof(ssDataEx_format));

	if(lcd_ssDataEx.algo.SCDstate == 3){
		ssHr = lcd_ssDataEx.algo.hr/10;
		ssSpo2 = lcd_ssDataEx.algo.spo2/10;
	} else {
		ssHr = 0;
		ssSpo2 = 0;
	}
	ssWalk = lcd_ssDataEx.algo.totalWalkSteps;

//	printf("%d,\t accX:%d,\t accY:%d,\t accZ:%d,\t ", counter++, ssAccX/100, ssAccY/100, ssAccZ/100);
//	printf("HR:%d,\t SpO2:%d\t ", ssHr/10, ssSpo2/10);
//	printf("\r\n");
	free(ssDataEx);
}
/* USER CODE END Application */

