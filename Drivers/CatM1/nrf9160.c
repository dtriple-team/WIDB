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
cat_m1_Status_BandAler_t cat_m1_Status_BandAler;
cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection;
cat_m1_Status_GPS_Location_t cat_m1_Status_GPS_Location;
cat_m1_Status_IMU_t cat_m1_Status_IMU;
cat_m1_Status_BandSet_t cat_m1_Status_BandSet;


extern uint8_t wpmInitializationFlag;
extern uint8_t mqttRetryTime;
extern uint8_t catM1MqttInitialSend;

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
	//HAL_UART_Transmit_IT(&huart1, (uint8_t*)cmd, strlen(cmd));
	HAL_UART_Transmit(&huart1, (uint8_t*)cmd, strlen(cmd), 5000);
	//PRINT_INFO("TX CMD >>> %s\r\n",cmd);

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
            printf("Response: Ready\r\n");
            cat_m1_Status.parseResult = 1;
            cat_m1_Status.bootCount++;
            cat_m1_Status.retryCount = 0;
            wpmInitializationFlag = 1;

            printf("cat_m1_Status.bootCount >>> %d\r\n", cat_m1_Status.bootCount);
            if (cat_m1_Status.bootCount >= 2) {
                catM1Reset();
            }
        } else if (strstr((char *)msg, "OK")) {
            printf("Response: OK\r\n");
            cat_m1_Status.parseResult = 1;
            cat_m1_Status.errorCount = 0;
            cat_m1_Status.retryCount = 0;
            wpmInitializationFlag = 1;
        } else if (strstr((char *)msg, "ERROR")) {
            printf("Response: ERROR\r\n");
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
	//printf("Command: %s\r\n", command);
	//printf("Value: %s\r\n", value);

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
    if (strstr(value, "1,1") != NULL)
    {
        cat_m1_Status.gpsOn = 1;
    }
    else if (strstr(value, "1,4") != NULL)
    {
    	strncpy((char *)cat_m1_at_cmd_rst.gps, (const char *)value, sizeof(cat_m1_at_cmd_rst.gps) - 1);
    	cat_m1_at_cmd_rst.gps[sizeof(cat_m1_at_cmd_rst.gps) - 1] = '\0';
    	cat_m1_Status.gpsOff = 1;
    }
    else if (strstr(value, "1,3") != NULL || strstr(value, "0,0") != NULL)
    {
    	cat_m1_Status.gpsOff = 1;
    }
}

