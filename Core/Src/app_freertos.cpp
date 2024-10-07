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
#include "speaker.h"

#include <gui_generated/initblackscreen_screen/initBlackScreenViewBase.hpp>
#include <gui_generated/falldetected_screen/fallDetectedViewBase.hpp>
#include <gui_generated/temphome_screen/tempHomeViewBase.hpp>
#include <gui_generated/containers/batteryprogress_containerBase.hpp>
#include <gui_generated/charging_screen_screen/charging_screenViewBase.hpp>
#include <gui_generated/uncharging_screen_screen/unCharging_screenViewBase.hpp>
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

extern uint8_t secTime;

uint8_t now_sleepmode = 0;

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
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for checkINTTask */
osThreadId_t checkINTTaskHandle;
const osThreadAttr_t checkINTTask_attributes = {
  .name = "checkINTTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void touchgfxSignalVSync(void);
uint8_t ssRunFlag = 0;
uint8_t pmicInitFlag = 0;

double test_mag_data[15] = {0,};
uint8_t set_bLevel = 7; // GUI val ?��?��
uint8_t before_bLevel = 0;
uint8_t flashlightOn = 0;

uint8_t lteRSSI_0_4 = 0; // CATM1 signal RSSI 0 to 4 value

initBlackScreenViewBase myBlackScreenView;
fallDetectedViewBase myFallDetectedView;
tempHomeViewBase myTempHomeView;

extern uint8_t occurred_imuInterrupt;
extern uint8_t occurred_PMICBUTTInterrupt;

/* USER CODE END FunctionPrototypes */

void StartInitTask(void *argument);
void StartlcdTask(void *argument);
void StartPPMTask(void *argument);
void StartWPMTask(void *argument);
void StartSPMTask(void *argument);
void StartSecTimerTask(void *argument);
void StartCheckINTTask(void *argument);

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

  /* creation of checkINTTask */
  checkINTTaskHandle = osThreadNew(StartCheckINTTask, NULL, &checkINTTask_attributes);

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
//	// PMIC init
//	pmic_init();
//	pmicInitFlag = 1;

	while(!pmicInitFlag);
	speaker_init();
	speaker_test_init();
	for(;;)
	{
		speaker_test();
	}

//	while(!pmicInitFlag);
//	testHaptic();

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
	pmic_init();
	pmicInitFlag = 1;

	while(!pmicInitFlag);
	ST7789_gpio_setting();
	ST7789_Init();
	ST7789_brightness_setting(set_bLevel);

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
	while(!pmicInitFlag);

//  BLE init
	stm32wb5mmg_init();
	stm32wb5mmg_adv_setting(&param_BLE_DATA);

  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
	stm32wb5mmg_adv(&param_BLE_DATA);
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
	while(!pmicInitFlag);

	// CatM1 init
	bg770a_gl_init();

//	// WiFi-BLE init
//	nora_w10_init();

  /* Infinite loop */
  for(;;)
  {
    osDelay(10000);
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
	while(!pmicInitFlag);

	// Smart Sensor Hub init
	ssInit();
	ssBegin();
	ssRead_setting();
	ssRunFlag = 1; // start read PPG, using Timer

	init_iis2mdc();
	init_ism330dhcx();
	init_lps22hh();

//	double pre_pressure[PRESSURE_VAL_LEN] = {0,};

  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
	// read sensor
	double magnetX, magnetY, magnetZ, iisTemp;
	read_iis2mdc(&magnetX, &magnetY, &magnetZ, &iisTemp);

	uint16_t gyroSensi = 125;
	uint8_t accSensi = 2;
	double ismTemp, gyroX, gyroY, gyroZ, accX, accY, accZ;
	read_ism330dhcx(gyroSensi, accSensi, &ismTemp, &gyroX, &gyroY, &gyroZ, &accX, &accY, &accZ);

	double pressure, lpsTemp;
	read_lps22hh(&pressure, &lpsTemp);
//		for(int i=0; i<PRESSURE_VAL_LEN-1; i++){
//			pre_pressure[i] = pre_pressure[i+1];
//		}
//		pre_pressure[PRESSURE_VAL_LEN-1] = pressure;

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
	while(!pmicInitFlag);

	// using parameter init (default val)
	uint8_t now_bLevel = set_bLevel;
	uint8_t bLevelCtrlTimCount = 0;

	uint8_t pre_secTime = 0;
	screenOnTime = 20;
	uint8_t pre_brightness_count = 0;

  /* Infinite loop */
  for(;;)
  {
	osDelay(100);


//		if(bLevelCtrlTimCount*100 > 300){ // bright ctrl add delay
	bLevelCtrlTimCount = 0;
	// change parameter val
	if(now_bLevel != set_bLevel){
		now_bLevel = set_bLevel;
		ST7789_brightness_setting(now_bLevel);
	}

	// screenOnTime == brightness_count�????? ?���????? ?���????? 꺼라
	// brightness_count == 0?���????? 바�?�면 백라?��?���????? 켜라
	if(pre_secTime != secTime && secTime%1 == 0){ // 1sec
		// turn off LCD backlight
		if(brightness_count == 0 && pre_brightness_count >= screenOnTime){
			ST7789_brightness_setting(set_bLevel);
			now_sleepmode = 0;
		}
		else if(brightness_count >= screenOnTime && pre_brightness_count < screenOnTime){
			ST7789_brightness_setting(0);
			myBlackScreenView.changeToInitBlackScreen();
			now_sleepmode = 1;
		}
		pre_brightness_count = brightness_count;
		pre_secTime = secTime;
		brightness_count++;
	}
  }
  /* USER CODE END secTimerTask */
}

/* USER CODE BEGIN Header_StartCheckINTTask */
/**
* @brief Function implementing the checkINTTask thread.
* @param argument: Not used
* @retval None
*/
batteryprogress_containerBase myBatteryprogress_container;
charging_screenViewBase myCharging_screenView;
unCharging_screenViewBase myUnCharging_screenView;
bool isCharging = 0;
uint8_t interrupt_kind = 0;
#define PRESSURE_VAL_LEN 10
#include <math.h>
uint8_t battVal = 0;
unsigned char batterylevel;
double calculateAltitudeDifference(double P1, double P2) {
    const double R = 8.314;       // 기체 ?��?�� (J/(mol·K))
    const double T = 273.15+25;   // ?���??? ?��?�� (K) - ?���??? ??�??? 조건 15°C
    const double g = 9.80665;     // 중력 �????��?�� (m/s²)
    const double M = 0.02896;     // 공기?�� �??? 질량 (kg/mol)

    double altitudeDifference = (R * T) / (g * M) * log(P1 / P2);

    return altitudeDifference;
}
//uint8_t updateBattVal(){
//	uint8_t batt = 0;
//	return batt;
//}
/* USER CODE END Header_StartCheckINTTask */
void StartCheckINTTask(void *argument)
{
  /* USER CODE BEGIN checkINTTask */
	while(!pmicInitFlag);

	double before_falling_pressure[PRESSURE_VAL_LEN] = {0,};
	double after_falling_pressure[PRESSURE_VAL_LEN] = {0,};

  /* Infinite loop */
  for(;;)
  {
    osDelay(100);

    if(occurred_imuInterrupt){
    	occurred_imuInterrupt = 0;
    	interrupt_kind = whatKindInterrupt();
    	if((interrupt_kind & 0x01) == 0x01){
    		// free-fall + pressure(after outlier delet => cal mean val)
    		/*
    		 * back light enable
    		 * change screen
    		 * haptic
    		 * send signal to web server using CatM1
    		 */

    		ST7789_brightness_setting(16);
			myFallDetectedView.changeToFallDetected(); ////////////////////////
    	}
    	if((interrupt_kind & 0x02) == 0x02){
    		// wake-up
    	}
    	if((interrupt_kind & 0x04) == 0x04){
    		// single-tap
    	}
    	if((interrupt_kind & 0x08) == 0x08){
    		// double-tap
    	}
    	if((interrupt_kind & 0x10) == 0x10){
    		// change position
//    		if(now_sleepmode == 1){
//				ST7789_brightness_setting(now_bLevel);
//				myBlackScreenView.changeToInitBlackScreen();
//    		}
    	}
    	if((interrupt_kind & 0x20) == 0x20){
    		// change activity/inactivity
    	}
    }

    // MCU GPIO button click => change to home screen & backlight on
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET){
    	brightness_count = 0;
    	if(flashlightOn){
    		flashlightOn = 0;
    		set_bLevel = before_bLevel; // turn off flash light : brightness
    	}
    	myTempHomeView.changeToHomeScreen();
    }

    // update Battery
    bool pmicBATTERR = 0;
    if(pmicSOCRead(&batterylevel) != 0x00){ // occur err
    	MX_I2C3_Init(); // occur err...
    	pmicBATTERR = 1;
    }
    if(!pmicBATTERR){
    	// update Battery value
    	if(battVal != batterylevel){
    		battVal = batterylevel;
//    		myBatteryprogress_container.changeBATTVal();
    	}

	    // check and update Battery Charging value
//		isCharging = isBATTCharging();
		uint8_t chargingStatus = (uint8_t)isBATTCharging();
		if(chargingStatus != 0xFF && battVal!=100){
			bool isCharging_Now = chargingStatus;
			if(isCharging != isCharging_Now){
				isCharging = isCharging_Now;
				if(isCharging){
//					myBatteryprogress_container.batteryCharging();
					myCharging_screenView.changeChargeScreen();
			    	brightness_count = 0;
				}
				else{
//					myBatteryprogress_container.batteryNotCharging();
					myUnCharging_screenView.changeUnChargeScreen();
			    	brightness_count = 0;
				}
			}
		}
		else if(battVal == 100 && isCharging == true){ // charging finish
			isCharging = false;
			myUnCharging_screenView.changeUnChargeScreen();
	    	brightness_count = 0;
		}
    }

    // PMIC interrupt occur => emergency signal send to Web (CATM1)
    if(occurred_PMICBUTTInterrupt){
    	occurred_PMICBUTTInterrupt = 0;
    }
  }
  /* USER CODE END checkINTTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

uint16_t ssHr = 0;
uint16_t ssSpo2 = 0;
uint32_t ssWalk = 0;

uint8_t canDisplayPPG = 0;

void read_ppg()
{
//	if(canDisplayPPG) return; // full buffer => can display UI // occur timing problem

	uint8_t data[76+1] = {0,}; // +1: status byte
	if(-1 == ssRead(data, sizeof(data))){
//		osDelay(100);
		return;
	}

	struct ssDataEx_format* ssDataEx = (ssDataEx_format*)malloc(sizeof(struct ssDataEx_format));
	rxDataSplit(data, ssDataEx); // return struct format

	if(ssDataEx->readStatus != 0){
		// err status check
		free(ssDataEx);
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

	canDisplayPPG = 1;
}



/* USER CODE END Application */

