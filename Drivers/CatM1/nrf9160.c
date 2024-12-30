/*
 * nrf9160.c
 *
 *  Created on: Oct 3, 2024
 *      Author: phb10
 */

#include <nrf9160.h>
#include "stm32u5xx_hal.h"
#include <main.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define MINMEA_MAX_SENTENCE_LENGTH 256

uint8_t uart_cat_m1_buf[MINMEA_MAX_SENTENCE_LENGTH] = {0, };

cat_m1_Status_t cat_m1_Status;
uart_cat_m1_t uart_cat_m1_rx;
cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
cat_m1_Status_Band_t cat_m1_Status_Band;
cat_m1_Status_BandAlert_t cat_m1_Status_BandAlert;
cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection;
cat_m1_Status_GPS_Location_t cat_m1_Status_GPS_Location;
cat_m1_Status_IMU_t cat_m1_Status_IMU;
cat_m1_Status_BandSet_t cat_m1_Status_BandSet;
cat_m1_Status_uuid_t cat_m1_Status_uuid;
cat_m1_Status_Fall_Difference_Value_t cat_m1_Status_Fall_Difference_Value;

WpmState currentWpmState = WPM_INIT_CHECK;
CheckState currentCheckState = SYSTEM_MODE_CHECK;
MqttState currentMqttState = MQTT_INIT;
GpsState gpsState = GPS_INIT;

extern uint8_t nRFCloudFlag;
extern bool cell_locationFlag;
extern uint8_t wpmInitializationFlag;
extern uint8_t gpsOffCheckTime;
extern uint8_t UartRxRetryTime;
extern bool gpsFlag;
extern int gps_operation_cycle;
extern uint32_t deviceID;
extern uint8_t deviceID_check;
extern uint8_t gpsRSSI_0_1;

bool txCompleteFlag = 0;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        txCompleteFlag = 1;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
    	push(&uart_cat_m1_rx, uart_cat_m1_rx.temp);
    	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
    }
}

void clear_uart_buf(uart_cat_m1_t*u)
{
  u->head = 0;
  u->tail = 0;
  memset(u->buffer, 0, sizeof(u->buffer));
}

void push(uart_cat_m1_t* u, uint8_t data)
{
  u->buffer[u->head] = data;

  u->head++;

  if (u->head >= CAT_M1_UART_BUF_SIZE)
  {
    u->head = 0;
  }
}

uint8_t pop(uart_cat_m1_t* u)
{
  uint8_t data = u->buffer[u->tail];

  u->tail++;

  if (u->tail >= CAT_M1_UART_BUF_SIZE)
  {
    u->tail = 0;
  }
  return data;
}

uint8_t isEmpty(uart_cat_m1_t* u)
{
  return u->head == u->tail;
}


bool send_at_command(const char *cmd)
{
    cat_m1_Status.txflag = 1;
    txCompleteFlag = 0;

    HAL_UART_Transmit_IT(&huart1, (uint8_t*)cmd, strlen(cmd));
    //PRINT_INFO("TX CMD >>> %s\r\n", cmd);

    while (txCompleteFlag == 0)
    {

    }

    return receive_at_command_ret();
}

bool receive_at_command_ret()
{
//	if (strstr(&uart_cat_m1_rx, str) != NULL)
//    {
//        //PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
//        return true;
//    }
	if(cat_m1_Status.parseResult)
	{
		return true;
	}
	else if(cat_m1_Status.parseResult == 0)
	{
		return false;
	}
	return false;
}

bool receive_response(void)
{
    if (isEmpty(&uart_cat_m1_rx) == 0)
    {
    	cat_m1_Status.txflag = 0;
        uart_cat_m1_rx.rxd = pop(&uart_cat_m1_rx);

        if (uart_cat_m1_rx.rxd == '\r' || uart_cat_m1_rx.rxd == '\n')
        {
            uart_cat_m1_buf[cat_m1_Status.parseCount] = uart_cat_m1_rx.rxd;
            cat_m1_Status.parseCount++;

            //PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
            cat_m1_parse_process(uart_cat_m1_buf);

            memset(&uart_cat_m1_buf, 0, MINMEA_MAX_SENTENCE_LENGTH);
            cat_m1_Status.parseCount = 0;
        } else
        {
            if (cat_m1_Status.parseCount < MINMEA_MAX_SENTENCE_LENGTH - 1) {
                uart_cat_m1_buf[cat_m1_Status.parseCount] = uart_cat_m1_rx.rxd;
                cat_m1_Status.parseCount++;
            }
        }
    }
    return true;
}

