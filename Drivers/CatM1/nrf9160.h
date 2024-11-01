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

// CA Certificate
#define caCert "AT%CMNG=0,16842753,0,\"-----BEGIN CERTIFICATE-----\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\nADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\nb24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\nMAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\nb3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\nca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\nIFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\nVOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\njgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\nAYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\nA4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\nU5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\nN+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\no/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\nrqXRfboQnoZsG4q5WTP468SQvvG5\n-----END CERTIFICATE-----\n\"\r\n"

// Client Certificate
#define clientCert "AT%CMNG=0,16842753,1,\"-----BEGIN CERTIFICATE-----\nMIICuDCCAaACCQD1sW5ydunD5DANBgkqhkiG9w0BAQsFADBsMQswCQYDVQQGEwJO\nTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNVBAoM\nFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4Yjkw\nMCAXDTI0MTAzMTA3MDA0OVoYDzIwNTQxMDI0MDcwMDQ5WjCBmDELMAkGA1UEBhMC\nTk8xEjAQBgNVBAgMCVRyb25kZWxhZzESMBAGA1UEBwwJVHJvbmRoZWltMSEwHwYD\nVQQKDBhOb3JkaWMgU2VtaWNvbmR1Y3RvciBBU0ExLTArBgNVBAMMJDUwNGU1NzM3\nLTMyMzUtNDg2YS04MGYwLTBhMmMyZjZiOTgxMjEPMA0GA1UELhMGMTIzNDU2MFkw\nEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAEXRdzwrmYtdN35/hLfa2lrUaqWshnl9pH\nKHy8GorLFzQNrqmlVFANXtTUGeRaCG7eMcDqLsuKxtTa0kcJ0QqkLTANBgkqhkiG\n9w0BAQsFAAOCAQEAoKRJCyJK2GN6kGlRcRRJPjEw2GeGwaIuXWGYzrrthHUWzqao\niJQY3OGFhiNyu1q1T4oym6Y5bJTEt95aIs0C/p81H2KslBraO6Tkbd2gonUP3GPL\nIBUBrpnEd95RfSgYU5PdOpFtGOKk0BjI8BTe4I0ml09W6JUHLiznUg75VQoDq/8e\nHVzJ7ypxG1GX0GmaAzi/N3CEwmucScOEMWGOfGkb8tfC9Qzz8ffTuKm3Fpiefd9j\nGHMLN8CpEswmAD75YcbcAkvy8/uUG4gDxQldNwqswnJLxQVjEUr9YPcTTsHhCl62\nx1vNvcAGm31e1qMT+R80VbhzzHOCP+jERc9wQw==\n-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----\nMIIDqzCCApOgAwIBAgIJAOXo6/ALtz+gMA0GCSqGSIb3DQEBCwUAMGwxCzAJBgNV\nBAYTAk5PMQ8wDQYDVQQIDAZOb3J3YXkxEjAQBgNVBAcMCVRyb25kaGVpbTEdMBsG\nA1UECgwUTm9yZGljIFNlbWljb25kdWN0b3IxGTAXBgNVBAsMEEdlbmVyaWMtMTRh\nMThiOTAwHhcNMjMwMzE2MDMzODAwWhcNMjYwMTAzMDMzODAwWjBsMQswCQYDVQQG\nEwJOTzEPMA0GA1UECAwGTm9yd2F5MRIwEAYDVQQHDAlUcm9uZGhlaW0xHTAbBgNV\nBAoMFE5vcmRpYyBTZW1pY29uZHVjdG9yMRkwFwYDVQQLDBBHZW5lcmljLTE0YTE4\nYjkwMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA2CE46Te7DvZxfauo\nCZhNGpvJ/RNP5cfunU3qnzhpnpDwbgMT8lU2zMe14kolzNr2LQN09EYSDmBYh5je\nszKUT1FKKvMAs59UnPrdLiwWG6tWhfa5CzsNgMi+TjGcqK8K7D+Gv+b7EzDqtYFM\ng5FovJE6wYO/DIHRq7dVa21B3GB2vqiQZCXuef8kc1NCAXFm2MX5lkV6MQxyXYBo\nV8+/jNTiXSriGFJVG6MvF4lRTKC0TTV2NBFaJmRDwEuBoUSpbNoNDhhNOm+kbVBH\nlfXP81YwNOl+RVNbjGmA2lG3SEf/42jsCiaKjXp1cozF+EKGI8/H7ryMyoq0a3dG\nEFy7zwIDAQABo1AwTjAdBgNVHQ4EFgQU8QcvSXGLHmKmu6LrgIobANmjQ6IwHwYD\nVR0jBBgwFoAU8QcvSXGLHmKmu6LrgIobANmjQ6IwDAYDVR0TBAUwAwEB/zANBgkq\nhkiG9w0BAQsFAAOCAQEAAuXJuAx2BBDh44ljxqQsfLfhDNN3J8LZeoG5wbcSKQw6\nXCBp4BO/oeL8SWZ8G7WmTIxxpWyf5wBEvVGqmUnKj+skRXKVsHon63+ihomGDZTM\nb+lsPJFH0XYvmFhYhRMnDJC5FVyhsyRloyWgmRcsFoXqlkySPD8qN7/EXvHdcQwI\nB4d6mfcN9943Oywh72GdlMPxvmdBsOoRDP46Hb8NoVlEcgvNT4SWfjh6AHZiqO5r\n2NOCvvbO8S2r1NzCXBuBPtm5dY/hmbZOCiTBnK7SX6Aol24rVH7vuYOW0iLv30O2\nqke6pyCrthgdokfe2kd94L/Saos6cR8phmH5SqkZFg==\n-----END CERTIFICATE-----\n\"\r\n"
// Private Key
#define privateKey "AT%CMNG=0,16842753,2,\"-----BEGIN EC PARAMETERS-----\nBggqhkjOPQMBBw==\n-----END EC PARAMETERS-----\n-----BEGIN EC PRIVATE KEY-----\nMHcCAQEEICMiomLbCf+AFeIpfO29mhTk+pEyxj4XEMDauVLrwxZpoAoGCCqGSM49\nAwEHoUQDQgAEXRdzwrmYtdN35/hLfa2lrUaqWshnl9pHKHy8GorLFzQNrqmlVFAN\nXtTUGeRaCG7eMcDqLsuKxtTa0kcJ0QqkLQ==\n-----END EC PRIVATE KEY-----\n\"\r\n"

