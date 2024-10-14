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

// Constants
#define MAX_CMD_LEN 100
#define MAX_VALUE_LEN 100
#define MAX_PARAMS_LEN 100
#define MAX_RESPONSE_LEN 256

#define ICCID_LEN 20

#define CAT_M1_UART_BUF_SIZE 512

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
  uint8_t gps[100];
  uint8_t time[30];
} cat_m1_at_cmd_rst_t;

typedef struct {
  uint8_t bid[10];
  uint8_t pid[2];
  uint8_t rssi[1];
  uint8_t start_byte[1];
  uint8_t hr[1];
  uint8_t spo2[1];
  uint8_t motionFlag[1];
  uint8_t scdState[1];
  uint8_t activity[1];
  uint8_t walk_steps[4];
  uint8_t run_steps[4];
  uint8_t temperature[1];
  uint8_t pres[4];
  uint8_t battery_level[1];
} cat_m1_Status_Band_t;

typedef struct {
  uint8_t hr_alert[1];
  uint8_t spo2_alert[1];
} cat_m1_Status_BandAler_t;

typedef struct {
  uint8_t type[1];
  uint8_t fall_detect[1];
} cat_m1_Status_FallDetection_t;

typedef struct {
  uint8_t lat[1];
  uint8_t lng[1];
  uint8_t alt[1];
  uint8_t accuracy[1];
  uint8_t speed[1];
  uint8_t heading[1];
} cat_m1_Status_GPS_Location_t;

typedef struct {
  int8_t acc_x[2];
  int8_t acc_y[2];
  int8_t acc_z[2];

  int8_t gyro_x[2];
  int8_t gyro_y[2];
  int8_t gyro_z[2];

  int8_t mag_x[2];
  int8_t mag_y[2];
  int8_t mag_z[2];
} cat_m1_Status_IMU_t;

typedef struct {
  uint8_t hr_min[1];
  uint8_t hr_max[1];
  uint8_t spo2_min[1];
  uint8_t spo2_max[1];
  uint8_t height[1];
  uint8_t weight[1];
} cat_m1_Status_BandSet_t;

typedef struct {
  uint8_t alert[1];
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

// nRF9160 Modem Interaction
void uart_init();
void nrf9160_init();
void nrf9160_ready();
void nrf9160_check();

void nrf9160_mqtt_setting();
void nrf9160_mqtt_test();
void test_send_json_publish();
void send_Status_Band(uint8_t* bid, uint8_t* pid, uint8_t* rssi,
                       uint8_t* start_byte, uint8_t* hr, uint8_t* spo2,
                       uint8_t* motionFlag, uint8_t* scdState, uint8_t* activity,
                       uint8_t* walk_steps, uint8_t* run_steps, uint8_t* temperature,
                       uint8_t* pres, uint8_t* battery_level);
void send_Status_BandAlert(uint8_t* bid, uint8_t* hr_alert, uint8_t* spo2_alert);
void send_Status_FallDetection(uint8_t* bid, uint8_t* type, uint8_t* fall_detect);
void send_GPS_Location(uint8_t* bid, uint8_t* lat, uint8_t* lng, uint8_t* alt, uint8_t* accuracy,
						uint8_t* speed, uint8_t* heading);
void send_Status_IMU(uint8_t* bid, uint8_t* acc_x, uint8_t* acc_y, uint8_t* acc_z,
		uint8_t* gyro_x, uint8_t* gyro_y, uint8_t* gyro_z,
		uint8_t* mag_x, uint8_t* mag_y, uint8_t* mag_z);

void nrf9160_Get_gps();
void nrf9160_Get_gps_State();
void nrf9160_Get_time();
void catM1PWRGPIOInit();

#endif /* CATM1_NRF9160_H_ */