bool cat_m1_parse_process(uint8_t *msg) {
    if (!msg) return false;

    char command[MAX_CMD_LEN] = {0};
    char value[MAX_VALUE_LEN] = {0};

    char *colon_pos = strchr((char *)msg, ':');

    if (colon_pos) {
        size_t cmd_len = colon_pos - (char *)msg;
        strncpy(command, (char *)msg, cmd_len < MAX_CMD_LEN ? cmd_len : MAX_CMD_LEN - 1);
        command[cmd_len < MAX_CMD_LEN ? cmd_len : MAX_CMD_LEN - 1] = '\0';

        colon_pos++;
        int i = 0;
        while (i < MAX_VALUE_LEN - 1 && strncmp(colon_pos, "OK", 2) != 0 &&
               strncmp(colon_pos, "ERROR", 5) != 0 && strncmp(colon_pos, "Ready", 5) != 0) {
            if (*colon_pos == '\0' || *colon_pos == '\r' || *colon_pos == '\n') break;
            value[i++] = *colon_pos++;
        }
        value[i] = '\0';

        cat_m1_parse_result(command, value);

        if (strstr(command, "%XICCID") != NULL){
        	if(sizeof(value) < 20){
        		send_at_command("AT%XICCID\r\n");
        	}
        }

    } else {
        if (strstr((char *)msg, "Ready")) {
            PRINT_INFO("Response: Ready\r\n");
            cat_m1_Status.parseResult = 1;
            cat_m1_Status.bootCount++;
            cat_m1_Status.retryCount = 0;
            wpmInitializationFlag = 1;

            PRINT_INFO("cat_m1_Status.bootCount >>> %d\r\n", cat_m1_Status.bootCount);
            if (cat_m1_Status.bootCount >= 2) {
                catM1Reset();
            }
        } else if (strstr((char *)msg, "OK")) {
            PRINT_INFO("Response: OK\r\n");
            cat_m1_Status.parseResult = 1;
            cat_m1_Status.errorCount = 0;
            cat_m1_Status.retryCount = 0;
            wpmInitializationFlag = 1;
        } else if (strstr((char *)msg, "ERROR")) {
            PRINT_INFO("Response: ERROR\r\n");
            cat_m1_Status.parseResult = 0;
            cat_m1_Status.errorCount++;
            if (cat_m1_Status.errorCount >= 10) {
                catM1Reset();
            }
        }
    }
    return false;
}

void cat_m1_parse_result(const char *command, const char *value)
{
	//PRINT_INFO("Command: %s\r\n", command);
	//PRINT_INFO("Value: %s\r\n", value);

	if (!command || !value)
    	return;

    if (strstr(command, "+COPS") != NULL)
    {
        handle_cops_command(value);
    }
    else if (strstr(command, "+CFUN") != NULL)
    {
        handle_cfun_command(value);
    }
    else if (strstr(command, "%XSYSTEMMODE") != NULL)
    {
        handle_system_mode_command(value);
    }
    else if (strstr(command, "#XMQTTCFG") != NULL)
    {
        handle_mqtt_cfg_command(value);
    }
    else if (strstr(command, "+CGDCONT") != NULL)
    {
        handle_cgdcont_command(value);
    }
    else if (strstr(command, "%XICCID") != NULL)
    {
        handle_iccid_command(value);
    }
    else if (strstr(command, "%XMONITOR") != NULL)
    {
        handle_monitor_command(value);
    }
    else if (strstr(command, "+CESQ") != NULL)
	{
		handle_cesq_command(value);
	}
    else if (strstr(command, "#XGPS") != NULL)
    {
        handle_gps_command(value);
    }
    else if (strstr(command, "#XMQTTEVT") != NULL)
    {
        handle_mqtt_event_command(value);
    }
    else if (strstr(command, "+CCLK") != NULL)
    {
        handle_cclk_command(value);
    }
    else if (strstr(command, "#XNRFCLOUDPOS") != NULL)
    {
    	handle_cell_location_command(value);
    }
    else if (strstr(command, "#XUUID") != NULL)
    {
    	handle_xuuid_command(value);
    }
    else if (strstr(command, "+CNUM") != NULL)
    {
    	handle_cnum_command(value);
    }
}

void handle_cops_command(const char *value)
{
    int cops_length = strlen(value);
    cat_m1_Status.connectionStatus = (cops_length > 5) ? 1 : 0;
    strncpy((char *)cat_m1_at_cmd_rst.cops, (const char *)value, MAX_VALUE_LEN - 1);
    cat_m1_at_cmd_rst.cops[MAX_VALUE_LEN - 1] = '\0';
}

void handle_cfun_command(const char *value)
{
	cat_m1_Status.cfunStatus = (strstr(value, "1") != NULL) ? 1 : 0;
}

void handle_system_mode_command(const char *value)
{
    if (strstr(value, "1,0,0,0") != NULL)
    {
    	cat_m1_Status.systemModeStatus = 1;
    }
    else if (strstr(value, "0,0,1,0") != NULL)
    {
    	cat_m1_Status.systemModeStatus = 2;
    }
    else if (strstr(value, "1,0,1,0") != NULL)
    {
    	cat_m1_Status.systemModeStatus = 3;
    }
}

void handle_mqtt_cfg_command(const char *value)
{
    int mqttcfg_length = strlen(value);
    cat_m1_Status.mqttSetStatus = (mqttcfg_length > 5) ? 1 : 0;
}

void handle_cgdcont_command(const char *value)
{
	strncpy((char *)cat_m1_at_cmd_rst.cgdcont, (const char *)value, MAX_VALUE_LEN - 1);
	cat_m1_at_cmd_rst.cgdcont[MAX_VALUE_LEN - 1] = '\0';
}

void handle_iccid_command(const char *value)
{
    for (int i = 0; i < ICCID_LEN - 1 && value[i] != '\0'; i++) {
        cat_m1_at_cmd_rst.iccid[i] = value[i];
    }
    cat_m1_at_cmd_rst.iccid[ICCID_LEN - 1] = '\0';

    if (!deviceID_check)
    {
        char iccid9[10];
        for (int i = 0; i < 9; i++) {
            iccid9[i] = cat_m1_at_cmd_rst.iccid[11 + i];
        }
        iccid9[9] = '\0';

        deviceID = (uint32_t)strtol(iccid9, NULL, 10);
        PRINT_INFO("deviceID >>> %u\r\n", (unsigned int)deviceID);
        HAL_Delay(250);
        deviceID_check = 1;
    }
}

