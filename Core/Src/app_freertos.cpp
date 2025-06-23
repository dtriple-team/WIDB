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

extern "C" {
	#include "../../Drivers/q_cmd/command.h"
	#include "../../Drivers/q_cmd/queue.h"
}

//#include <gui_generated/initblackscreen_screen/initBlackScreenViewBase.hpp>
//#include <gui_generated/falldetected_screen/fallDetectedViewBase.hpp>
//#include <gui_generated/temphome_screen/tempHomeViewBase.hpp>
//#include <gui_generated/containers/batteryprogress_containerBase.hpp>
//#include <gui_generated/charging_screen_screen/charging_screenViewBase.hpp>
//#include <gui_generated/uncharging_screen_screen/unCharging_screenViewBase.hpp>
//#include <gui_generated/sos_alert_screen/sos_alertViewBase.hpp>
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

#define mqtt_operation_cycle 60*1
uint8_t mqttTime = 0;
bool mqttFlag = false;

#define mqtt_RetryTime_cycle 11
uint8_t UartRxRetryTime = 0;
bool UartRxRetryTimeFlag = false;

//int gps_operation_cycle  = 60*3;
int gps_operation_cycle  = 60*4;
//#define gps_operation_cycle 60*4
uint8_t gpsTime = 0;
bool gpsFlag = false;

#define gps_offCheck_cycle 180+10
uint8_t gpsOffCheckTime = 0;

int cell_location_operation_cycle  = 60*1;
uint8_t cell_locationTime = 0;
bool cell_locationFlag = true;

#define fall_Check_cycle 0 // falling event occure => after N sec => MQTT // 60
uint8_t fallCheckTime = 0;
uint8_t fallCheckFlag = 0;

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

float falling_threshold = 1.0; // ?��?�� ?���???????? 기�? ?��?�� 차이

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
  .stack_size = 512 * 4,
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
uint8_t set_bLevel = 1; // GUI val ?��?�� // 7
uint8_t before_bLevel = set_bLevel;
uint8_t flashlightOn = 0;

uint8_t lteRSSI_0_4 = 0; // CATM1 signal RSSI 0 to 4 value
uint8_t gpsRSSI_0_1 = 0;

//initBlackScreenViewBase myBlackScreenView;
//fallDetectedViewBase myFallDetectedView;
//tempHomeViewBase myTempHomeView;
//sos_alertViewBase mySOSAlertViewBase;

extern uint8_t occurred_imuInterrupt;
extern uint8_t occurred_PMICBUTTInterrupt;

