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

WpmState currentWpmState = WPM_INIT_CHECK;
CheckState currentCheckState = SYSTEM_MODE_CHECK;
MqttState currentMqttState = MQTT_INIT;
GpsState gpsState = GPS_INIT;

extern uint8_t wpmInitializationFlag;
extern uint8_t gpsOffCheckTime;
extern uint8_t UartRxRetryTime;
extern uint8_t gpsFlag;

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
    PRINT_INFO("TX CMD >>> %s\r\n", cmd);

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

            PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
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
}

void handle_cops_command(const char *value)
{
    int cops_length = strlen(value);
    cat_m1_Status.connectionStatus = (cops_length > 5) ? 1 : 0;
    cat_m1_Status.mqttChecking = (cops_length <= 5) ? 0 : cat_m1_Status.mqttChecking;
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
	strncpy((char *)cat_m1_at_cmd_rst.iccid, (const char *)value, ICCID_LEN - 1);
	cat_m1_at_cmd_rst.iccid[ICCID_LEN - 1] = '\0';
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
        cat_m1_Status.gpsOn = 1;
    }
    if (strstr(value, "1,4") != NULL) {
        cat_m1_Status.gpsOff = 0;
    } else {
        if (gpsDataLength > 10) {
            strncpy((char *)cat_m1_at_cmd_rst.gps, (const char *)value, sizeof(cat_m1_at_cmd_rst.gps) - 1);
            cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';
        }
    }
    if (strstr(value, "1,3") != NULL || strstr(value, "0,0") != NULL)
    {
    	cat_m1_Status.gpsOff = 1;
    }
    if (strstr(value, "1,2") != NULL)
    {
    	cat_m1_Status.gpsManual = 1;
    }
}

void handle_mqtt_event_command(const char *value)
{
    if (strstr(value, "1,-") != NULL) {
    	catM1Reset();
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
                send_at_command("AT%XSYSTEMMODE=1,0,0,0\r\n");
                send_at_command("AT%XSYSTEMMODE?\r\n");
                osDelay(2000);

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
                send_at_command("AT+CFUN?\r\n");
                osDelay(2000);

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
            send_at_command("AT+CGDCONT?\r\n");
            osDelay(100);
            send_at_command("AT%XICCID\r\n");
            osDelay(1000);

            cat_m1_Status.Checked = 1;
            currentCheckState = CHECK_COMPLETE;

            PRINT_INFO("All checks completed.\n");
            break;

        case CHECK_COMPLETE:
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
                send_at_command("AT#XMQTTCFG?\r\n");
                osDelay(2000);
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

                if (cat_m1_Status.retryCount >= 5)
                {
                	catM1Reset();
                    //currentMqttState = MQTT_COMPLETE;
                }
            }
            else
            {
                currentMqttState = MQTT_SUBSCRIBE_STATUS;
            }
            break;

        case MQTT_SUBSCRIBE_STATUS:
            if (cat_m1_Status.mqttSubscribeStatus == 0)
            {
                send_at_command(SUB_STATUS_BANDSET);
                osDelay(5000);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 5)
                {
                	catM1Reset();
                    //currentMqttState = MQTT_COMPLETE;
                }
            }
            else
            {
                currentMqttState = MQTT_SUBSCRIBE_ALERT;
            }
            break;

        case MQTT_SUBSCRIBE_ALERT:
            if (cat_m1_Status.mqttSubscribeStatus == 1)
            {
                send_at_command(SUB_SERVER_ALERT);
                osDelay(5000);
                cat_m1_Status.retryCount++;

                if (cat_m1_Status.retryCount >= 5)
                {
                	catM1Reset();
                    //currentMqttState = MQTT_COMPLETE;
                }
            }
            else
            {
                currentMqttState = MQTT_COMPLETE;
            }
            break;

        case MQTT_COMPLETE:
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