void handle_monitor_command(const char *value)
{
    strncpy((char *)cat_m1_at_cmd_rst.networkinfo, (const char *)value, sizeof(cat_m1_at_cmd_rst.networkinfo) - 1);
    cat_m1_at_cmd_rst.networkinfo[sizeof(cat_m1_at_cmd_rst.networkinfo) - 1] = '\0';
}

void handle_cesq_command(const char *value)
{
    strncpy((char *)cat_m1_at_cmd_rst.cesq, (const char *)value, sizeof(cat_m1_at_cmd_rst.cesq) - 1);
    cat_m1_at_cmd_rst.cesq[sizeof(cat_m1_at_cmd_rst.cesq) - 1] = '\0';

    char *token;
    char *str = strdup(value);
    int count = 0;
    int rssi_value = 0;

    token = strtok(str, ",");
    while (token != NULL)
    {
        count++;

        if (count == 6)
        {
        	if((int)atoi(token) != 255)
        	{
            rssi_value = (int)atoi(token);
            cat_m1_at_cmd_rst.rssi = rssi_value - 140;
            break;
        	}
        }
        token = strtok(NULL, ",");
    }

    free(str);
}

void handle_gps_command(const char *value)
{
	int gpsDataLength = strlen(value);
    if (strstr(value, "1,1") != NULL)
    {
    	//gpsRSSI_0_1 = 0;
    	gpsRSSI_0_1 = 1;
        cat_m1_Status.gpsOn = 1;
        cell_locationFlag = true;
    }

    else if (strstr(value, "1,4") != NULL) {
    	//gpsRSSI_0_1 = 1;
    	gpsRSSI_0_1 = 0;
        cat_m1_Status.gpsOff = 1;
        gps_operation_cycle = (60*1);
        cell_locationFlag = false;
        gpsFlag = false;
    }
#if !defined(nRF9160_KT)
    else if (strstr(value, "1,3") != NULL || strstr(value, "0,0") != NULL)
#else
    else if (strstr(value, "1,3") != NULL || strstr(value, "1,0") != NULL || strstr(value, "0,0") != NULL)
#endif
    {
    	gps_operation_cycle = (60*4);
    	gpsRSSI_0_1 = 0;
    	cat_m1_Status.gpsOff = 1;
    	cell_locationFlag = true;
    	gpsFlag = false;
    }

    else { // strstr(value, "1,4") => after MSG: GPS DATA
       	if (gpsDataLength > 10) {
       	    char tempBuffer[sizeof(cat_m1_at_cmd_rst.gps)];
       	    int j = 0;

       	    for (int i = 0; value[i] != '\0' && j < sizeof(tempBuffer) - 1; i++) {
       	        if (value[i] != '"') {
       	            tempBuffer[j++] = value[i];
       	        }
       	    }
       	    tempBuffer[j] = '\0';

       	    strncpy((char *)cat_m1_at_cmd_rst.gps, tempBuffer, sizeof(cat_m1_at_cmd_rst.gps) - 1);
       	    cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';
       	}
    }
}

void handle_cell_location_command(const char *value)
{
//	int cell_locationDataLength = strlen(value);
//
//	if (cell_locationDataLength > 10) {
//	    char tempBuffer[sizeof(cat_m1_at_cmd_rst.gps)];
//	    int j = 0;
//
//	    char *token = strtok(value, ",");
//
//	    token = strtok(NULL, ",");
//
//	    if (token != NULL) {
//	        strncpy(tempBuffer, token, sizeof(tempBuffer) - 1);
//	        tempBuffer[sizeof(tempBuffer) - 1] = '\0';
//	        j = strlen(tempBuffer);
//	    }
//
//	    token = strtok(NULL, ",");
//	    if (token != NULL && j < sizeof(tempBuffer) - 1) {
//	        strncat(tempBuffer, ",", sizeof(tempBuffer) - j - 1);
//	        strncat(tempBuffer, token, sizeof(tempBuffer) - j - 2);
//	    }
//
//	    strncpy((char *)cat_m1_at_cmd_rst.gps, tempBuffer, sizeof(cat_m1_at_cmd_rst.gps) - 1);
//	    cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';

		strncpy((char *)cat_m1_at_cmd_rst.gps, (const char *)value, sizeof(cat_m1_at_cmd_rst.gps) - 1);
		cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';
//	}
}

void handle_xuuid_command(const char *value)
{
	strncpy((char *)cat_m1_at_cmd_rst.uuid, (const char *)value, sizeof(cat_m1_at_cmd_rst.uuid) - 1);
	cat_m1_at_cmd_rst.uuid[sizeof(cat_m1_at_cmd_rst.uuid) - 1] = '\0';
}

void handle_mqtt_event_command(const char *value)
{
    if (strstr(value, "1,-") != NULL) {
    	//catM1Reset();
    	wpmInitializationFlag = 1;
    	cat_m1_Status.Checked = 1;
    	currentMqttState = MQTT_CONNECT;
    }
    else if (strstr(value, "7,0") != NULL)
    {
    	cat_m1_Status.mqttSubscribeStatus++;
    }
    else if (strstr(value, "0,0") != NULL)
    {
    	cat_m1_Status.mqttConnectionStatus = 1;
    }
}

