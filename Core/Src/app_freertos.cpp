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
#include "NORA-W10.h"
#include "mems.h"
#include "stm32u5xx_hal.h"
extern "C" {
	#include "stm32wb5mmg.h"
	#include "stm32wb_at_ble.h"
	#include "nrf9160.h"
}
#include "speaker.h"

#include <gui_generated/initblackscreen_screen/initBlackScreenViewBase.hpp>
#include <gui_generated/falldetected_screen/fallDetectedViewBase.hpp>
#include <gui_generated/temphome_screen/tempHomeViewBase.hpp>
#include <gui_generated/containers/batteryprogress_containerBase.hpp>
#include <gui_generated/charging_screen_screen/charging_screenViewBase.hpp>
#include <gui_generated/uncharging_screen_screen/unCharging_screenViewBase.hpp>
#include <gui_generated/sos_alert_screen/sos_alertViewBase.hpp>
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

uint8_t now_sleepmode = 0;

uint8_t nRFCloudFlag = 0;

#define cat_m1_rssi_cycle 40
uint8_t cat_m1_rssi_cycleTime = 0;
bool cat_m1_rssi_cycleFlag = false;

uint8_t mqttTime = 0;
bool mqttFlag = false;

#define mqtt_RetryTime_cycle 11
uint8_t UartRxRetryTime = 0;
bool UartRxRetryTimeFlag = false;

//int gps_operation_cycle  = 60*3;
int gps_operation_cycle  = GNSS_INTERVAL_SEC;
//#define gps_operation_cycle 60*4
uint8_t gpsTime = 0;
bool gpsFlag = false;

#define gps_offCheck_cycle 120
uint8_t gpsOffCheckTime = 0;

int cell_location_operation_cycle  = 60*1;
uint8_t cell_locationTime = 0;
bool cell_locationFlag = true;

#define fall_Check_cycle 60 // falling event occure => after N sec => MQTT // 60
uint8_t fallCheckTime = 0;
uint8_t fallCheckFlag = 0;

#define SOS_Check_cycle 60 // SOS event occure => after N sec => MQTT // 60
uint8_t SOSCheckTime = 0;
uint8_t SOSCheckFlag = 0;
uint8_t sendSOSFlag = 0;

uint8_t pressCheckTime = 0;
uint8_t pressCheckFlag = 0;

uint8_t pressCheckStartTime = 0;
uint8_t pressCheckStartFlag = 0;

uint8_t catM1MqttDangerMessage = 0;

extern cat_m1_Status_t cat_m1_Status;
extern cat_m1_Status_Band_t cat_m1_Status_Band;
extern cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
extern cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection;
extern cat_m1_Status_BandAlert_t cat_m1_Status_BandAlert;
extern cat_m1_Status_GPS_Location_t cat_m1_Status_GPS_Location;
extern cat_m1_Status_uuid_t cat_m1_Status_uuid;
extern cat_m1_Status_Fall_Difference_Value_t cat_m1_Status_Fall_Difference_Value;
extern cat_m1_Status_BATTData_Value_t cat_m1_Status_BATTData_Value;

uint32_t deviceID = 0;
uint8_t deviceID_check = 0;

uint8_t time_check = 0;

#define SAMPLE_COUNT 10
int scdStateCheckCount = 0;
int ssHrSamples[SAMPLE_COUNT] = {0};
int ssSpo2Samples[SAMPLE_COUNT] = {0};
int sampleIndex = 0;
int previousSCDstate = -1;
int previousRSSIstate = -1;
bool lowBatteryAlertSent = false;
bool biosignalAlertSent = false;

//bool freeFall_int_on = false;

float heights[5] = {0};
float height_current = 0;
float bmpAlt = 0;
float deltaAlt = 0;
uint16_t curr_height = 0;
int height_num = 0;

float falling_threshold = 1.0; // ?��?�� ?���?????????? 기�? ?��?�� 차이

uint8_t ssSCD = 0;
uint16_t ssHr = 0;
uint16_t ssSpo2 = 0;
uint32_t ssWalk = 0;
uint32_t imuTemp = 0;
uint32_t press = 0;
uint8_t battVal = 0;

uint32_t ssWalk_SUM = 0;

uint8_t hapticFlag = 1;
uint8_t beforeHaptic = hapticFlag;
uint8_t soundFlag = 1;

uint8_t haptic_SOS = 0;

bool isCharging = 0;

typedef enum{
	interrupt = 0,
	output = 1,
	input = 2
}GPIOMode;

uint16_t hrMeaserPeriode_sec = 60*1;
uint16_t spo2MeaserPeriode_sec = 60*5;
uint8_t ppgMeasFlag = 1;
uint16_t ppgMeaserCount = 0;