void handle_mqtt_event_command(const char *value)
{
    if (strstr(value, "1,-") != NULL) {
        wpmInitializationFlag = 0;
        cat_m1_Status.Checked = 0;
        cat_m1_Status.connectionStatus = 0;
        cat_m1_Status.mqttConnectionStatus = 0;
        cat_m1_Status.mqttSubscribeStatus = 0;
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

void handle_cclk_command(const char *value)
{
	strncpy((char *)cat_m1_at_cmd_rst.time, (const char *)value, sizeof(cat_m1_at_cmd_rst.time) - 1);
	cat_m1_at_cmd_rst.time[sizeof(cat_m1_at_cmd_rst.time) - 1] = '\0';
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
	memset(&cat_m1_Status_BandAler, 0, sizeof(cat_m1_Status_BandAler));
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
	while (!wpmInitializationFlag)
	{
		receive_at_command_ret();
		send_at_command("AT\r\n");
		osDelay(500);

		if (cat_m1_Status.errorCount >= 5) {
	        break;
	    }
		if (mqttRetryTime > 3) {
			uart_init();
		}
	}
}

void nrf9160_check()
{
	while(cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 2)
	{
		send_at_command("AT+CFUN=0\r\n");
		send_at_command("AT%XSYSTEMMODE=1,0,0,0\r\n");
		//send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
		send_at_command("AT%XSYSTEMMODE?\r\n");
		osDelay(2000);

		if (cat_m1_Status.retryCount >= 300) {
			break;
		}
	}
	while(!cat_m1_Status.cfunStatus)
	{
		send_at_command("AT+CFUN=1\r\n");
		send_at_command("AT+CFUN?\r\n");
		osDelay(2000);

	    if (cat_m1_Status.retryCount >= 300) {
	        break;
	    }
	}
	while(!cat_m1_Status.connectionStatus)
	{
		send_at_command("AT+COPS?\r\n");
		osDelay(500);

	    if (cat_m1_Status.retryCount >= 60*10) {
	        break;
	    }
	}

	send_at_command("AT+CGDCONT?\r\n");
	osDelay(100);
	send_at_command("AT%XICCID\r\n");

	osDelay(1000);
	cat_m1_Status.Checked = 1;


//	PRINT_INFO("COPS result >>> %s\r\n", cat_m1_at_cmd_rst.cops);
//	PRINT_INFO("CGDCONT result >>> %s\r\n", cat_m1_at_cmd_rst.cgdcont);
//	PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst.iccid);
}

void nrf9160_mqtt_setting()
{
	while(!cat_m1_Status.mqttSetStatus)
	{
		send_at_command("AT#XMQTTCFG=\"\",300,1\r\n");
		send_at_command("AT#XMQTTCFG?\r\n");
		osDelay(2000);
		cat_m1_Status.retryCount++;

		if (cat_m1_Status.retryCount >= 10)
		{
			break;
		}
	}

//	if (send_at_command("AT#XMQTTCON=1,\"\",\"\",\"broker.hivemq.com\",1883\r\n"))
//	{
//		//return true;
//	}
//	if (send_at_command("AT#XMQTTSUB=\"topic/slm/sub\",0\r\n"))
//	{
//		//return true;
//	}
	while(cat_m1_Status.mqttConnectionStatus == 0)
	{
		send_at_command("AT#XMQTTCON=1,\"\",\"\",\"t-vsm.com\",18831\r\n");
		osDelay(5000);
		cat_m1_Status.retryCount++;

		if (cat_m1_Status.retryCount >= 5)
		{
			break;
		}
	}
	while(cat_m1_Status.mqttSubscribeStatus == 0)
	{
		send_at_command("AT#XMQTTSUB=\"/DT/eHG4/Status/BandSet\",0\r\n");
		osDelay(5000);
		cat_m1_Status.retryCount++;

		if (cat_m1_Status.retryCount >= 5)
		{
			break;
		}
	}
	while (cat_m1_Status.mqttSubscribeStatus == 1)
	{
		send_at_command("AT#XMQTTSUB=\"/DT/eHG4/Status/ServerAlert\",0\r\n");
		osDelay(5000);

		cat_m1_Status.retryCount++;
		if (cat_m1_Status.retryCount >= 5)
		{
			break;
		}
	}
	cat_m1_Status.Checked = 2;
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
    sprintf(json_message_networkinfo, "{\"networkinfo\": \"%s\"}+++\r\n", cat_m1_at_cmd_rst.networkinfo);

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
        printf("AT command sent successfully.\n");
    }
    else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(json_message_networkinfo))
    {
        printf("JSON message sent successfully.\n");
    }
    else
    {
        printf("Failed to send JSON message.\n");
    }
    send_at_command("AT#XMQTTCON=0\r\n");
}