uint8_t timeUpdateFlag = 0;
void handle_cclk_command(const char *value)
{
	strncpy((char *)cat_m1_at_cmd_rst.time, (const char *)value, sizeof(cat_m1_at_cmd_rst.time) - 1);
	cat_m1_at_cmd_rst.time[sizeof(cat_m1_at_cmd_rst.time) - 1] = '\0';
	timeUpdateFlag = 1;
}

void handle_cnum_command(const char *value)
{
    // 중간 부분만 추출 (국가 코드 뒤 번호만 남기기)
    const char *phone_number = value + 3; // "+46" 이후의 번호 사용
    char formatted_number[20] = {0};      // 변환 후 저장할 버퍼

    // 전화번호를 "1912-1227-5694" 형식으로 변환
    snprintf(formatted_number, sizeof(formatted_number), "%.4s-%.4s-%.4s",
             phone_number, phone_number + 4, phone_number + 8);

    // 변환된 번호를 구조체 멤버에 저장
    strncpy((char *)cat_m1_at_cmd_rst.cnum, formatted_number, sizeof(cat_m1_at_cmd_rst.cnum) - 1);
    cat_m1_at_cmd_rst.cnum[sizeof(cat_m1_at_cmd_rst.cnum) - 1] = '\0';
}


void uart_init()
{
	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
}

void nrf9160_clear_buf()
{
	clear_uart_buf(&uart_cat_m1_rx);
	memset(&cat_m1_Status, 0, sizeof(cat_m1_Status));
	memset(&cat_m1_at_cmd_rst, 0, sizeof(cat_m1_at_cmd_rst));
	memset(&uart_cat_m1_buf, 0, sizeof(uart_cat_m1_buf));
	memset(&cat_m1_Status_Band, 0, sizeof(cat_m1_Status_Band));
	memset(&cat_m1_Status_BandAlert, 0, sizeof(cat_m1_Status_BandAlert));
	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));
	memset(&cat_m1_Status_GPS_Location, 0, sizeof(cat_m1_Status_GPS_Location));
	memset(&cat_m1_Status_IMU, 0, sizeof(cat_m1_Status_IMU));
	memset(&cat_m1_Status_BandSet, 0, sizeof(cat_m1_Status_BandSet));
}

void nrf9160_init()
{
    uart_init();
    PRINT_INFO("nRF9160 initialized\r\n");
}

void nrf9160_ready(void)
{
    switch (currentWpmState)
    {
        case WPM_INIT_CHECK:
            if (!wpmInitializationFlag)
            {
                receive_at_command_ret();
                send_at_command("AT\r\n");
                osDelay(500);

                cat_m1_Status.retryCount++;
                if (cat_m1_Status.retryCount >= 5)
                {
                    PRINT_INFO("Error count exceeded. Initialization failed.\n");
                    //currentWpmState = WPM_INIT_COMPLETE;
                    uart_init();
#if !defined(nRF9160_initial_upload)
                    catM1Reset();
#endif
                }
            }
            else
            {
                currentWpmState = WPM_INIT_COMPLETE;
            }
            break;

        case WPM_INIT_COMPLETE:
            PRINT_INFO("WPM initialization completed successfully.\n");
            break;
    }
}

void nrf9160_check()
{
    switch (currentCheckState)
    {
        case SYSTEM_MODE_CHECK:
            if (cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 2)
            {
                send_at_command("AT+CFUN=0\r\n");
#if defined(nRF9160_KT)
                send_at_command("AT+COPS=1,2,\"45008\"\r\n");
                send_at_command("AT%XSYSTEMMODE=1,0,1,0\r\n");
                send_at_command("AT+CPSMS=1,,,\"00000001\",\"00000011\"\r\n");
                send_at_command("AT+CEDRXS=2,4,\"0011\"\r\n");
#else
                send_at_command("AT+COPS=0,2\r\n");
                send_at_command("AT%XSYSTEMMODE=1,0,0,0\r\n");
                send_at_command("AT+CPSMS=0\r\n");
                send_at_command("AT+CEDRXS=0\r\n");
#endif
                osDelay(1000);
                send_at_command("AT%XSYSTEMMODE?\r\n");
                osDelay(200);
                cat_m1_Status.retryCount++;
                if (cat_m1_Status.retryCount >= 300)
                {
                    PRINT_INFO("System mode check failed.\n");
                    currentCheckState = CHECK_COMPLETE;
                    break;
                }
            }
            else
            {
                currentCheckState = CFUN_CHECK;
                cat_m1_Status.retryCount = 0;
            }
            break;

        case CFUN_CHECK:
            if (!cat_m1_Status.cfunStatus)
            {
                send_at_command("AT+CFUN=1\r\n");
                osDelay(1000);
                send_at_command("AT+CFUN?\r\n");
                osDelay(200);
                cat_m1_Status.retryCount++;
                if (cat_m1_Status.retryCount >= 300)
                {
                    PRINT_INFO("CFUN check failed.\n");
                    currentCheckState = CHECK_COMPLETE;
                    break;
                }
            }
            else
            {
            	cat_m1_Status.cfunStatus = 0;
                currentCheckState = CONNECTION_CHECK;
                cat_m1_Status.retryCount = 0;
            }
            break;

        case CONNECTION_CHECK:
            if (!cat_m1_Status.connectionStatus)
            {
                send_at_command("AT+COPS?\r\n");
                osDelay(500);

                cat_m1_Status.retryCount++;
                if (cat_m1_Status.retryCount >= 60 * 10)
                {
                    PRINT_INFO("Connection check failed.\n");
                    currentCheckState = CHECK_COMPLETE;
                    break;
                }
            }
            else
            {
                currentCheckState = FINAL_COMMANDS;
                cat_m1_Status.retryCount = 0;
            }
            break;

        case FINAL_COMMANDS:

			send_at_command("AT+CNUM\r\n");
        	send_at_command("AT#XNRFCLOUD=1\r\n");

            send_at_command("AT+CGDCONT?\r\n");
            osDelay(200);
            send_at_command("AT%XICCID\r\n");
            osDelay(200);

            currentCheckState = CHECK_COMPLETE;
            PRINT_INFO("All checks completed.\n");
            break;

        case CHECK_COMPLETE:
            cat_m1_Status.Checked = 1;
            break;
    }
}