void mfioGPIOModeChange(GPIOMode mode);
void measPPG(void);

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

	cat_m1_Status_Rtt_Gps_t gpsStatus = {
		.bid = 0,                // Set the bid value to 12345
		.svData01 = {0},                 // Initialize 'data' array to zero
		.svData02 = {0},                 // Initialize 'data' array to zero
		.svData03 = {0},                 // Initialize 'data' array to zero
		.svData04 = {0},                 // Initialize 'data' array to zero
		.svData05 = {0},                 // Initialize 'data' array to zero
		.svData06 = {0},                 // Initialize 'data' array to zero
		.svData07 = {0},                 // Initialize 'data' array to zero
		.svData08 = {0},                 // Initialize 'data' array to zero
		.svData09 = {0},                 // Initialize 'data' array to zero
		.svData10 = {0},                 // Initialize 'data' array to zero
		.svData11 = {0},                 // Initialize 'data' array to zero
		.svData12 = {0},                 // Initialize 'data' array to zero
		.svData13 = {0},                 // Initialize 'data' array to zero
		.svData14 = {0},                 // Initialize 'data' array to zero
		.svData15 = {0},                 // Initialize 'data' array to zero
		.svData16 = {0},                 // Initialize 'data' array to zero
		.svData17 = {0},                 // Initialize 'data' array to zero
		.svData18 = {0},                 // Initialize 'data' array to zero
		.svData19 = {0},                 // Initialize 'data' array to zero
		.svData20 = {0},                 // Initialize 'data' array to zero
		.svData21 = {0},                 // Initialize 'data' array to zero
		.svData22 = {0},                 // Initialize 'data' array to zero
		.svData23 = {0},                 // Initialize 'data' array to zero
		.svData24 = {0},                 // Initialize 'data' array to zero
		.svData25 = {0},                 // Initialize 'data' array to zero
		.svData26 = {0},                 // Initialize 'data' array to zero
		.svData27 = {0},                 // Initialize 'data' array to zero
		.svData28 = {0},                 // Initialize 'data' array to zero
		.svData29 = {0},                 // Initialize 'data' array to zero
		.svData30 = {0},                 // Initialize 'data' array to zero
		.svData31 = {0},                 // Initialize 'data' array to zero
		.svData32 = {0},                 // Initialize 'data' array to zero
		.GPGGA = {0},     // Initialize 'GPGGA' with some sample string (up to 100 characters)
		.GPGLL = {0},     // Initialize 'GPGLL' with some sample string
		.GPGSA = {0},     // Initialize 'GPGSA' with some sample string
		.GPGSV = {0},     // Initialize 'GPGSV' with some sample string
		.GPRMC = {0},      // Initialize 'GPRMC' with some sample string
	};

	for(;;){
		// haptic
		if(cat_m1_Status_FallDetection.fall_detect == 1){
			if(hapticFlag == 1){
				runHaptic(20, 500, 3);
			}
			brightness_count = 0; // lcd backlight count reset
		}
		if(beforeHaptic != hapticFlag){ // toggle haptic BTN
			beforeHaptic = hapticFlag;
			if(hapticFlag == 1){
				runHaptic(20, 500, 1);
			}
		}
		if(haptic_SOS == 1){
			if(hapticFlag == 1){
				runHaptic(20, 500, 3);
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
	pmic_init();
	pmicInitFlag = 1;

	while(!pmicInitFlag){
		osDelay(10);
	}
	runHaptic(20, 500, 1); // turn on device haptic
//	HAL_Delay(5000); // ?���???????? ?��?�� + ?��버거 ?���???????? ?���????????
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

	osDelay(5000);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
	osDelay(10);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);

  /* Infinite loop */
  for(;;)
  {
//    osDelay(10);

//	  extern bool uartRXFinish;
//	  extern uint16_t uart_rx_count;
//	  if(uartRXFinish == 1){
//		  extern UART_HandleTypeDef huart2;
//	//    uint32_t* rx_data = &(uart_cat_m1_rx.buffer[uart_cat_m1_rx.tail]);
//		  HAL_UART_Transmit(&huart2, &(uart_cat_m1_rx.buffer[uart_cat_m1_rx.tail]), uart_rx_count, HAL_MAX_DELAY);
//		  uart_rx_count = 0;
//	  }

	  command_queue_handler();
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

	extern BAND_STATE now_band_state;

	nrf9160_init();
	nrf9160_clear_buf();
	catM1PWRGPIOInit();
	HAL_Delay(1000);

//	nrf9160_ready();
//	nrf9160_check();
//	nrf9160_mqtt_setting();

    send_at_command("AT+CFUN=0\r\n");
    send_at_command("AT+COPS=1,2,\"45008\"\r\n");
    send_at_command("AT%XSYSTEMMODE=1,0,1,0\r\n");
    send_at_command("AT+CPSMS=1,,,\"00000001\",\"00000011\"\r\n");
    send_at_command("AT+CEDRXS=2,4,\"0011\"\r\n");
    osDelay(1000);
    send_at_command("AT%XSYSTEMMODE?\r\n");
    send_at_command("AT+CFUN=1\r\n");
    send_at_command("AT+COPS?\r\n");

  /* Infinite loop */
  for(;;)
  {
	  switch(now_band_state){
	  case GPS_INIT_STATE:
		  now_band_state = GPS_STATE;
		  break;
	  case GPS_STATE:
		  nrf9160_Get_gps();
		  break;
	  case CATM1_INIT_STATE:
		  nrf9160_Stop_gps();

		    send_at_command("AT+CFUN=0\r\n");
		    send_at_command("AT+COPS=1,2,\"45008\"\r\n");
		    send_at_command("AT%XSYSTEMMODE=1,0,1,0\r\n");
		    send_at_command("AT+CPSMS=0,,,\"00000001\",\"00000011\"\r\n");
		    send_at_command("AT+CEDRXS=2,4,\"0011\"\r\n");
		    osDelay(1000);
		    send_at_command("AT%XSYSTEMMODE?\r\n");
		    send_at_command("AT+CFUN=1\r\n");
		    send_at_command("AT+COPS?\r\n");

		  now_band_state = CATM1_STATE;
		  break;
	  case CATM1_STATE:
		  nrf9160_Get_rssi();
		  if(cat_m1_Status_Band.rssi == -255){
			  now_band_state = CATM1_INIT_STATE;
		  }
		  osDelay(1000);
		  break;
	  default:
		  now_band_state = GPS_INIT_STATE;
		  break;
	  }
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
// �?????????��?�� ?��?��?�� 구조�????????
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
		return 1; // ?��?��?���???????? 감�?
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
		return 1; // ?��?��?���???????? 감�?
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

  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END spmTask */
}

/* USER CODE BEGIN Header_StartSecTimerTask */
/**
* @brief Function implementing the secTimerTask thread.
* @param argument: Not used
* @retval None
*/
//int start_count = 0;
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

	uint8_t pre_secTime = 0;
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

	// screenOnTime == brightness_count�?????????????? ?���?????????????? ?���?????????????? 꺼라
	// brightness_count == 0?���?????????????? 바�?�면 백라?��?���?????????????? 켜라
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
//batteryprogress_containerBase myBatteryprogress_container;
//charging_screenViewBase myCharging_screenView;
//unCharging_screenViewBase myUnCharging_screenView;
uint8_t interrupt_kind = 0;
#define PRESSURE_VAL_LEN 10
#include <math.h>
unsigned char batterylevel;
double calculateAltitudeDifference(double P1, double P2) {
    const double R = 8.314;       // 기체 ?��?�� (J/(mol·K))
    const double T = 273.15+25;   // ?���???????????? ?��?�� (K) - ?���???????????? ??�???????????? 조건 15°C
    const double g = 9.80665;     // 중력 �?????????????��?�� (m/s²)
    const double M = 0.02896;     // 공기?�� �???????????? 질량 (kg/mol)

    double altitudeDifference = (R * T) / (g * M) * log(P1 / P2);

    return altitudeDifference;
}
uint8_t temp_blevel = 0;
//uint8_t updateBattVal(){
//	uint8_t batt = 0;
//	return batt;
//}
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
    extern uint8_t occurred_HOMEBTNInterrupt;
    if(occurred_HOMEBTNInterrupt == 1){
    	occurred_HOMEBTNInterrupt = 0;
    	brightness_count = 0;
    	if(flashlightOn){
    		flashlightOn = 0;
    		set_bLevel = before_bLevel; // turn off flash light : brightness
    	}
//    	myTempHomeView.changeToHomeScreen();

//    	ST7789_brightness_setting(before_bLevel);
    	if(temp_blevel == 15) temp_blevel = 0;
    	ST7789_brightness_setting(temp_blevel++);

    	// cat_m1_Status_FallDetection.fall_detect = 0;
    	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));

    	fallCheckTime = 0;

#if defined(nRF9160_Fall_Difference_Value_Send)
    	magnitude = 0;
#endif
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
//					myCharging_screenView.changeChargeScreen();
			    	brightness_count = 0;
			    	ppgMeasFlag = 0;
				}
				else{
//					myBatteryprogress_container.batteryNotCharging();
//					myUnCharging_screenView.changeUnChargeScreen();
			    	brightness_count = 0;
			    	ppgMeasFlag = 1;
				}
			}
		}
		else if(battVal == 100 && isCharging == true){ // charging finish
			isCharging = false;
//			myUnCharging_screenView.changeUnChargeScreen();
	    	brightness_count = 0;
		}
    }
/*
    // PMIC interrupt occur => emergency signal send to Web (CATM1)
    if(occurred_PMICBUTTInterrupt){
    	if (cat_m1_Status.gpsChecking)
    	{
    	nrf9160_Stop_gps();
    	}
    	// change screen
		before_bLevel = set_bLevel;
		ST7789_brightness_setting(16);
		brightness_count = 0;
//    	mySOSAlertViewBase.changeToSOSDetected();
    	// haptic
    	haptic_SOS = 1;
    	// send SOS MQTT
    	cat_m1_Status_BandAlert.bid = deviceID;
		cat_m1_Status_BandAlert.type = 6;
		cat_m1_Status_BandAlert.value = 1;
		send_Status_BandAlert(&cat_m1_Status_BandAlert);
		catM1MqttDangerMessage = 1;

    	occurred_PMICBUTTInterrupt = 0;
    }
*/
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
	extern bool uartRXFinish;
  /* Infinite loop */
  for(;;)
  {
	  receive_response();// Cat-M1 Buffer parsing
	 osDelay(1);
  }
  /* USER CODE END dataTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