// MQTT Topic
#define NEW_BAND_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/Band\"\r\n"
#define	OLD_BAND_TOPIC "AT#XMQTTPUB=\"/efwb/post/sync\"\r\n"

#define NEW_BANDALERT_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/BandAlert\"\r\n"
#define OLD_BANDALERT_TOPIC "AT#XMQTTPUB=\"/efwb/post/async\"\r\n"

#define NEW_FALLDETECTION_TOPIC "AT#XMQTTPUB=\"/DT/eHG4/Status/FallDetection\"\r\n"
#define OLD_FALLDETECTION_TOPIC "AT#XMQTTPUB=\"/efwb/post/async\"\r\n"

#define IMU_TOPIC 			"AT#XMQTTPUB=\"/DT/eHG4/Status/IMU\"\r\n"
#define GPS_LOCATION_TOPIC	"AT#XMQTTPUB=\"/DT/eHG4/GPS/Location\"\r\n"

#define UUID_TOPIC	"AT#XMQTTPUB=\"/DT/eHG4/UUID\"\r\n"

#define SUB_STATUS_BANDSET 	"AT#XMQTTSUB=\"/DT/test_eHG4/Status/BandSet\",0\r\n"
#define SUB_SERVER_ALERT	"AT#XMQTTSUB=\"/DT/eHG4/Status/ServerAlert\",0\r\n"

typedef enum {
    WPM_INIT_CHECK,
    WPM_INIT_COMPLETE
} WpmState;

typedef enum {
    SYSTEM_MODE_CHECK,
    CFUN_CHECK,
    CONNECTION_CHECK,
    FINAL_COMMANDS,
    CHECK_COMPLETE
} CheckState;

typedef enum {
    MQTT_INIT,
    MQTT_CONFIG,
    MQTT_CONNECT,
    MQTT_SUBSCRIBE_STATUS,
    MQTT_SUBSCRIBE_ALERT,
    MQTT_COMPLETE
} MqttState;

typedef enum {
    GPS_INIT,
    GPS_SYSTEM_MODE,
    GPS_CFUN,
    GPS_ON,
    GPS_COMPLETE
} GpsState;

// Constants
#define MAX_CMD_LEN 100
#define MAX_VALUE_LEN 100
#define MAX_PARAMS_LEN 100
#define MAX_RESPONSE_LEN 256

#define ICCID_LEN 21

#define CAT_M1_UART_BUF_SIZE 512

typedef struct {
	uint8_t txflag;
	uint8_t InitialLoad;
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
  uint8_t uuid[100];
  int altitude;
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
  int pres;
  uint8_t battery_level;
} cat_m1_Status_Band_t;

typedef struct {
  uint32_t bid;
//  uint8_t hr_alert;
//  uint8_t spo2_alert;
  uint8_t type;
  uint8_t value;
} cat_m1_Status_BandAlert_t;

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
} cat_m1_Status_uuid_t;

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

typedef struct{
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
}catM1Time;

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
void handle_cell_location_command(const char *value);
void handle_mqtt_event_command(const char *value);
void handle_cclk_command(const char *value);
void handle_xuuid_command(const char *value);

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
void send_Status_BandAlert(cat_m1_Status_BandAlert_t* alertData);
void send_Status_FallDetection(cat_m1_Status_FallDetection_t* fallData);
void send_GPS_Location(cat_m1_Status_GPS_Location_t* location);
void send_Status_IMU(cat_m1_Status_IMU_t* imu_data);
void send_UUID(cat_m1_Status_uuid_t* uuid);

void nrf9160_Get_gps();
void nrf9160_Stop_gps();
void nrf9160_Get_gps_State();
void nrf9160_Get_rssi();
void nrf9160_Get_time();
void catM1Reset();
void catM1nRFCloud_Init();
void catM1PWRGPIOInit();

void nrf9160_Get_cell_location();

catM1Time getCatM1Time(void);

#endif /* CATM1_NRF9160_H_ */