void nrf9160_mqtt_setting()
{
    switch (currentMqttState) {
        case MQTT_INIT:
            cat_m1_Status.retryCount = 0;
            currentMqttState = MQTT_CONFIG;
            break;

        case MQTT_CONFIG:
            if (!cat_m1_Status.mqttSetStatus)
            {
                send_at_command("AT#XMQTTCFG=\"\",300,1\r\n");
                osDelay(1500);
                send_at_command("AT#XMQTTCFG?\r\n");
                osDelay(100);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 10)
                {
                	catM1Reset();
                    //currentMqttState = MQTT_COMPLETE;
                }
            }
            else
            {
                currentMqttState = MQTT_CONNECT;
            }
            break;

        case MQTT_CONNECT:
            if (cat_m1_Status.mqttConnectionStatus == 0)
            {
                send_at_command("AT#XMQTTCON=1,\"\",\"\",\"t-vsm.com\",18831\r\n");
                osDelay(5000);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 30)
                {
                	catM1Reset();
                    //currentMqttState = MQTT_COMPLETE;
                }
            }
            else
            {
                //currentMqttState = MQTT_SUBSCRIBE_STATUS;
            	currentMqttState = MQTT_COMPLETE;

            }
            break;

//        case MQTT_SUBSCRIBE_STATUS:
//            if (cat_m1_Status.mqttSubscribeStatus == 0)
//            {
//                send_at_command(SUB_STATUS_BANDSET);
//                osDelay(1000);
//                cat_m1_Status.retryCount++;
//
//                if (cat_m1_Status.retryCount >= 30)
//                {
//                	catM1Reset();
//                    //currentMqttState = MQTT_COMPLETE;
//                }
//            }
//            else
//            {
//                currentMqttState = MQTT_SUBSCRIBE_ALERT;
//            }
//            break;
//
//        case MQTT_SUBSCRIBE_ALERT:
//            if (cat_m1_Status.mqttSubscribeStatus == 1)
//            {
//                send_at_command(SUB_SERVER_ALERT);
//                osDelay(1000);
//                cat_m1_Status.retryCount++;
//
//                if (cat_m1_Status.retryCount >= 30)
//                {
//                	catM1Reset();
//                    //currentMqttState = MQTT_COMPLETE;
//                }
//            }
//            else
//            {
//                currentMqttState = MQTT_COMPLETE;
//            }
//            break;

        case MQTT_COMPLETE:
        	osDelay(5000);
            cat_m1_Status.Checked = 2;
            break;
    }
}

void nrf9160_mqtt_test()
{
	send_at_command("AT#XMQTTPUB=\"topic/slm/pub\",\"Hi~ from nRF9160\",0,0\r\n");
	osDelay(500);
}

