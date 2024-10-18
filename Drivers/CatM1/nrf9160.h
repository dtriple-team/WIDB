/*
 * nrf9160.h
 *
 *  Created on: Oct 3, 2024
 *      Author: phb10
 */

#ifndef CATM1_NRF9160_H_
#define CATM1_NRF9160_H_

#include "stm32u5xx_hal.h"
#include <stdbool.h>

#include "cmsis_os2.h"

// Constants
#define MAX_CMD_LEN 100
#define MAX_VALUE_LEN 100
#define MAX_PARAMS_LEN 100
#define MAX_RESPONSE_LEN 256

#define ICCID_LEN 20

#define CAT_M1_UART_BUF_SIZE 512

typedef struct {
	uint8_t Checked;
    uint8_t parseCount;
    uint8_t parseResult;
    uint8_t bootCount;
    uint8_t errorCount;
    uint8_t retryCount;
    uint8_t cfunStatus;
    uint8_t systemModeStatus;
    uint8_t connectionStatus;
    uint8_t mqttSetStatus;
    uint8_t mqttConnectionStatus;
    uint8_t mqttSubscribeStatus;
    uint8_t gpsOn;
    uint8_t gpsOff;
    uint8_t mqttChecking;
    uint8_t gpsChecking;
} cat_m1_Status_t;

typedef struct {
  uint8_t head;
  uint8_t tail;
  uint8_t buffer[CAT_M1_UART_BUF_SIZE];
  uint8_t rxd;
  uint8_t temp;
  bool done;
} uart_cat_m1_t;

typedef struct {
  uint8_t buffer[MAX_RESPONSE_LEN];
  uint8_t cops[MAX_VALUE_LEN];
  uint8_t cgdcont[MAX_VALUE_LEN];
  uint8_t iccid[ICCID_LEN];
  uint8_t networkinfo[180];
  uint8_t cesq[100];
  uint8_t gps[100];
  uint8_t time[100];
  int  rssi;
} cat_m1_at_cmd_rst_t;

typedef struct {
  uint32_t bid;
  uint16_t pid;
  int  rssi;
  uint8_t start_byte;
  uint16_t hr;
  uint16_t spo2;
  uint8_t motionFlag;
  uint8_t scdState;
  uint8_t activity;
  uint32_t walk_steps;
  uint32_t run_steps;
  uint32_t temperature;
  uint32_t pres;
  uint8_t battery_level;
} cat_m1_Status_Band_t;

typedef struct {
  uint32_t bid;
  uint8_t hr_alert;
  uint8_t spo2_alert;
} cat_m1_Status_BandAler_t;

typedef struct {
  uint32_t bid;
  uint8_t type;
  uint8_t fall_detect;
} cat_m1_Status_FallDetection_t;

typedef struct {
  uint32_t bid;
} cat_m1_Status_GPS_Location_t;

typedef struct {
  uint32_t bid;
  int16_t acc_x;
  int16_t acc_y;
  int16_t acc_z;

  int16_t gyro_x;
  int16_t gyro_y;
  int16_t gyro_z;

  int16_t mag_x;
  int16_t mag_y;
  int16_t mag_z;
} cat_m1_Status_IMU_t;

typedef struct {
  uint32_t bid;
  uint8_t hr_min;
  uint8_t hr_max;
  uint8_t spo2_min;
  uint8_t spo2_max;
  uint8_t height;
  uint8_t weight;
} cat_m1_Status_BandSet_t;

typedef struct {
  uint32_t bid;
  uint8_t alert;
} cat_m1_Status_ServerAlert_t;

extern uart_cat_m1_t uart_cat_m1_rx;

void clear_uart_buf(uart_cat_m1_t* u);
void push(uart_cat_m1_t* u, uint8_t data);
uint8_t pop(uart_cat_m1_t* u);
uint8_t isEmpty(uart_cat_m1_t* u);

// External UART handle (replace huart1 with the appropriate UART handle if needed)
extern UART_HandleTypeDef huart1;

// UART Communication related functions
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
bool send_at_command(const char *cmd);
bool receive_at_command_ret(void);
bool receive_response(void);
bool cat_m1_parse_process(uint8_t *msg);
void cat_m1_parse_result(const char *command, const char *value);
void handle_cops_command(const char *value);
void handle_cfun_command(const char *value);
void handle_system_mode_command(const char *value);
void handle_mqtt_cfg_command(const char *value);
void handle_cgdcont_command(const char *value);
void handle_iccid_command(const char *value);
void handle_monitor_command(const char *value);
void handle_cesq_command(const char *value);
void handle_gps_command(const char *value);
void handle_mqtt_event_command(const char *value);
void handle_cclk_command(const char *value);

// nRF9160 Modem Interaction
void uart_init();
void nrf9160_clear_buf();
void nrf9160_init();
void nrf9160_ready();
void nrf9160_check();

void nrf9160_mqtt_setting();
void nrf9160_mqtt_test();
void test_send_json_publish();
void send_Status_Band(cat_m1_Status_Band_t *status);
void send_Status_BandAlert(cat_m1_Status_BandAler_t* alertData);
void send_Status_FallDetection(cat_m1_Status_FallDetection_t* fallData);
void send_GPS_Location(cat_m1_Status_GPS_Location_t* location);
void send_Status_IMU(cat_m1_Status_IMU_t* imu_data);

void nrf9160_Get_gps();
void nrf9160_Stop_gps();
void nrf9160_Get_gps_State();
void nrf9160_Get_rssi();
void nrf9160_Get_time();
void catM1Reset();
void catM1PWRGPIOInit();

#endif /* CATM1_NRF9160_H_ */