#define RTC_WAKEUP_INTERVER_SEC 30 // (min~max) 0~30

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
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for spmTask */
osThreadId_t spmTaskHandle;
const osThreadAttr_t spmTask_attributes = {
  .name = "spmTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for secTimerTask */
osThreadId_t secTimerTaskHandle;
const osThreadAttr_t secTimerTask_attributes = {
  .name = "secTimerTask",
  .stack_size = 512 * 4, // 128
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for checkINTTask */
osThreadId_t checkINTTaskHandle;
const osThreadAttr_t checkINTTask_attributes = {
  .name = "checkINTTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal
};
/* Definitions for dataTask */
osThreadId_t dataTaskHandle;
const osThreadAttr_t dataTask_attributes = {
  .name = "dataTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

stm32wb_at_BLE_ADV_DATA_t param_BLE_DATA;

void read_ppg();
double getAltitude(double pressure_hPa);
void updateHeightData();
void checkFallDetection();
void BandAlert();
extern void touchgfxSignalVSync(void);
uint8_t ssRunFlag = 0;
uint8_t initFlag = 0;
uint8_t pmicInitFlag = 0;
uint8_t wpmInitializationFlag = 0;
uint8_t lcdInitFlag = 0;

double test_mag_data[15] = {0,};
uint8_t set_bLevel = 7; // GUI val ?��?�� // 7
uint8_t before_bLevel = set_bLevel;
uint8_t flashlightOn = 0;

uint8_t lteRSSI_0_4 = 0; // CATM1 signal RSSI 0 to 4 value
uint8_t gpsRSSI_0_1 = 0;

initBlackScreenViewBase myBlackScreenView;
fallDetectedViewBase myFallDetectedView;
tempHomeViewBase myTempHomeView;
sos_alertViewBase mySOSAlertViewBase;

unsigned char batterylevel;
uint16_t batteryVoltage = 0;
float batteryVoltage_cal = 0;

extern uint8_t occurred_imuInterrupt;
extern uint8_t occurred_PMICBUTTInterrupt;

void mfioGPIOModeChange(GPIOMode mode);
void measPPG(void);

void Enter_StopMode(void);
void Enter_StopMode_LCD(void);

#define stopModeMin 1
uint8_t stopModeCount = 0;
RTC_TimeTypeDef startTime;
RTC_DateTypeDef startDate;
void GetTimeAtA(RTC_TimeTypeDef *startTime, RTC_DateTypeDef *startDate);
uint32_t GetElapsedTime(RTC_TimeTypeDef *startTime, RTC_DateTypeDef *startDate);

/* USER CODE END FunctionPrototypes */

void StartInitTask(void *argument);
void StartlcdTask(void *argument);
void StartPPMTask(void *argument);
void StartWPMTask(void *argument);
void StartSPMTask(void *argument);
void StartSecTimerTask(void *argument);
void StartCheckINTTask(void *argument);
void StartDATATask(void *argument);

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

//  /* creation of ppmTask */
//  ppmTaskHandle = osThreadNew(StartPPMTask, NULL, &ppmTask_attributes);

  /* creation of wpmTask */
  wpmTaskHandle = osThreadNew(StartWPMTask, NULL, &wpmTask_attributes);

  /* creation of spmTask */
  spmTaskHandle = osThreadNew(StartSPMTask, NULL, &spmTask_attributes);

  /* creation of secTimerTask */
  secTimerTaskHandle = osThreadNew(StartSecTimerTask, NULL, &secTimerTask_attributes);

  /* creation of checkINTTask */
  checkINTTaskHandle = osThreadNew(StartCheckINTTask, NULL, &checkINTTask_attributes);

  /* creation of dataTask */
  dataTaskHandle = osThreadNew(StartDATATask, NULL, &dataTask_attributes);

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
uint8_t busyPMIC_haptic = 0;
/* USER CODE END Header_StartInitTask */
void StartInitTask(void *argument)
{
  /* USER CODE BEGIN initTask */
//	// PMIC init
//	pmic_init();
//	pmicInitFlag = 1;

//	while(!pmicInitFlag);
//	speaker_init();
//	speaker_test_init();
//	for(;;)
//	{
//		speaker_test();
//	}

//	runHaptic();

	for(;;){
		// haptic
		if(cat_m1_Status_FallDetection.fall_detect == 1){
			if(hapticFlag == 1){
				busyPMIC_haptic = 1;
				runHaptic(20, 500, 3);
				busyPMIC_haptic = 0;
			}
			brightness_count = 0; // lcd backlight count reset
		}
		if(beforeHaptic != hapticFlag){ // toggle haptic BTN
			beforeHaptic = hapticFlag;
			if(hapticFlag == 1){
				busyPMIC_haptic = 1;
				runHaptic(20, 500, 1);
				busyPMIC_haptic = 0;
			}
		}
		if(haptic_SOS == 1){
			if(hapticFlag == 1){
				busyPMIC_haptic = 1;
				runHaptic(20, 500, 3);
				busyPMIC_haptic = 0;
			}
			brightness_count = 0; // lcd backlight count reset
			haptic_SOS = 0;
		}
		osDelay(100);
	}

//	// finish Task
//	vTaskDelete(NULL);
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

	GetTimeAtA(&startTime, &startDate);

	pmic_init();
	pmicInitFlag = 1;

	while(!pmicInitFlag){
		osDelay(10);
	}
	runHaptic(20, 500, 1); // turn on device haptic
//	HAL_Delay(5000); // ?���?????????? ?��?�� + ?��버거 ?���?????????? ?���??????????
	ST7789_gpio_setting();
	ST7789_Init();
	ST7789_brightness_setting(set_bLevel);

	lcdInitFlag = 1;

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
	while(!pmicInitFlag){
		osDelay(10);
	}
//  BLE init
	stm32wb5mmg_init();
	stm32wb5mmg_adv_setting(&param_BLE_DATA);

  /* Infinite loop */
  for(;;)
  {
    osDelay(10);
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
	while(!pmicInitFlag){
		osDelay(10);
	}
	// device ID init (ST UID)
	//deviceID = HAL_GetUIDw2();
	//PRINT_INFO("deviceID >>> %u\r\n",deviceID);

	// UART INT INIT, buffer init
	nrf9160_init();
	nrf9160_clear_buf();
	// CatM1 PWR GPIO ON
	catM1PWRGPIOInit(); // ->??
	HAL_Delay(1000);

//	// WiFi-BLE init
//	nora_w10_init();
//	cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection = {
//	    .bid = deviceID, // Band?�� bid 값을 ?��?��
//	    .type = 0,
//	    .fall_detect = 1
//	};
  /* Infinite loop */
  for(;;)
  {
	if(wpmInitializationFlag == 0)
	{
		// CatM1 init
		nrf9160_ready();
	}
	if(wpmInitializationFlag && cat_m1_Status.Checked == 0)
	{
#if defined(nRF9160_nRFCLOUD_Init)
		if(!nRFCloudFlag)
		{
			catM1nRFCloud_Init();
		}
#endif
		nrf9160_check();
	}
	if(wpmInitializationFlag && cat_m1_Status.Checked == 1)
	{
		nrf9160_mqtt_setting();
		if(cat_m1_Status.InitialLoad == 0)
		{
			osDelay(1000);
			if(time_check == 0)
			{
				nrf9160_Get_time();
				time_check = 1;
			}
			nrf9160_Get_rssi();

			if(-95 <= cat_m1_Status_Band.rssi){
				previousRSSIstate = 0;
				lteRSSI_0_4 = 4;
			} else if(-105 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -95) {
				previousRSSIstate = 0;
				lteRSSI_0_4 = 3;
			} else if(-115 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -105) {
				previousRSSIstate = 0;
				lteRSSI_0_4 = 2;
			} else if(-125 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -115) {
				lteRSSI_0_4 = 1;
			} else {
				lteRSSI_0_4 = 0;
			}
			cat_m1_Status.InitialLoad = 1;
		}
		//gpsTime = 0;
		cat_m1_rssi_cycleTime = 0;
	}
	if(wpmInitializationFlag && cat_m1_Status.Checked == 2)
	{
#if defined(nRF9160_nRFCLOUD_Init)
			if ((strlen((const char*)cat_m1_at_cmd_rst.uuid) > 0) && cat_m1_Status.mqttChecking == 0)
			{
				cat_m1_Status_uuid.bid = deviceID;
				send_UUID(&cat_m1_Status_uuid);
			}
#endif
#if !defined(nRF9160_KT)
		if ((mqttFlag && cat_m1_Status.gpsChecking == 0) || catM1MqttDangerMessage)
#else
		if (mqttFlag || catM1MqttDangerMessage)
#endif
		{
			//_State();
			//test_send_json_publish();

			if(cat_m1_Status.mqttChecking == 0)
			{
				cat_m1_Status_Band_t cat_m1_Status_Band =
				{
					.bid = deviceID,
					.pid = 0xA021,
					.rssi = (cat_m1_at_cmd_rst.rssi),
					.start_byte = 0xAA,
					.hr = ssHr,
					.spo2 = ssSpo2,
					.motionFlag = lcd_ssDataEx.algo.spo2MotionFlag,
					.scdState = ssSCD,
					.activity = lcd_ssDataEx.algo.activity,
					.walk_steps = ssWalk,
					.run_steps = 0,
					.temperature = imuTemp,
					.pres = cat_m1_at_cmd_rst.altitude,
					.battery_level = battVal
				};
				send_Status_Band(&cat_m1_Status_Band);

				#if defined(BattData_Value_Send)
					cat_m1_Status_BATTData_Value.bid = deviceID;
					cat_m1_Status_BATTData_Value.level = (int)batterylevel;
					cat_m1_Status_BATTData_Value.voltage = (int)batteryVoltage;
					send_BATTData_Value(&cat_m1_Status_BATTData_Value);
				#endif
				// **RTC time update (correction)**
				// Retrieve time information from CatM1
				// Compare the RTC time with the CatM1 time
				// If the difference is within 1 minute:
				//     Update the RTC value using the CatM1 time
				// Otherwise:
				//     Retain the current RTC value
				nrf9160_Get_time();
				nrf9160_Get_rssi();

				if(-95 <= cat_m1_Status_Band.rssi){
					previousRSSIstate = 0;
					lteRSSI_0_4 = 4;
				} else if(-105 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -95) {
					previousRSSIstate = 0;
					lteRSSI_0_4 = 3;
				} else if(-115 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -105) {
					previousRSSIstate = 0;
					lteRSSI_0_4 = 2;
				} else if(-125 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -115) {
					lteRSSI_0_4 = 1;
				} else {
					lteRSSI_0_4 = 0;
				}

				osDelay(500);
				extern RTC_HandleTypeDef hrtc;
				extern catM1Time nowTimeinfo;
				extern RTC_TimeTypeDef sTime;
				extern RTC_DateTypeDef sDate;

				HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
				catM1Time nowNetTimeinfo = getCatM1Time();
				catM1Time nowRTCTimeinfo = {sDate.Year, sDate.Month, sDate.Date, sTime.Hours, sTime.Minutes, sTime.Seconds};

				if(isDifferenceWithinNMinute(nowNetTimeinfo, nowRTCTimeinfo, mqtt_operation_cycle+60)){
					nowTimeinfo = nowNetTimeinfo;

					// To prevent the appearance of time decreasing when updating RTC time with GNSS time,
					// caused by RTC time flowing faster than GNSS time.
					// RTC ?��간이 GNSS ?��간보?�� 빠르�?????????? ?��르면?��, RTC ?��간을 GNSS ?��간으�?????????? ?��?��?��?��?�� ?�� ?��간이 감소?��?�� 것처?�� 보이?�� ?��?��?�� 방�??���?????????? ?��?��.
					if(sTime.Minutes > (uint8_t)nowTimeinfo.min){
						sDate.Year = (uint8_t)nowTimeinfo.year;
						sDate.Month = (uint8_t)nowTimeinfo.month;
						sDate.Date = (uint8_t)nowTimeinfo.day;
						sTime.Hours = (uint8_t)nowTimeinfo.hour;
						sTime.Minutes = sTime.Minutes;
						sTime.Seconds = 0;
					}
					else {
						sDate.Year = (uint8_t)nowTimeinfo.year;
						sDate.Month = (uint8_t)nowTimeinfo.month;
						sDate.Date = (uint8_t)nowTimeinfo.day;
						sTime.Hours = (uint8_t)nowTimeinfo.hour;
						sTime.Minutes = (uint8_t)nowTimeinfo.min;
						sTime.Seconds = (uint8_t)nowTimeinfo.sec;
					}

					HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
					HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
				} else {
					nowTimeinfo = nowRTCTimeinfo;
				}
			}
			mqttFlag = false;
			catM1MqttDangerMessage = 0;
		}

		if ((strlen((const char*)cat_m1_at_cmd_rst.gps) > 0) && cat_m1_Status.mqttChecking == 0 && cat_m1_Status.gpsChecking == 0)
		{
		    cat_m1_Status_GPS_Location.bid = deviceID;
		    send_GPS_Location(&cat_m1_Status_GPS_Location);
		}
#if defined(nRF9160_cell_location)
		//soundFlag off no nRF9160_cell_location
		else if (soundFlag && !isCharging && cell_locationFlag && cat_m1_Status.mqttChecking == 0 && cat_m1_Status.gpsChecking == 0)
		{
		    nrf9160_Get_cell_location();
		    cell_locationFlag = false;
		}
#endif
		if(gpsFlag && cat_m1_Status.mqttChecking == 0)
		{
			//catM1MqttDangerMessage = 1;
			//nrf9160_Stop_gps();
			nrf9160_Get_gps();
			//nrf9160_Get_gps_State();
			//gpsFlag = false;
		}
		if(cat_m1_Status.gpsChecking)
		{
			//nrf9160_Get_gps_State();
			if(cat_m1_Status.gpsOff)
			{
				nrf9160_Stop_gps();
				gpsTime = 0;
				gpsOffCheckTime = 0;
			}
		}
		if(cat_m1_rssi_cycleFlag && cat_m1_Status.gpsChecking == 0 && cat_m1_Status.mqttChecking == 0)
		{
			nrf9160_Get_rssi();
			cat_m1_rssi_cycleFlag = false;
		}

	}
	//	if(wpmFlag ==1)
	//	{

	//		wpmFlag = 0;
	//	}
	//osDelay(10000);
	if(initFlag){

	}
	BandAlert();
	osDelay(10);
  }
  /* USER CODE END wpmTask */
}

/* USER CODE BEGIN Header_StartSPMTask */
/**
* @brief Function implementing the spmTask thread.
* @param argument: Not used
* @retval None
*/

//#define fall_algo_test
#if !defined(fall_algo_test)
#define ACC_threshold 3000
#else
#define ACC_threshold 2000 // 2G
#define GYRO_threshold 200 // 200degree/s
#endif

#if defined(nRF9160_Fall_Difference_Value_Send)
double magnitude = 0;
#endif


#if !defined(fall_algo_test)
// �???????????��?�� ?��?��?�� 구조�??????????
typedef struct {
    double x;
    double y;
    double z;
} AccelData;
uint8_t detect_fall(AccelData* accel_data, double threshold) {
	double magnitude_local = sqrt(accel_data->x * accel_data->x +
								   accel_data->y * accel_data->y +
								   accel_data->z * accel_data->z);
#if defined(nRF9160_Fall_Difference_Value_Send)
	magnitude = magnitude < magnitude_local ? magnitude_local : magnitude;
#endif

	if (magnitude_local > threshold) {
		return 1; // ?��?��?���?????????? 감�?
	}
	else return 0; // ?��?�� ?��?��
}
#else
typedef struct {
    double ax, ay, az;
    double gx, gy, gz;
} IMUData;
uint8_t detect_fall(IMUData* imu_data, double accel_threshold, double gyro_threshold) {
	double accel_magnitude_local = sqrt(imu_data->ax * imu_data->ax +
										imu_data->ay * imu_data->ay +
										imu_data->az * imu_data->az);
	double gyro_magnitude_local = sqrt(imu_data->gx * imu_data->gx +
										imu_data->gy * imu_data->gy +
										imu_data->gz * imu_data->gz);
#if defined(nRF9160_Fall_Difference_Value_Send)
	magnitude = magnitude < magnitude_local ? magnitude_local : magnitude;
#endif

	if (accel_magnitude_local > accel_threshold && gyro_magnitude_local > gyro_threshold) {
		return 1; // ?��?��?���?????????? 감�?
	}
	else return 0; // ?��?�� ?��?��
}
#endif

/* USER CODE END Header_StartSPMTask */
void StartSPMTask(void *argument)
{
  /* USER CODE BEGIN spmTask */
	while(!pmicInitFlag){
		osDelay(10);
	}
	// Smart Sensor Hub init
	ssInit();
//	ssBegin(0x00);
//	ssRead_setting();
//	ssRunFlag = 1; // start read PPG, using Timer

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

	uint16_t imu_walk;
	read_ism330dhcx_stepCount(&imu_walk);
	ssWalk = (uint32_t)imu_walk;

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

	imuTemp = ismTemp;
	press = pressure;

#if !defined(fall_algo_test)
	AccelData accel_data;
	accel_data.x = accX;
	accel_data.y = accY;
	accel_data.z = accZ;
	uint8_t highG_Detect = 0;
	highG_Detect = detect_fall(&accel_data, ACC_threshold);
#else
	IMUData imu_data;
	imu_data.ax = accX;
	imu_data.ay = accY;
	imu_data.az = accZ;
	imu_data.gx = gyroX;
	imu_data.gy = gyroY;
	imu_data.gz = gyroZ;
	uint8_t highG_Detect = detect_fall(&imu_data, ACC_threshold, GYRO_threshold);
#endif

//	if(ssRunFlag == 1)
//	{
//	  read_ppg();
//	}
	bmpAlt = getAltitude(pressure);
	//PRINT_INFO("bmpAlt >>> %f\r\n",bmpAlt);

	if (bmpAlt < 0)
	{
	    bmpAlt = -bmpAlt;
	}

	if(pressCheckFlag && pressCheckStartFlag)// && ssSCD == 3)
	{
		updateHeightData();
		pressCheckFlag = 0;
	}
//	if(freeFall_int_on && ssSCD == 3)
//	{
//		checkFallDetection();
//		freeFall_int_on = false;
//	}
	if(highG_Detect == 1)// && ssSCD == 3)
	{
		checkFallDetection();
//		freeFall_int_on = false;
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
uint8_t pre_secTime = 0;
/* USER CODE END Header_StartSecTimerTask */
void StartSecTimerTask(void *argument)
{
  /* USER CODE BEGIN secTimerTask */
	while(!pmicInitFlag){
		osDelay(10);
	}
	// using parameter init (default val)
	uint8_t now_bLevel = set_bLevel;
	uint8_t bLevelCtrlTimCount = 0;

	screenOnTime = 20;
	uint8_t pre_brightness_count = 0;

	extern uint8_t secTime;

	while(!lcdInitFlag){
		osDelay(10);
	}
  /* Infinite loop */
  for(;;)
  {
	osDelay(100);

//		if(bLevelCtrlTimCount*100 > 300){ // bright ctrl add delay
	bLevelCtrlTimCount = 0;
	// change parameter val
	if(now_bLevel != set_bLevel){
		now_bLevel = set_bLevel;
//		HAL_Delay(100);
		ST7789_brightness_setting(now_bLevel);
	}

	// screenOnTime == brightness_count�???????????????? ?���???????????????? ?���???????????????? 꺼라
	// brightness_count == 0?���???????????????? 바�?�면 백라?��?���???????????????? 켜라
//	if(pre_secTime != secTime && secTime%1 == 0){ // 1sec
//		// turn off LCD backlight
//		if(brightness_count == 0 && pre_brightness_count >= screenOnTime){
//			ST7789_brightness_setting(set_bLevel);
//			now_sleepmode = 0;
//		}
//		else if(brightness_count >= screenOnTime && pre_brightness_count < screenOnTime){
//			ST7789_brightness_setting(0);
//			myBlackScreenView.changeToInitBlackScreen();
//			now_sleepmode = 1;
//		}
//		pre_brightness_count = brightness_count;
//		pre_secTime = secTime;
//		brightness_count++;
//	}
	if(pre_secTime != secTime){ // 1sec
		pre_secTime = secTime;

		// turn on LCD backlight (in screenOnTime, active only one)
		if(sendSOSFlag == 0){
			if(brightness_count == 0){
				if(pre_brightness_count >= screenOnTime)
					ST7789_brightness_setting(set_bLevel);
				brightness_count++;
				now_sleepmode = 0;
			}
			else if(brightness_count < screenOnTime){
				brightness_count++;
			}
			// turn off LCD backlight (out of screenOnTime)
			else if(brightness_count >= screenOnTime){
				ST7789_brightness_setting(0);
				myBlackScreenView.changeToInitBlackScreen();
				osDelay(100);
				now_sleepmode = 1;
			}
			pre_brightness_count = brightness_count;
		}

		//////////////////////////////// 5�?????? 주기 ?��?�� Task�?????? CatM1, GNSS ?��?�� ?��?�� ////////////////////////////////
#if 0
		cat_m1_rssi_cycleTime++;
//		PRINT_INFO("mqttTime >>> %d\r\n",mqttTime);
		if(cat_m1_rssi_cycleTime > cat_m1_rssi_cycle )
		{
			cat_m1_rssi_cycleFlag = true;
			cat_m1_rssi_cycleTime = 0;
		}
#if !defined(nRF9160_KT)
		if(cat_m1_Status.gpsChecking == 0)
		{
			mqttTime++;
		}
#else
			mqttTime++;
#endif
//		PRINT_INFO("mqttTime >>> %d\r\n",mqttTime);
		if(mqttTime > mqtt_operation_cycle)
		{
			mqttFlag = true;
			mqttTime = 0;
		}

		if(cat_m1_Status.txflag)
		{
			UartRxRetryTime++;
		}
//		PRINT_INFO("UartRxRetryTime >>> %d\r\n",UartRxRetryTime);
#endif
		if(UartRxRetryTime > 3)
		{
			uart_init();
			UartRxRetryTime = 0;
			cat_m1_Status.txflag = 0;
		}
		else if(UartRxRetryTime > 10)
		{
#if !defined(nRF9160_initial_upload)
			catM1Reset();
#endif
			UartRxRetryTime = 0;
			cat_m1_Status.txflag = 0;
		}
#if 0
#if !defined(nRF9160_no_auto_gps)
		if(gpsFlag == 0)
		{
			gpsTime++;
		}
#endif
//		PRINT_INFO("gpsTime >>> %d\r\n",gpsTime);
		if(gpsTime > gps_operation_cycle)
		{
			gpsFlag = true;
			gpsTime = 0;
		}
#endif
		if(cat_m1_Status.gpsChecking)
		{
			gpsOffCheckTime++;
		}
		if(gpsOffCheckTime > gps_offCheck_cycle)
		{
#if !defined(nRF9160_KT)
			catM1Reset();
#else
			nrf9160_Stop_gps();

#endif
		}
//		if(cell_locationFlag == 0)
//		{
//			cell_locationTime++;
//		}
//		if(cell_locationTime > cell_location_operation_cycle)
//		{
//			cell_locationFlag = true;
//			cell_locationTime = 0;
//		}
		if(cat_m1_Status_FallDetection.fall_detect)
		{
			fallCheckTime++;
		}
		if(fallCheckTime > fall_Check_cycle)
		{
			fallCheckFlag = 1;
			fallCheckTime = 0;
		}
		pressCheckTime++;
		if(pressCheckTime >= 1)
		{
			pressCheckFlag = 1;
			pressCheckTime = 0;
		}
		pressCheckStartTime++;
		if(pressCheckStartTime >= 7)
		{
			pressCheckStartFlag = 1;
			pressCheckStartTime = 0;
		}

		if(sendSOSFlag == 1)
		{
			SOSCheckTime++;
			brightness_count = 0;
		}
		if(SOSCheckTime > SOS_Check_cycle){
			if (cat_m1_Status.gpsChecking)
			{
				nrf9160_Stop_gps();
			}

			sendSOSFlag = 0;
			SOSCheckTime = 0;
			// haptic
			haptic_SOS = 1;
			// send SOS MQTT
			cat_m1_Status_BandAlert.bid = deviceID;
			cat_m1_Status_BandAlert.type = 6;
			cat_m1_Status_BandAlert.value = 1;
			send_Status_BandAlert(&cat_m1_Status_BandAlert);
			catM1MqttDangerMessage = 1;

			gpsFlag = true;
		}

		measPPG();

//		if(secTime % 20 == 0){
//			now_sleepmode = 1;
//		}
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
uint8_t interrupt_kind = 0;
#define PRESSURE_VAL_LEN 10
#include <math.h>
double calculateAltitudeDifference(double P1, double P2) {
    const double R = 8.314;       // 기체 ?��?�� (J/(mol·K))
    const double T = 273.15+25;   // ?���?????????????? ?��?�� (K) - ?���?????????????? ??�?????????????? 조건 15°C
    const double g = 9.80665;     // 중력 �???????????????��?�� (m/s²)
    const double M = 0.02896;     // 공기?�� �?????????????? 질량 (kg/mol)

    double altitudeDifference = (R * T) / (g * M) * log(P1 / P2);

    return altitudeDifference;
}
//uint8_t updateBattVal(){
//	uint8_t batt = 0;
//	return batt;
//}
uint8_t finishReadPPG = 1;
uint8_t backendStopModeEnterFlag = 1;
__attribute__((section(".retention_ram"))) uint8_t rtcAlarmEventCount = 0;
int timerSecCounter = -1;
uint8_t spo2Flag = 0;
uint8_t hrFlag = 0;
/* USER CODE END Header_StartCheckINTTask */
void StartCheckINTTask(void *argument)
{
  /* USER CODE BEGIN checkINTTask */
	while(!pmicInitFlag){
		osDelay(10);
	}
	double before_falling_pressure[PRESSURE_VAL_LEN] = {0,};
	double after_falling_pressure[PRESSURE_VAL_LEN] = {0,};

  /* Infinite loop */
  for(;;)
  {
    osDelay(100);

	extern uint8_t RTC_CallBack_Check;
	if(RTC_CallBack_Check == 1){ //5�??????
		RTC_CallBack_Check = 0;

		// PPG 기능 ?��?��
		ssRunFlag = 0;
//		osDelay(100);
		ssBegin(0x00);
		ssRead_setting();
		spo2Flag = 1;
		hrFlag = 1;
		ssRunFlag = 1;

		if(rtcAlarmEventCount % 2 == 0){ //10�??????
			// CatM1, GNSS 기능 ?��?��
			cat_m1_rssi_cycleFlag = true;
			gpsFlag = true;
		}
		rtcAlarmEventCount++;

		//timerSecCounter = 60*10; // about 60sec
		timerSecCounter = 140*10; // about 140sec
	}
	else {
		if(timerSecCounter == 0){ // after about 60sec
			// off PPG
			ssRunFlag = 0;
	//		osDelay(100);
			ssBegin(0x05);
			ssPause_setting();
			ssRunFlag = 1;
			// enter stop mode
			backendStopModeEnterFlag = 1;
		}
		timerSecCounter--;
	}

    if(now_sleepmode == 1 && backendStopModeEnterFlag == 1){
    	// PPG meas finish
    	if(finishReadPPG == 1){
//    		finishReadPPG = 0;
			now_sleepmode = 0;
			Enter_StopMode_LCD();
			int a = 0;
    	}
	}

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
//    		freeFall_int_on = true;

//    		cat_m1_Status_FallDetection.bid = deviceID;
//    		cat_m1_Status_FallDetection.type = 0;
//    		cat_m1_Status_FallDetection.fall_detect = 1;
//
//    		PRINT_INFO("catM1MqttDangerMessage\r\n");
//
//    		myFallDetectedView.changeToFallDetected();
//    		before_bLevel = set_bLevel;
//    		brightness_count = 0;
//    		ST7789_brightness_setting(16);

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
//    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET){
    extern uint8_t occured_HOMEBTNInterrupt;
    if(occured_HOMEBTNInterrupt == 1){
    	occured_HOMEBTNInterrupt = 0;
    	brightness_count = 0;
    	if(flashlightOn){
    		flashlightOn = 0;
    		set_bLevel = before_bLevel; // turn off flash light : brightness
    	}
    	myTempHomeView.changeToHomeScreen();

    	ST7789_brightness_setting(before_bLevel);

    	// cat_m1_Status_FallDetection.fall_detect = 0;
    	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));

    	fallCheckTime = 0;

		sendSOSFlag = 0;
		fallCheckTime = 0;

#if defined(nRF9160_Fall_Difference_Value_Send)
    	magnitude = 0;
#endif
    }

    // update Battery
    bool pmicBATTERR = 0;
    if(busyPMIC_haptic == 0){ // not run PMIC haptic (I2C3)
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
						ppgMeasFlag = 0;
					}
					else{
	//					myBatteryprogress_container.batteryNotCharging();
						myUnCharging_screenView.changeUnChargeScreen();
						brightness_count = 0;
						ppgMeasFlag = 1;
					}
				}
			}
			else if(battVal == 100 && isCharging == true){ // charging finish
				isCharging = false;
				myUnCharging_screenView.changeUnChargeScreen();
				brightness_count = 0;
			}
		}

		pmicVCELLRead(&batteryVoltage);
		batteryVoltage_cal = batteryVoltage * 78.125 / 1000000;
    }

    // PMIC interrupt occur => emergency signal send to Web (CATM1)
    if(occurred_PMICBUTTInterrupt){
//    	if (cat_m1_Status.gpsChecking)
//    	{
//    	nrf9160_Stop_gps();
//    	}
    	// change screen
		before_bLevel = set_bLevel;
		ST7789_brightness_setting(16);
		brightness_count = 0;
    	mySOSAlertViewBase.changeToSOSDetected();
    	// haptic
    	haptic_SOS = 1;
//    	// send SOS MQTT
//    	cat_m1_Status_BandAlert.bid = deviceID;
//		cat_m1_Status_BandAlert.type = 6;
//		cat_m1_Status_BandAlert.value = 1;
//		send_Status_BandAlert(&cat_m1_Status_BandAlert);
//		catM1MqttDangerMessage = 1;
    	sendSOSFlag = 1;

    	occurred_PMICBUTTInterrupt = 0;
    }
  }
  /* USER CODE END checkINTTask */
}

/* USER CODE BEGIN Header_StartDATATask */
/**
* @brief Function implementing the dataTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDATATask */
void StartDATATask(void *argument)
{
  /* USER CODE BEGIN dataTask */
	while(!pmicInitFlag){
		osDelay(10);
	}
  /* Infinite loop */
  for(;;)
  {
	 receive_response();// Cat-M1 Buffer parsing
	 osDelay(10);
  }
  /* USER CODE END dataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

//uint16_t ssHr = 0;
//uint16_t ssSpo2 = 0;
//uint32_t ssWalk = 0;

uint8_t canDisplayPPG = 0;
uint8_t checkReadStatus = 0;

#define SDC_COUNT 10

int scdStateSamples[SDC_COUNT] = {0};
int scdSampleIndex = 0;

void read_ppg()
{
    uint8_t data[76+1] = {0,};
    if(-1 == ssRead(data, sizeof(data))){
        return;
    }

    struct ssDataEx_format* ssDataEx = (ssDataEx_format*)malloc(sizeof(struct ssDataEx_format));
    rxDataSplit(data, ssDataEx);

    checkReadStatus = ssDataEx->readStatus;

    if(ssDataEx->readStatus != 0){
        free(ssDataEx);
        return;
    }

//    if(ssDataEx->algo.SCDstate == 0){
//    	ssWalk = ssDataEx->algo.totalWalkSteps + ssWalk_SUM;
//        free(ssDataEx);
//        return;
//    }

    memcpy(&lcd_ssDataEx, ssDataEx, sizeof(ssDataEx_format));

    if(spo2Flag == 1 || hrFlag == 1){
		scdStateSamples[scdSampleIndex] = lcd_ssDataEx.algo.SCDstate;
		scdSampleIndex = (scdSampleIndex + 1) % SDC_COUNT;

		int count1 = 0, count2 = 0, count3 = 0;
		for (int i = 0; i < SDC_COUNT; i++)
		{
			if (scdStateSamples[i] == 1) count1++;
			else if (scdStateSamples[i] == 2) count2++;
			else if (scdStateSamples[i] == 3) count3++;
		}

		int scdStateAvg;
		if (count3 >= count1 && count3 >= count2) scdStateAvg = 3;
		else if (count2 >= count1 && count2 >= count3) scdStateAvg = 2;
		else scdStateAvg = 1;

		if (scdStateAvg == 3)
		{
			ssSCD = 3;
			ssHr = lcd_ssDataEx.algo.hr / 10;

			if (lcd_ssDataEx.algo.spo2 != 0)
			{
				ssSpo2 = lcd_ssDataEx.algo.spo2 / 10;
			}
		}
		else if (scdStateAvg == 2)
		{
			ssSCD = 2;
			ssHr = 0;
			ssSpo2 = 0;
		}
		else
		{
			ssSCD = 1;
			ssHr = 0;
			ssSpo2 = 0;
		}
    }

//    ssWalk = lcd_ssDataEx.algo.totalWalkSteps + ssWalk_SUM;

    free(ssDataEx);
    canDisplayPPG = 1;
    finishReadPPG = 1;
}

double getAltitude(double pressure_hPa) {
    // hPa�?????????? Pa�?????????? �???????????��
    double pressure_Pa = pressure_hPa * 100.0; // 1 hPa = 100 Pa

    // ?��?��면에?��?�� 기�? ?��?�� (Pa)
    const double P0 = 1013.25 * 100.0; // ?��반적?�� ?��?���?????????? ?��?�� �?????????? (hPa?��?�� Pa�?????????? �???????????��)

    // ??�?????????? ?��?�� 공식?�� ?��?�� 고도 계산
    double p = pressure_Pa / P0; // ?��?? ?��?��
    double b = 1.0 / 5.255; // �???????????��
    double alt = 44330.0 * (1.0 - pow(p, b)); // 고도 (미터 ?��?��)

    return alt;
}

void updateHeightData()
{
	switch (height_num)
	{
	case 0:
		heights[height_num] = bmpAlt;
		height_num++;
		break;
	case 1:
		heights[height_num] = bmpAlt;
		height_num++;
		break;
	case 2:
		heights[height_num] = bmpAlt;
		height_num++;
		break;
	case 3:
		heights[height_num] = bmpAlt;
		height_num++;
		break;
	case 4:
		heights[height_num] = bmpAlt;
		height_num = 0;
		break;
	}

    height_current = (heights[0] + heights[1] + heights[2] + heights[3] + heights[4]) / 5;
    //PRINT_INFO("height_current >>> %f\r\n",height_current);
}

void checkFallDetection()
{
    float height_int = bmpAlt;
    float min_height = height_int;

    for (int n = 0; n < 7; ++n)
    {
        deltaAlt = bmpAlt - height_int;

        if (n > 0 && bmpAlt < min_height)
        {
            min_height = bmpAlt;
        }
        osDelay(0.15);
    }

    float diff = min_height - height_current;

    //PRINT_INFO("Height diff: %f - %f = %f[m]\r\n", min_height, height_current, diff);
#if defined(nRF9160_Fall_Difference_Value_Send)
    cat_m1_Status_Fall_Difference_Value.bid = deviceID;
    cat_m1_Status_Fall_Difference_Value.data = (diff * 100);
    cat_m1_Status_Fall_Difference_Value.accScal_data = (magnitude);
    send_Fall_Difference_Value(&cat_m1_Status_Fall_Difference_Value);
#endif
    if (diff > falling_threshold)
    {
    	PRINT_INFO("Fall detected!\r\n");
		cat_m1_Status_FallDetection.bid = deviceID;
		cat_m1_Status_FallDetection.type = 0;
		cat_m1_Status_FallDetection.fall_detect = 1;

		myFallDetectedView.changeToFallDetected();
		before_bLevel = set_bLevel;
		brightness_count = 0;
		ST7789_brightness_setting(16);
    }
    else
    {
    	PRINT_INFO("Not detected\r\n");
    }

    for (int i = 0; i < 5; ++i)
    {
        heights[i] = min_height;
    }
}

void BandAlert()
{
	if(cat_m1_Status.mqttConnectionStatus == 1)
	{
		if (fallCheckFlag == 1 && cat_m1_Status.mqttChecking == 0)
		{
			fallCheckFlag = 0;
			if(cat_m1_Status.gpsChecking)
			{
				nrf9160_Stop_gps();
			}
				catM1MqttDangerMessage = 1;
				send_Status_FallDetection(&cat_m1_Status_FallDetection);
				gpsFlag = 1;

//				ST7789_brightness_setting(before_bLevel);
//		    	myTempHomeView.changeToHomeScreen();
		}
		if (cat_m1_Status.InitialLoad && previousRSSIstate != 1 && cat_m1_Status.mqttChecking == 0)
		{
			if(-125 <= cat_m1_Status_Band.rssi && cat_m1_Status_Band.rssi < -115)
			{
				cat_m1_Status_BandAlert.bid = deviceID;
				cat_m1_Status_BandAlert.type = 5;
				cat_m1_Status_BandAlert.value = 1;
				send_Status_BandAlert(&cat_m1_Status_BandAlert);
			}
			previousRSSIstate = 1;
		}
		if (ssSCD == 1 && previousSCDstate != 1 && cat_m1_Status.mqttChecking == 0)
		{
//			if (cat_m1_Status.gpsChecking)
//			{
//				nrf9160_Stop_gps();
//			}
			cat_m1_Status_BandAlert.bid = deviceID;
			cat_m1_Status_BandAlert.type = 3;
			cat_m1_Status_BandAlert.value = 1;
			send_Status_BandAlert(&cat_m1_Status_BandAlert);

			previousSCDstate = 1;
		}
		else if (ssSCD == 2 || ssSCD == 3)
		{
			previousSCDstate = ssSCD;
		}
		if (battVal < 15 && !lowBatteryAlertSent && cat_m1_Status.mqttChecking == 0)
		{
		    cat_m1_Status_BandAlert.bid = deviceID;
		    cat_m1_Status_BandAlert.type = 1;
		    cat_m1_Status_BandAlert.value = 1;
		    send_Status_BandAlert(&cat_m1_Status_BandAlert);
		    lowBatteryAlertSent = true;
		}
		if (battVal < 50 && !lowBatteryAlertSent && cat_m1_Status.mqttChecking == 0)
		{
		    cat_m1_Status_BandAlert.bid = HAL_GetUIDw2();
		    cat_m1_Status_BandAlert.type = 2;
		    cat_m1_Status_BandAlert.value = 1;
		    send_Status_BandAlert(&cat_m1_Status_BandAlert);
		    lowBatteryAlertSent = true;
		}

		if (battVal >= 51)
		{
		    lowBatteryAlertSent = false;
		}
//		if (ssSCD == 3 || biosignalAlertSent)
//		{
//		    if (ssHr < 60 || ssHr > 100 || ssHr != 0 || ssSpo2 < 95 || ssSpo2 != 0)
//		    {
//		        ssHrSamples[sampleIndex] = ssHr;
//		        ssSpo2Samples[sampleIndex] = ssSpo2;
//		        sampleIndex = (sampleIndex + 1) % SAMPLE_COUNT;
//
//		        biosignalAlertSent = true;
//		        for (int i = 0; i < SAMPLE_COUNT; i++)
//		        {
//		            if ((ssHrSamples[i] >= 60 && ssHrSamples[i] <= 100) ||
//		                (ssSpo2Samples[i] >= 95 && ssSpo2Samples[i] <= 100))
//		            {
//		                biosignalAlertSent = false;
//		                break;
//		            }
//		        }
//
//		        if (ssSCD == 3)
//		        {
//		            scdStateCheckCount++;
//
//		            if (scdStateCheckCount >= 60)
//		            {
//		                if (biosignalAlertSent && cat_m1_Status.mqttChecking == 0)
//		                {
//		                    if (cat_m1_Status.gpsChecking)
//		                    {
//		                        nrf9160_Stop_gps();
//		                    }
//
//		                    cat_m1_Status_BandAlert.bid = deviceID;
//		                    cat_m1_Status_BandAlert.type = 4;
//		                    cat_m1_Status_BandAlert.value = 1;
//		                    catM1MqttDangerMessage = 1;
//		                    send_Status_BandAlert(&cat_m1_Status_BandAlert);
//		                    biosignalAlertSent = false;
//		                    memset(ssHrSamples, 0, sizeof(ssHrSamples));
//		                    memset(ssSpo2Samples, 0, sizeof(ssSpo2Samples));
//		                    sampleIndex = 0;
//
//		                    scdStateCheckCount = 0;
//		                    biosignalAlertSent = false;
//		                }
//		            }
//		        }
//		        else
//		        {
//		            scdStateCheckCount = 0;
//		        }
//		    }
//		    else
//		    {
//		        biosignalAlertSent = false;
//		        scdStateCheckCount = 0;
//		    }
//		}
	}
}

void mfioGPIOModeChange(GPIOMode mode){

	HAL_GPIO_DeInit(MFIO_PORT, MFIO_PIN);
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	switch(mode){
		case interrupt:
			GPIO_InitStruct.Pin = MFIO_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case output:
			GPIO_InitStruct.Pin = MFIO_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			break;
		case input:
			break;
		default:
			break;
	}

	HAL_GPIO_Init(MFIO_PORT, &GPIO_InitStruct);
}

//	ssInit();
//	ssBegin();
//	ssRead_setting();
uint8_t spo2Count = 0;
uint8_t hrCount = 0;
uint8_t pre_ppgMeasFlag = 0;
void measPPG(){
////	if (ppgMeasFlag == 0){
//		ssRunFlag = 0;
//
//		// start ppg
//		if(ppgMeaserCount % spo2MeaserPeriode_sec == 0){
////			mfioGPIOModeChange(output);
//			ssWalk_SUM = ssWalk; // total walk count ?��?�� ?��?��
//			ssBegin(0x00);
//			ssRead_setting();
//			spo2Flag = 1;
////			mfioGPIOModeChange(interrupt);
//		}
//		else if(ppgMeaserCount % hrMeaserPeriode_sec == 0){
////			mfioGPIOModeChange(output);
//			ssWalk_SUM = ssWalk; // total walk count ?��?�� ?��?��
//			ssBegin(0x02);
//			ssRead_setting();
//			hrFlag = 1;
////			mfioGPIOModeChange(interrupt);
//		}
//		else if(ppgMeaserCount == spo2MeaserPeriode_sec*hrMeaserPeriode_sec/60){
//			ppgMeaserCount = 1;
//		}
//
//		// stop ppg
//		if(spo2Flag){
//			spo2Count++;
//		}
//		if(hrFlag){
//			hrCount++;
//		}
//
//		if(spo2Count == 60){ // < spo2MeaserPeriode_sec = 60*5
//			ssWalk_SUM = ssWalk; // total walk count ?��?�� ?��?��
//			ssBegin(0x05);
//			ssRead_setting();
//			spo2Count = 0;
//			spo2Flag = 0;
//		}
//		if(hrCount == 30){ // < hrMeaserPeriode_sec = 60 * 1
//			ssWalk_SUM = ssWalk; // total walk count ?��?�� ?��?��
//			ssBegin(0x05);
//			ssRead_setting();
//			hrCount = 0;
//			hrFlag = 0;
//		}
//		ssRunFlag = 1;
////	}

	if(pre_ppgMeasFlag != ppgMeasFlag){
		if(ppgMeasFlag == 1){
			ppgMeaserCount++;
		} else {
			ppgMeaserCount = 1;
			ssWalk_SUM = ssWalk; // total walk count ?��?�� ?��?��
			ssBegin(0x05);
			ssRead_setting();
			hrCount = 0;
			spo2Count = 0;
		}
	}
	pre_ppgMeasFlag = ppgMeasFlag;
	return;
}

/**
 * @brief A �????????��?��?�� ?��?�� RTC ?���??????? ???��
 * @param startTime ???��?�� RTC ?���??????? 구조�???????
 */
void GetTimeAtA(RTC_TimeTypeDef *startTime, RTC_DateTypeDef *startDate) {
	extern RTC_HandleTypeDef hrtc;
    HAL_RTC_GetTime(&hrtc, startTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, startDate, RTC_FORMAT_BIN); // ?��짜도 ?���??????? ?��?��?�� ?���??????? 갱신 문제 방�?
}
// Function to convert RTC time and date to time_t
time_t convertRTCToTimeT(RTC_DateTypeDef* date, RTC_TimeTypeDef* time) {
    struct tm t = {0};
    t.tm_year = (date->Year + 2000) - 1900; // Adjust year to start from 1900
    t.tm_mon = date->Month - 1;            // tm_mon is 0-based
    t.tm_mday = date->Date;
    t.tm_hour = time->Hours;
    t.tm_min = time->Minutes;
    t.tm_sec = time->Seconds;
    return mktime(&t); // Convert to time_t
}

// Function to calculate if the difference between two RTC timestamps is within a threshold
double isDifferenceWithinThreshold(RTC_DateTypeDef* date1, RTC_TimeTypeDef* time1) {
    RTC_TimeTypeDef endTime;
    RTC_DateTypeDef endDate;

    GetTimeAtA(&endTime, &endDate);
    time_t time1_t = convertRTCToTimeT(date1, time1);
    time_t time2_t = convertRTCToTimeT(&endDate, &endTime);

    // Calculate absolute difference in seconds
    double difference = (time2_t - time1_t);
    if(difference >= 30) difference = 30;
    if(difference < 0) -1*difference;
    return difference;
}

double elapsedTime = 0;
bool StopModeState = false;
void Enter_StopMode(void) {
	// FreeRTOS ?��?��?�� 중단
	vTaskSuspendAll();

//	/**Enable the WakeUp => MX_RTC_Init();
//	32000 / 16 = 2000Hz
//	1sec = 2000Hz
//	1min = 120000
//	*/
//	extern RTC_HandleTypeDef hrtc;
//	HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 2000*RTC_WAKEUP_INTERVER_SEC, RTC_WAKEUPCLOCK_RTCCLK_DIV16, 0);

	HAL_TIM_Base_Stop_IT(&htim4);  // ppg
	HAL_TIM_Base_Stop_IT(&htim17); // sec
	HAL_TIM_Base_Stop_IT(&htim15); // us delay
	HAL_SuspendTick();

	// 모든 ?��?��?��?�� ?��?�� ???��
	portDISABLE_INTERRUPTS();

	// NVIC ?��?��?��?�� ?��?��
	HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);      // HOME_BTN_INT?��
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);
	HAL_NVIC_SetPriority(EXTI5_IRQn, 0, 0);      // SOS_BTN_INT?��
	HAL_NVIC_EnableIRQ(EXTI5_IRQn);
	HAL_NVIC_SetPriority(EXTI6_IRQn, 0, 0);      // CHARGING_INT?��
	HAL_NVIC_EnableIRQ(EXTI6_IRQn);
	HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);      // IMU_INT?��
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);

	HAL_NVIC_SetPriority(EXTI13_IRQn, 0, 0);      // TP_INT?��
	HAL_NVIC_EnableIRQ(EXTI13_IRQn);
	HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);      // RTC wakeup
	HAL_NVIC_EnableIRQ(RTC_IRQn);