//    if (send_at_command(NEW_BAND_TOPIC))
//    {
//        PRINT_INFO("AT command sent successfully.\n");
//    }
    if (send_at_command(OLD_BAND_TOPIC))
    {
        PRINT_INFO("AT command sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        PRINT_INFO("JSON message sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send JSON message.\n");
    }
    cat_m1_Status.mqttChecking = 0;
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

//    if (send_at_command(NEW_BANDALERT_TOPIC))
//    {
//        PRINT_INFO("AT command sent successfully.\n");
//    }
	if (send_at_command(OLD_BANDALERT_TOPIC))
	{
		PRINT_INFO("AT command sent successfully.\n");
	}
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        PRINT_INFO("JSON message sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send JSON message.\n");
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

//    if (send_at_command(NEW_FALLDETECTION_TOPIC))
//    {
//        PRINT_INFO("AT command sent successfully.\n");
//    }
	if (send_at_command(OLD_FALLDETECTION_TOPIC))
	{
		PRINT_INFO("AT command sent successfully.\n");
	}
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
    	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));
        PRINT_INFO("JSON message sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send JSON message.\n");
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
    }
    else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
    	memset(&cat_m1_Status_GPS_Location, 0, sizeof(cat_m1_Status_GPS_Location));
        PRINT_INFO("JSON message sent successfully.\n");
    }
    else
    {
        PRINT_INFO("Failed to send JSON message.\n");
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
    } else
    {
        PRINT_INFO("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        PRINT_INFO("JSON message sent successfully.\n");
    } else
    {
        PRINT_INFO("Failed to send JSON message.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void nrf9160_Get_gps()
{
    switch (gpsState)
    {
        case GPS_INIT:
            cat_m1_Status.gpsChecking = 1;
            send_at_command("AT#XMQTTCON=0\r\n");
            cat_m1_Status.retryCount = 0;
            gpsState = GPS_SYSTEM_MODE;
            break;

        case GPS_SYSTEM_MODE:
            if (cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 1)
            {
                send_at_command("AT+CFUN=0\r\n");
                send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
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
                send_at_command("AT#XGPS=1,0,0,180\r\n");
                osDelay(2000);
                send_at_command("AT#XGPS?\r\n");

//                if (cat_m1_Status.parseResult == 0)
//                {
//                    send_at_command("AT#XGPS=0\r\n");
//                    cat_m1_Status.errorCount =0;
//
//                }

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
            gpsFlag = 2;
            gpsState = GPS_INIT;
            break;
    }
}

void nrf9160_Get_gps_self_control()
{
    switch (gpsState)
    {
        case GPS_INIT:
            cat_m1_Status.gpsChecking = 1;
            send_at_command("AT#XMQTTCON=0\r\n");
            cat_m1_Status.retryCount = 0;
            gpsState = GPS_SYSTEM_MODE;
            break;

        case GPS_SYSTEM_MODE:
            if (cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 1)
            {
                send_at_command("AT+CFUN=0\r\n");
                send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
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
                gpsState = GPS_COMPLETE;
            break;

        case GPS_COMPLETE:
            HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
            cat_m1_Status.Checked = 2;
            gpsState = GPS_INIT;
            break;
    }
}

void nrf9160_Stop_gps()
{
	//send_at_command("AT#XGPS=0\r\n");
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
	cat_m1_Status.gpsOn = 0;
	cat_m1_Status.gpsOff = 0;
	cat_m1_Status.gpsManual = 0;
	cat_m1_Status.mqttSetStatus = 0;
	cat_m1_Status.gpsChecking = 0;
	wpmInitializationFlag = 1;
	//gpsOffCheckTime = 0;
	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
}

void nrf9160_Get_gps_State()
{
	send_at_command("AT#XGPS?\r\n");
	osDelay(1000);
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
	cat_m1_Status.gpsManual = 0;
	cat_m1_Status.mqttSetStatus = 0;
	catM1PWRGPIOInit();
	//send_at_command("AT+CFUN=0\r\n");
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
