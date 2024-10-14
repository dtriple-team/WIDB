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
void send_json_publish(uint8_t shortAddress, uint8_t extAddressLow, uint8_t extAddressHigh,
		uint8_t capabilityInfoLow, uint8_t capabilityInfoHigh,
		uint8_t active, uint8_t pid,
		uint8_t ambienceTemp, uint8_t objectTemp, uint8_t rawData,
		uint8_t batteryLevel, uint8_t hrConfidence, uint8_t spo2Confidence,
		uint8_t hr, uint8_t spo2,
		uint8_t motionFlag, uint8_t scdState, uint8_t activity,
		uint8_t walkSteps, uint8_t runSteps, uint8_t x, uint8_t y, uint8_t z,
		uint8_t t, uint8_t h,
		uint8_t rssi, uint8_t reportingInterval, uint8_t pollingInterval);
void nrf9160_Get_gps();
void nrf9160_Get_gps_State();
void nrf9160_Get_time();
void catM1PWRGPIOInit();

#endif /* CATM1_NRF9160_H_ */
