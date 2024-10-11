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
void uart_init(void);
void nrf9160_init(void);
void nrf9160_ready(void);
void nrf9160_check(void);

void nrf9160_mqtt_setting(void);
void nrf9160_mqtt_test(void);
void test_send_json_publish(void);
void send_json_publish(int shortAddress, unsigned long extAddressLow, unsigned long extAddressHigh,
                             unsigned long capabilityInfoLow, unsigned long capabilityInfoHigh,
                             bool active, const char *pid,
                             int ambienceTemp, int objectTemp, int rawData,
                             int batteryLevel, int hrConfidence, int spo2Confidence,
                             int hr, int spo2,
                             int motionFlag, int scdState, int activity,
                             int walkSteps, int runSteps, int x, int y, int z,
                             unsigned long t, unsigned long h,
                             int rssi, int reportingInterval, const char *pollingInterval);

void catM1PWRGPIOInit(void);

#endif /* CATM1_NRF9160_H_ */