//	extern RTC_HandleTypeDef hrtc;
//	if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 2000*(RTC_WAKEUP_INTERVER_SEC-elapsedTime), RTC_WAKEUPCLOCK_RTCCLK_DIV16, 0) != HAL_OK)
//	{
//		Error_Handler();
//	}

	// Stop 모드 진입
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);

	// Wake-up ?�� ?��?��?�� 복원
	extern void SystemClock_Config(void);
	SystemClock_Config();  // ?��?��?�� ?��?�� ?��?��?��
//	HAL_ResumeTick();

	HAL_NVIC_SetPriority(RTC_IRQn, 5, 0);      // RTC wakeup
	HAL_NVIC_EnableIRQ(RTC_IRQn);
	HAL_NVIC_SetPriority(EXTI13_IRQn, 5, 0);      // TP_INT?��
	HAL_NVIC_EnableIRQ(EXTI13_IRQn);

	HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);      // IMU_INT?��
	HAL_NVIC_EnableIRQ(EXTI3_IRQn);
	HAL_NVIC_SetPriority(EXTI6_IRQn, 5, 0);      // CHARGING_INT?��
	HAL_NVIC_EnableIRQ(EXTI6_IRQn);
	HAL_NVIC_SetPriority(EXTI5_IRQn, 5, 0);      // SOS_BTN_INT?��
	HAL_NVIC_EnableIRQ(EXTI5_IRQn);
	HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);      // HOME_BTN_INT?��
	HAL_NVIC_EnableIRQ(EXTI4_IRQn);

	portENABLE_INTERRUPTS();

	HAL_ResumeTick();
	HAL_TIM_Base_Start_IT(&htim15);
	HAL_TIM_Base_Start_IT(&htim17);
	HAL_TIM_Base_Start_IT(&htim4);