void send_Status_Band(cat_m1_Status_Band_t *status)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];
/*
    snprintf(mqtt_data, sizeof(mqtt_data),
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
            "\"h\": %u"
        "},"
        "\"rssi\": %d"
        "}+++\r\n",
		(unsigned int)status->bid, status->pid, status->start_byte,
        status->battery_level, status->hr, status->spo2,
        status->motionFlag, status->scdState, status->activity,
		(unsigned int)status->walk_steps, (unsigned int)status->run_steps, (unsigned int)status->temperature, (unsigned int)status->pres, status->rssi
    );

    if (send_at_command("AT#XMQTTPUB=\"/DT/eHG4/Status/Band\"\r\n"))
    {
        printf("AT command sent successfully.\n");
    }
//    if (send_at_command("AT#XMQTTPUB=\"/efwb/post/sync\"\r\n"))
//    {
//        printf("AT command sent successfully.\n");
//    }
    else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        printf("JSON message sent successfully.\n");
    }
    else
    {
        printf("Failed to send JSON message.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void send_Status_BandAlert(cat_m1_Status_BandAler_t* alertData)
{
	cat_m1_Status.mqttChecking = 1;
    char mqtt_data[1024];
    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
        "\"hr_alert\": %d,"
        "\"spo2_alert\": %d"
    	"}+++\r\n",
		(unsigned int)alertData->bid, alertData->hr_alert, alertData->spo2_alert);

    if (send_at_command("AT#XMQTTPUB=\"/DT/eHG4/Status/BandAlert\"\r\n"))
    {
        printf("AT command sent successfully.\n");
    }
    else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        printf("JSON message sent successfully.\n");
    }
    else
    {
        printf("Failed to send JSON message.\n");
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

    if (send_at_command("AT#XMQTTPUB=\"DT/eHG4/Status/FallDetection\"\r\n"))
    {
        printf("AT command sent successfully.\n");
    }
//	if (send_at_command("AT#XMQTTPUB=\"/efwb/post/async\"\r\n"))
//	{
//		printf("AT command sent successfully.\n");
//	}
    else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
    	memset(&cat_m1_Status_FallDetection, 0, sizeof(cat_m1_Status_FallDetection));
        printf("JSON message sent successfully.\n");
    }
    else
    {
        printf("Failed to send JSON message.\n");
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

    if (send_at_command("AT#XMQTTPUB=\"/DT/eHG4/GPS/Location\"\r\n"))
    {
        printf("AT command sent successfully.\n");
    }
    else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        printf("JSON message sent successfully.\n");
    }
    else
    {
        printf("Failed to send JSON message.\n");
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

    if (send_at_command("AT#XMQTTPUB=\"/DT/eHG4/Status/IMU\"\r\n"))
    {
        printf("AT command sent successfully.\n");
    } else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    if (send_at_command(mqtt_data))
    {
        printf("JSON message sent successfully.\n");
    } else
    {
        printf("Failed to send JSON message.\n");
    }
    cat_m1_Status.mqttChecking = 0;
}

void nrf9160_Get_gps()
{
	send_at_command("AT#XMQTTCON=0\r\n");

	while(cat_m1_Status.systemModeStatus == 0 || cat_m1_Status.systemModeStatus == 1)
	{

		send_at_command("AT+CFUN=0\r\n");
		send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
		send_at_command("AT%XSYSTEMMODE?\r\n");
		osDelay(2000);
		if (cat_m1_Status.retryCount >= 60*1) {
			break;
		}
	}
	send_at_command("AT+CFUN=31\r\n");
	while(!cat_m1_Status.gpsOn)
	{
		send_at_command("AT#XGPS=1,0,0,60\r\n");
		osDelay(2000);
		send_at_command("AT#XGPS?\r\n");

		osDelay(500);
		if (cat_m1_Status.retryCount >= 30) {
			break;
		}
	}
	//send_at_command("AT+CFUN=0\r\n");
	//send_at_command("AT%XSYSTEMMODE=1,0,1,0\r\n");
	//send_at_command("AT+CFUN=31\r\n");
	//send_at_command("AT#XGPS=1,0,0,60\r\n");

	//send_at_command("AT#XGPS?\r\n");
	//cat_m1_Status.Checked = 2;
	cat_m1_Status.gpsChecking = 1;
}

void nrf9160_Stop_gps()
{
	send_at_command("AT#XGPS=0\r\n");
	send_at_command("AT+CFUN=0\r\n");
	cat_m1_Status.Checked = 0;
	cat_m1_Status.connectionStatus = 0;
	cat_m1_Status.mqttConnectionStatus = 0;
	cat_m1_Status.mqttSubscribeStatus = 0;
	cat_m1_Status.cfunStatus = 0;
	cat_m1_Status.systemModeStatus = 0;
	cat_m1_Status.gpsOn = 0;
	cat_m1_Status.gpsOff = 0;
	cat_m1_Status.mqttSetStatus = 0;
	cat_m1_Status.gpsChecking = 0;
	wpmInitializationFlag = 0;
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
	cat_m1_Status.Checked = 0;
	cat_m1_Status.connectionStatus = 0;
	cat_m1_Status.mqttConnectionStatus = 0;
	cat_m1_Status.mqttSubscribeStatus = 0;
	cat_m1_Status.bootCount = 0;
	cat_m1_Status.errorCount = 100;
	cat_m1_Status.gpsChecking = 0;
	cat_m1_Status.mqttChecking = 0;
	cat_m1_Status.cfunStatus = 0;
	cat_m1_Status.systemModeStatus = 0;
	cat_m1_Status.retryCount = 0;
	catM1MqttInitialSend = 0;
	cat_m1_Status.gpsOn = 0;
	cat_m1_Status.gpsOff = 0;
	cat_m1_Status.mqttSetStatus = 0;
	catM1PWRGPIOInit();
	send_at_command("AT+CFUN=0\r\n");
}

void catM1PWRGPIOInit()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	osDelay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}