void test_send_json_publish(void)
{
	send_at_command("AT#XMQTTCON=1,\"\",\"\",\"t-vsm.com\",18831\r\n");
	osDelay(300);
	send_at_command("AT%XMONITOR\r\n");

    const char *at_command = "AT#XMQTTPUB=\"/efwb/post/sync\"\r\n";

    // JSON message to be published
    const char *json_message = "{\"msg\":\"Let's go home\"}+++\r\n";

    char json_message_networkinfo[180];
    sPRINT_INFO(json_message_networkinfo, "{\"networkinfo\": \"%s\"}+++\r\n", cat_m1_at_cmd_rst.networkinfo);

//	const char *mqtt_data = "{\"shortAddress\": 2,"
//							"\"extAddress\": {\"low\": 285286663, \"high\": 0, \"unsigned\": true}+++\r\n";

    const char *mqtt_data = "{\"shortAddress\": 1,"
                            "\"extAddress\": {\"low\": 553722113, \"high\": 0, \"unsigned\": true},"
                            "\"capabilityInfo\": {\"low\": 553722113, \"high\": 0, \"unsigned\": true},"
                            "\"active\": \"true\","
                            "\"pid\": \"0xA021\","
                            "\"temperaturesensor\": {\"ambienceTemp\": 111, \"objectTemp\": 222},"
                            "\"lightsensor\": {\"rawData\": 333},"
                            "\"bandData\": {"
                                "\"start_byte\": 170,"
                                "\"sample_count\": 6,"
                                "\"fall_detect\": 0,"
                                "\"battery_level\": 30,"
                                "\"hrConfidence\": 100,"
                                "\"spo2Confidence\": 0,"
                                "\"hr\": 82,"
                                "\"spo2\": 0,"
                                "\"motionFlag\": 0,"
                                "\"scdState\": 1,"
                                "\"activity\": 0,"
                                "\"walk_steps\": 0,"
                                "\"run_steps\": 0,"
                                "\"x\": 731,"
                                "\"y\": -3,"
                                "\"z\": 687,"
                                "\"t\": 2819,"
                                "\"h\": 100953"
                            "},"
                            "\"rssi\": -36,"
                            "\"reportingInterval\": 2000,"
                            "\"pollingInterval\": \"always on device\""
                            "}+++\r\n";

    if (send_at_command(at_command))
    {
        PRINT_INFO("AT command sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(json_message_networkinfo))
    {
        PRINT_INFO("JSON message sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send JSON message.\n");
    }
    send_at_command("AT#XMQTTCON=0\r\n");
}

void send_Status_Band(cat_m1_Status_Band_t *status)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];
/*
    snPRINT_INFO(mqtt_data, sizeof(mqtt_data),
        "{\"bid\": %u,"
        "\"pid\": %u,"
        "\"rssi\": %u,"
        "\"start_byte\": %u,"
        "\"hr\": %u,"
        "\"spo2\": %u,"
        "\"motionFlag\": %u,"
        "\"scdState\": %u,"
        "\"activity\": %u,"
        "\"walk_steps\": %u,"
        "\"run_steps\": %u,"
        "\"temperature\": %u,"
        "\"pres\": %u,"
        "\"battery_level\": %u"
        "}+++\r\n",
        status->bid, status->pid, status->rssi, status->start_byte,
        status->hr, status->spo2, status->motionFlag, status->scdState,
        status->activity, status->walk_steps, status->run_steps,
        status->temperature, status->pres, status->battery_level);
*/
    snprintf(mqtt_data, sizeof(mqtt_data),
        "{\"extAddress\": {\"low\": %u, \"high\": 0},"
    	"\"pid\": \"0x%X\","
        "\"bandData\": {"
            "\"start_byte\": %u,"
            "\"sample_count\": 0,"
            "\"fall_detect\": 0,"
            "\"battery_level\": %u,"
            "\"hr\": %u,"
            "\"spo2\": %u,"
            "\"hrConfidence\": 100,"
            "\"spo2Confidence\": 100,"
            "\"motionFlag\": %u,"
            "\"scdState\": %u,"
            "\"activity\": %u,"
            "\"walk_steps\": %u,"
            "\"run_steps\": %u,"
            "\"x\": 0,"
            "\"y\": 0,"
            "\"z\": 0,"
            "\"t\": %u,"
            "\"h\": %d"
        "},"
        "\"rssi\": %d"
        "}+++\r\n",
		(unsigned int)status->bid, status->pid, status->start_byte,
        status->battery_level, status->hr, status->spo2,
        status->motionFlag, status->scdState, status->activity,
		(unsigned int)status->walk_steps, (unsigned int)status->run_steps, (unsigned int)status->temperature, status->pres, status->rssi
    );

//  if (send_at_command(NEW_BAND_TOPIC))

    if (send_at_command(OLD_BAND_TOPIC))
    {
        PRINT_INFO("OLD_BAND_TOPIC AT command sent successfully.\n");
        if (send_at_command(mqtt_data))
        {
            PRINT_INFO("JSON send_Status_Band message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send OLD_BAND_TOPIC AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
    //cell_locationFlag = true;
}

void send_Status_BandAlert(cat_m1_Status_BandAlert_t* alertData)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];
//    snprintf(mqtt_data, sizeof(mqtt_data),
//    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
//        "\"hr_alert\": %d,"
//        "\"spo2_alert\": %d"
//    	"}+++\r\n",
//		(unsigned int)alertData->bid, alertData->hr_alert, alertData->spo2_alert);
    snprintf(mqtt_data, sizeof(mqtt_data),
		"{\"extAddress\": {\"low\": %u, \"high\": 0},"
		"\"type\": %d,"
		"\"value\": %d"
		"}+++\r\n",
		(unsigned int)alertData->bid, alertData->type, alertData->value);

//  if (send_at_command(NEW_BANDALERT_TOPIC))

    if (send_at_command(OLD_BANDALERT_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");
        if (send_at_command(mqtt_data))
        {
            PRINT_INFO("JSON send_Status_BandAlert message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_Status_FallDetection(cat_m1_Status_FallDetection_t* fallData)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];
    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
        "\"type\": %d,"
        "\"value\": %d"
    	"}+++\r\n",
		(unsigned int)fallData->bid, fallData->type, fallData->fall_detect);

//  if (send_at_command(NEW_FALLDETECTION_TOPIC))

    if (send_at_command(OLD_FALLDETECTION_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");
        if (send_at_command(mqtt_data))
        {
            memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));
            PRINT_INFO("JSON send_Status_FallDetection message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_GPS_Location(cat_m1_Status_GPS_Location_t* location)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
    	"\"data\": \"%s\""
        "}+++\r\n",
		(unsigned int)location->bid, cat_m1_at_cmd_rst.gps);

    if (send_at_command(GPS_LOCATION_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");

        if (send_at_command(mqtt_data))
        {
        	osDelay(5000);
            memset(&cat_m1_at_cmd_rst.gps, 0, sizeof(cat_m1_at_cmd_rst.gps));
            PRINT_INFO("JSON send_GPS_Location message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_UUID(cat_m1_Status_uuid_t* uuid)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
    	"\"data\": \"%s\""
        "}+++\r\n",
		(unsigned int)uuid->bid, cat_m1_at_cmd_rst.uuid);

    if (send_at_command(UUID_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");

        if (send_at_command(mqtt_data))
        {
            memset(&cat_m1_at_cmd_rst.uuid, 0, sizeof(cat_m1_at_cmd_rst.uuid));
            PRINT_INFO("JSON message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_Fall_Difference_Value(cat_m1_Status_Fall_Difference_Value_t* Fall_Difference)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
    	"\"data\": \"%d\""
    	"\"accScal_data\": \"%d\""
        "}+++\r\n",
		(unsigned int)Fall_Difference->bid, Fall_Difference->data, Fall_Difference->accScal_data);

    if (send_at_command(FALLDETECTION_CHECK_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");

        if (send_at_command(mqtt_data))
        {
            memset(&cat_m1_at_cmd_rst.uuid, 0, sizeof(cat_m1_at_cmd_rst.uuid));
            PRINT_INFO("JSON message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_Status_IMU(cat_m1_Status_IMU_t* imu_data)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
        "\"acc_x\": %d,"
        "\"acc_y\": %d,"
        "\"acc_z\": %d,"
        "\"gyro_x\": %d,"
        "\"gyro_y\": %d,"
        "\"gyro_z\": %d,"
        "\"mag_x\": %d,"
        "\"mag_y\": %d,"
        "\"mag_z\": %d,"
    	"}+++\r\n",
		(unsigned int)imu_data->bid, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z,
		imu_data->gyro_x, imu_data->gyro_y, imu_data->gyro_z,
		imu_data->mag_x, imu_data->mag_y, imu_data->mag_z);

    if (send_at_command(IMU_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");
        if (send_at_command(mqtt_data))
        {
            PRINT_INFO("JSON message sent successfully.\n");
        }
        else
        {
            PRINT_INFO("Failed to send JSON message.\n");
        }
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void nrf9160_Get_gps()
{
    switch (gpsState)
    {
        case GPS_INIT:
            cat_m1_Status.gpsChecking = 1;
#if !defined(nRF9160_KT)
            send_at_command("AT#XMQTTCON=0\r\n");
#endif
            cat_m1_Status.retryCount = 0;
#if defined(nRF9160_KT)
            gpsState = GPS_ON;
#else
            gpsState = GPS_SYSTEM_MODE;
#endif
            break;

        case GPS_SYSTEM_MODE:
            if (cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 1)
            {
                send_at_command("AT+CFUN=0\r\n");
                send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
                osDelay(200);
                send_at_command("AT%XSYSTEMMODE?\r\n");
                osDelay(2000);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 60)
                {
                	catM1Reset();
                    //gpsState = GPS_COMPLETE;
                }
            }
            else
            {
                gpsState = GPS_CFUN;
                cat_m1_Status.retryCount = 0;
            }
            break;

        case GPS_CFUN:
            if (!cat_m1_Status.cfunStatus)
            {
                send_at_command("AT+CFUN=31\r\n");
                osDelay(200);
                send_at_command("AT+CFUN?\r\n");
                osDelay(2000);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 60)
                {
                	catM1Reset();
                    //gpsState = GPS_COMPLETE;
                }
            }
            else
            {
                gpsState = GPS_ON;
                cat_m1_Status.retryCount = 0;
            }
            break;

        case GPS_ON:
            if (!cat_m1_Status.gpsOn)
            {
#if defined(nRF9160_KT)
            	send_at_command("AT#XGPS=1,1,0,180\r\n");
#else
                send_at_command("AT#XGPS=1,0,0,180\r\n");
#endif

                osDelay(2000);
                send_at_command("AT#XGPS?\r\n");

                if (cat_m1_Status.parseResult == 0)
                {
                    send_at_command("AT#XGPS=0\r\n");
                    osDelay(1000);
                    cat_m1_Status.errorCount = 0;

                }

                osDelay(500);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 60)
                {
                	catM1Reset();
                    //gpsState = GPS_COMPLETE;
                }
            }
            else
            {
                gpsState = GPS_COMPLETE;
            }
            break;

        case GPS_COMPLETE:
            HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
            cat_m1_Status.Checked = 2;
            //gpsFlag = false;
            gpsState = GPS_INIT;
            break;
    }
}

void nrf9160_Stop_gps()
{
	send_at_command("AT#XGPS=0\r\n");
#if !defined(nRF9160_KT)
	send_at_command("AT+CFUN=0\r\n");
	currentWpmState = WPM_INIT_CHECK;
	currentCheckState = SYSTEM_MODE_CHECK;
	currentMqttState = MQTT_INIT;
	gpsState = GPS_INIT;
	cat_m1_Status.InitialLoad = 0;
	cat_m1_Status.Checked = 0;
	cat_m1_Status.connectionStatus = 0;
	cat_m1_Status.mqttConnectionStatus = 0;
	cat_m1_Status.mqttSubscribeStatus = 0;
	cat_m1_Status.cfunStatus = 0;
	cat_m1_Status.systemModeStatus = 0;


	cat_m1_Status.mqttSetStatus = 0;
	wpmInitializationFlag = 1;
#endif
	cat_m1_Status.gpsChecking = 0;
	cat_m1_Status.gpsOn = 0;
	cat_m1_Status.gpsOff = 0;
	gpsOffCheckTime = 0;
	//cell_locationFlag = true;
	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
}

void nrf9160_Get_gps_State()
{
	send_at_command("AT#XGPS?\r\n");
	osDelay(1000);
}

void nrf9160_Get_cell_location()
{
	send_at_command("AT%NCELLMEAS\r\n");
	osDelay(5000);
	send_at_command("AT#XNRFCLOUDPOS=2,0\r\n");
}

void nrf9160_Get_rssi()
{
	send_at_command("AT+CESQ\r\n");
}

void nrf9160_Get_time()
{
	send_at_command("AT+CCLK?\r\n");
}

void catM1Reset()
{
	wpmInitializationFlag = 0;
	currentWpmState = WPM_INIT_CHECK;
	currentCheckState = SYSTEM_MODE_CHECK;
	currentMqttState = MQTT_INIT;
	gpsState = GPS_INIT;
	cat_m1_Status.InitialLoad = 0;
	cat_m1_Status.Checked = 0;
	cat_m1_Status.connectionStatus = 0;
	cat_m1_Status.mqttConnectionStatus = 0;
	cat_m1_Status.mqttSubscribeStatus = 0;
	cat_m1_Status.bootCount = 0;
	cat_m1_Status.errorCount = 0;
	cat_m1_Status.gpsChecking = 0;
	cat_m1_Status.mqttChecking = 0;
	cat_m1_Status.cfunStatus = 0;
	cat_m1_Status.systemModeStatus = 0;
	cat_m1_Status.retryCount = 0;
	cat_m1_Status.gpsOn = 0;
	cat_m1_Status.gpsOff = 0;
	cat_m1_Status.mqttSetStatus = 0;
	gps_operation_cycle = 60*4;
	cell_locationFlag = true;
	catM1PWRGPIOInit();
	//send_at_command("AT+CFUN=0\r\n");
}

void catM1nRFCloud_Init()
{
	send_at_command("AT#XUUID\r\n");
	osDelay(1000);
	// Disable modem functionality
	send_at_command("AT+CFUN=4\r\n");
	osDelay(5000);
	// Delete previous certificates in slots 0, 1, 2
	send_at_command("AT%CMNG=3,16842753,0\r\n");
	osDelay(5000);
	send_at_command("AT%CMNG=3,16842753,1\r\n");
	osDelay(5000);
	send_at_command("AT%CMNG=3,16842753,2\r\n");
	osDelay(5000);
	// caCert
	send_at_command(caCert);
	osDelay(5000);
	// clientCert
	send_at_command(clientCert);
	osDelay(5000);
	// privateKey
	send_at_command(privateKey);
	osDelay(5000);
	send_at_command("AT%CMNG=1\r\n");
	nRFCloudFlag = 1;


}

void catM1PWRGPIOInit()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	osDelay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}

// 윤년을 확인하는 함수
int is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// 각 월별 일 수를 반환하는 함수 (윤년 고려)
int get_days_in_month(int year, int month) {
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // 2월은 윤년이면 29일
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    return days_in_month[month - 1];  // month는 1부터 시작하므로 -1
}

// UTC -> KST 변환 함수
void utc_to_kst(catM1Time *time) {
    // 9시간 더하기 (UTC -> KST)
    time->hour += 9;

    // 시간이 24시를 초과할 경우
    if (time->hour >= 24) {
        time->hour -= 24;  // 24를 넘으면 다시 0시부터 시작
        time->day += 1;    // 날짜를 하루 증가

        // 월말을 초과했는지 확인 (윤년 고려)
        int days_in_this_month = get_days_in_month(time->year, time->month);
        if (time->day > days_in_this_month) {
            time->day = 1;  // 다음 달로 넘어감
            time->month += 1;  // 월을 1 증가

            // 12월을 초과하면 연도를 증가
            if (time->month > 12) {
                time->month = 1;  // 1월로 초기화
                time->year += 1;  // 연도를 1 증가
            }
        }
    }
}

// Function to convert catM1Time to time_t
// Assumes the input is valid and within a valid range
time_t convertToTimeT(catM1Time dt) {
    struct tm t = {0};
    t.tm_year = dt.year - 1900; // tm_year is years since 1900
    t.tm_mon = dt.month - 1;   // tm_mon is 0-based (0 = January)
    t.tm_mday = dt.day;
    t.tm_hour = dt.hour;
    t.tm_min = dt.min;
    t.tm_sec = dt.sec;
    return mktime(&t);
}

// Function to determine if the difference between two catM1Time inputs is 1 minute or less
bool isDifferenceWithinOneMinute(catM1Time dt1, catM1Time dt2) {
    time_t time1 = convertToTimeT(dt1);
    time_t time2 = convertToTimeT(dt2);

    // Get the absolute difference in seconds
    double difference = difftime(time1, time2);

    return difference <= 60 && difference >= -60; // Check if difference is within 1 minute
}

catM1Time getCatM1Time(void){
	catM1Time nowTime;

	char year[3];
	strncpy(year, &cat_m1_at_cmd_rst.time[2], 2);
	year[2] = '\0';

	char month[3];
	strncpy(month, &cat_m1_at_cmd_rst.time[5], 2);
	month[2] = '\0';

	char day[3];
	strncpy(day, &cat_m1_at_cmd_rst.time[8], 2);
	day[2] = '\0';

	char hour[3];
	strncpy(hour, &cat_m1_at_cmd_rst.time[11], 2);
	hour[2] = '\0';

	char min[3];
	strncpy(min, &cat_m1_at_cmd_rst.time[14], 2);
	min[2] = '\0';

	char sec[3];
	strncpy(sec, &cat_m1_at_cmd_rst.time[17], 2);
	sec[2] = '\0';


	nowTime.year = (int)atoi(year);
	nowTime.month = (int)atoi(month);
	nowTime.day = (int)atoi(day);
	nowTime.hour = (int)atoi(hour);
	nowTime.min = (int)atoi(min);
	nowTime.sec = (int)atoi(sec);

	utc_to_kst(&nowTime);

	return nowTime;
}