////	if (HAL_RTCEx_DeactivateWakeUpTimer(&hrtc) != HAL_OK)
////	{
////		int err = 1; //
////	}
//	extern uint8_t RTC_CallBack_Check;
//	if(RTC_CallBack_Check == 1){
//		RTC_CallBack_Check = 0;
//
//		// PPG 기능 ?��?��
//		ssRunFlag = 0;
////		osDelay(100);
//		ssBegin(0x00);
//		ssRead_setting();
//		spo2Flag = 1;
//		hrFlag = 1;
//		ssRunFlag = 1;
//
//		if(rtcAlarmEventCount % 2 == 0){
//			// CatM1, GNSS 기능 ?��?��
//		}
//		rtcAlarmEventCount++;
//
//		osDelay(60*1000);
//
//		// off PPG
//		ssRunFlag = 0;
////		osDelay(100);
//		ssBegin(0x05);
//		ssPause_setting();
//		ssRunFlag = 1;
//		// enter stop mode
//		backendStopModeEnterFlag = 1;
//	}
//
	xTaskResumeAll();
}

// frontend enter stopmode
void Enter_StopMode_LCD(void) {
//	lcdInitFlag = 0;

//	ssRunFlag = 0;
//
//    elapsedTime = isDifferenceWithinThreshold(&startDate, &startTime);
//    elapsedTime = 0;
//	for(uint8_t i = 0; i < (60*stopModeMin)/RTC_WAKEUP_INTERVER_SEC; i++){ // 5min period
//		extern uint8_t TP_INT;
//		TP_INT = 0;
//		Enter_StopMode();
//		elapsedTime = 0;
//		if(TP_INT == 1){ // TP_INT || HOME_BTN_INT || SOS_BTN_INT
//			TP_INT = 0;
//			break;
//		}
//	}
//	stopModeCount++; // 5min ++ => stopModeCount == even => catm1, gnss run
//	GetTimeAtA(&startTime, &startDate);

	StopModeState = true;

	ssRunFlag = 0;
	Enter_StopMode();

	StopModeState = false;

//	osDelay(100);
//    ssRunFlag = 1;

//	lcdInitFlag = 1;
}

/* USER CODE END Application */

