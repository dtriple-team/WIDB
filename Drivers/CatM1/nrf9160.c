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
uint8_t cat_m1_parse_cnt = 0;
uint8_t cat_m1_parse_ret = 0;
uint8_t cat_m1_boot_cnt = 0;
uint8_t cat_m1_error_cnt = 0;
uint8_t cat_m1_retry_cnt = 0;
uint8_t cat_m1_connection_status = 0;
uint8_t cat_m1_subscribe_status = 0;

uint8_t cat_m1_mqtt_checking = 0;
uint8_t cat_m1_gps_checking = 0;

uart_cat_m1_t uart_cat_m1_rx;
cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst_rx;

cat_m1_Status_Band_t cat_m1_Status_Band;
cat_m1_Status_BandAler_t cat_m1_Status_BandAler;
cat_m1_Status_FallDetection_t cat_m1_Status_FallDetection;
cat_m1_Status_GPS_Location_t cat_m1_Status_GPS_Location;
cat_m1_Status_IMU_t cat_m1_Status_IMU;
cat_m1_Status_BandSet_t cat_m1_Status_BandSet;


extern uint8_t wpmInitFlag;
uint8_t nrf9160_checked = 0;
extern uint8_t mqttRetryTime;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
    	push(&uart_cat_m1_rx, uart_cat_m1_rx.temp);
    	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
    }
}

void clear_uart_buf(uart_cat_m1_t* u)
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
	HAL_UART_Transmit(&huart1, (uint8_t*)cmd, strlen(cmd), 1000);
	PRINT_INFO("TX CMD >>> %s\r\n",cmd);

	return receive_at_command_ret();
}

bool receive_at_command_ret()
{
//	if (strstr(&uart_cat_m1_rx, str) != NULL)
//    {
//        //PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
//        return true;
//    }
	if(cat_m1_parse_ret)
	{
		return true;
	}
	else if(cat_m1_parse_ret == 0)
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
            uart_cat_m1_buf[cat_m1_parse_cnt] = uart_cat_m1_rx.rxd;
            cat_m1_parse_cnt++;

            PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
            cat_m1_parse_process(uart_cat_m1_buf);

            memset(&uart_cat_m1_buf, 0, MINMEA_MAX_SENTENCE_LENGTH);
            cat_m1_parse_cnt = 0;
        } else
        {
            if (cat_m1_parse_cnt < MINMEA_MAX_SENTENCE_LENGTH - 1) {
                uart_cat_m1_buf[cat_m1_parse_cnt] = uart_cat_m1_rx.rxd;
                cat_m1_parse_cnt++;
            }
        }
    }
    return true;
}

bool cat_m1_parse_process(uint8_t *msg)
{
    char command[MAX_CMD_LEN] = {0};
    char value[MAX_VALUE_LEN] = {0};

    char *colon_pos = strchr((char *)msg, ':');

    if (colon_pos != NULL)
    {
        int cmd_len = colon_pos - (char *)msg;
        strncpy(command, (char *)msg, cmd_len);
        command[cmd_len] = '\0';

        colon_pos++;
        int i = 0;

        while (i < MAX_VALUE_LEN - 1 && strncmp(colon_pos, "OK", 2) != 0 && strncmp(colon_pos, "ERROR", 5) != 0 && strncmp(colon_pos, "Ready", 5) != 0)
        {
            if (*colon_pos == '\0' || *colon_pos == '\r' || *colon_pos == '\n')
            {
                break;
            }
            value[i++] = *colon_pos++;
        }
        value[i] = '\0';
        //printf("AT Command: %s\r\n", command);
        //printf("Value: %s\r\n", value);

        cat_m1_parse_result((char *)command, (char *)value);
    }
    else
    {
    	if (strstr((char *)msg, "Ready"))
		{
			printf("Response: Ready\r\n");
			cat_m1_parse_ret = 1;
			cat_m1_boot_cnt++;
			wpmInitFlag = 1;
			cat_m1_retry_cnt = 0;
			printf("cat_m1_boot_cnt >>> %d\r\n",cat_m1_boot_cnt);
			if (cat_m1_boot_cnt >= 2)
			{
				catM1PWRGPIOInit();
				send_at_command("AT+CFUN=0\r\n");
				wpmInitFlag = 0;
				nrf9160_checked = 0;
				cat_m1_connection_status = 0;
				cat_m1_subscribe_status = 0;
				cat_m1_boot_cnt = 0;
				cat_m1_gps_checking = 0;
				cat_m1_mqtt_checking = 0;
				cat_m1_retry_cnt = 0;
				wpmInitFlag = 1;
			}
		}
    	else if (strstr((char *)msg, "OK"))
        {
            printf("Response: OK\r\n");
            cat_m1_parse_ret = 1;
            cat_m1_error_cnt = 0;
            wpmInitFlag = 1;
            cat_m1_retry_cnt = 0;
        }
        else if (strstr((char *)msg, "ERROR"))
        {
            printf("Response: ERROR\r\n");
            cat_m1_parse_ret = 0;
            cat_m1_error_cnt++;
			if (cat_m1_error_cnt >= 5)
			{
				catM1PWRGPIOInit();
				send_at_command("AT+CFUN=0\r\n");
				nrf9160_checked = 0;
				cat_m1_connection_status = 0;
				cat_m1_subscribe_status = 0;
				cat_m1_boot_cnt = 0;
				cat_m1_error_cnt = 0;
				cat_m1_gps_checking = 0;
				cat_m1_mqtt_checking = 0;
				cat_m1_retry_cnt = 0;
				wpmInitFlag = 1;
			}
        }
    }
    return false;
}

void cat_m1_parse_result(const char *command, const char *value)
{
    printf("Command: %s\r\n", command);
    printf("Value: %s\r\n", value);

    if (strstr(command, "+COPS") != NULL)
    {
        printf("COPS >>> OK\r\n");
        int cops_length = strlen(value);
        //PRINT_INFO("COPS result >>> %d\r\n", cops_length);
        //PRINT_INFO("COPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cops);

        if (cops_length > 5)
        {
            cat_m1_connection_status = 1;
        }
        else
        {
            cat_m1_connection_status = 0;
        }
        strcpy(cat_m1_at_cmd_rst_rx.cops, (const char *)value);
    }
    if (strstr(command, "+CGDCONT") != NULL)
    {
        printf("CGDCONT >>> OK\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.cgdcont, (const char *)value);
        //PRINT_INFO("CGDCONT result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cgdcont);
    }
    if (strstr(command, "%XICCID") != NULL)
    {
        printf("XICCID >>> OK\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.iccid, (const char *)value);
        //PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.iccid);
    }
    if (strstr(command, "%XMONITOR") != NULL)
    {
        printf("XMONITOR >>> OK\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.networkinfo, (const char *)value);
        //PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.networkinfo);
    }
    if (strstr(command, "#XGPS") != NULL)
	{
		printf("XGPS >>> OK\r\n");
		if (strstr(value, "1,4") != NULL)
        {
			printf("XGPS >>> 1,4\r\n");
        	strcpy(cat_m1_at_cmd_rst_rx.gps, (const char *)value);
        	//PRINT_INFO("GPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.gps);
        	send_at_command("AT#XGPS=0\r\n");
			send_at_command("AT+CFUN=0\r\n");
			nrf9160_checked = 0;
			cat_m1_connection_status = 0;
			cat_m1_subscribe_status = 0;
			cat_m1_gps_checking = 0;
			wpmInitFlag = 1;
        }
		else if (strstr(value, "1,3") != NULL)
		{
			printf("XGPS >>> 1,3\r\n");
			send_at_command("AT#XGPS=0\r\n");
			send_at_command("AT+CFUN=0\r\n");
			nrf9160_checked = 0;
			cat_m1_connection_status = 0;
			cat_m1_subscribe_status = 0;
			cat_m1_gps_checking = 0;
			wpmInitFlag = 1;
		}
	}
    if (strstr(command, "#XMQTTEVT") != NULL)
	{
		printf("#XMQTTEVT >>> OK\r\n");
		if (strstr(value, "1,-") != NULL)
		{
			printf("#XMQTTEVT >>> 1,-\r\n");
			wpmInitFlag = 1;
			nrf9160_checked = 1;
		}
		if (strstr(value, "7,0") != NULL)
		{
			printf("#XMQTTEVT >>> 7,0\r\n");
			cat_m1_subscribe_status++;
		}
	}
    if (strstr(command, "#XMQTTSERVERMSG") != NULL)
	{

	}
    if (strstr(command, "+CCLK") != NULL)
    {
    	printf("CCLK >>> OK\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.time, (const char *)value);
        PRINT_INFO("CCLK result >>> %s\r\n", cat_m1_at_cmd_rst_rx.time);
    }
}

// Initialize UART
void uart_init()
{
	HAL_UART_Receive_IT(&huart1, &uart_cat_m1_rx.temp, 1);
	clear_uart_buf(&uart_cat_m1_rx);
	clear_uart_buf(&cat_m1_at_cmd_rst_rx);
	clear_uart_buf(&uart_cat_m1_buf);
	clear_uart_buf(&cat_m1_Status_Band);
	clear_uart_buf(&cat_m1_Status_BandAler);
	clear_uart_buf(&cat_m1_Status_FallDetection);
	clear_uart_buf(&cat_m1_Status_GPS_Location);
	clear_uart_buf(&cat_m1_Status_IMU);
	clear_uart_buf(&cat_m1_Status_BandSet);
}

void nrf9160_init()
{
    uart_init();
    PRINT_INFO("nRF9160 initialized\r\n");
}

void nrf9160_ready(void)
{
	while (!wpmInitFlag)
	{
		receive_at_command_ret();
		send_at_command("AT\r\n");
		osDelay(500);

		if (cat_m1_error_cnt >= 5) {
	        break;
	    }
		if (mqttRetryTime > 5) {
			uart_init();
		}
	}
}

void nrf9160_check()
{
//	osDelay(100);
	send_at_command("AT%XSYSTEMMODE=1,0,0,0\r\n");
	//send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
//
//	osDelay(100);
	send_at_command("AT+CFUN=1\r\n");
	send_at_command("AT+CFUN?\r\n");
	osDelay(300);
	while(!cat_m1_connection_status)
	{
		send_at_command("AT+COPS?\r\n");
		osDelay(500);

	    if (cat_m1_retry_cnt >= 60*10) {
	        break;
	    }
	}

	send_at_command("AT+CGDCONT?\r\n");
	osDelay(100);
	send_at_command("AT%XICCID\r\n");

	osDelay(1000);
	nrf9160_checked = 1;


//	PRINT_INFO("COPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cops);
//	PRINT_INFO("CGDCONT result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cgdcont);
//	PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.iccid);
}

void nrf9160_mqtt_setting()
{
	send_at_command("AT#XMQTTCFG=\"\",300,1\r\n");

//	if (send_at_command("AT#XMQTTCON=1,\"\",\"\",\"broker.hivemq.com\",1883\r\n"))
//	{
//		//return true;
//	}
//	if (send_at_command("AT#XMQTTSUB=\"topic/slm/sub\",0\r\n"))
//	{
//		//return true;
//	}
	send_at_command("AT#XMQTTCON=1,\"\",\"\",\"t-vsm.com\",18831\r\n");
	while(cat_m1_subscribe_status == 0)
	{
		send_at_command("AT#XMQTTSUB=\"/DT/eHG4/Status/BandSet\",0\r\n");
		osDelay(5000);
		cat_m1_retry_cnt++;

		if (cat_m1_retry_cnt >= 5)
		{
			break;
		}
	}
	while (cat_m1_subscribe_status == 1)
	{
		send_at_command("AT#XMQTTSUB=\"/DT/eHG4/Status/ServerAlert\",0\r\n");
		osDelay(5000);

		cat_m1_retry_cnt++;
		if (cat_m1_retry_cnt >= 5)
		{
			break;
		}
	}
	nrf9160_checked = 2;
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
    sprintf(json_message_networkinfo, "{\"networkinfo\": \"%s\"}+++\r\n", cat_m1_at_cmd_rst_rx.networkinfo);

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
	cat_m1_mqtt_checking = 1;
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
        "\"rssi\": %u"
        "}+++\r\n",
		(unsigned int)status->bid, status->pid, status->start_byte,
        status->battery_level, status->hr, status->spo2,
        status->motionFlag, status->scdState, status->activity,
		(unsigned int)status->walk_steps, (unsigned int)status->run_steps, (unsigned int)status->temperature, (unsigned int)status->pres, status->rssi
    );

//    if (send_at_command("AT#XMQTTPUB=\"DT/eHG4/Status/Band\"\r\n"))
//    {
//        printf("AT command sent successfully.\n");
//    }
    if (send_at_command("AT#XMQTTPUB=\"/efwb/post/sync\"\r\n"))
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
    cat_m1_mqtt_checking = 0;
}

void send_Status_BandAlert(cat_m1_Status_BandAler_t* alertData)
{
	cat_m1_mqtt_checking = 1;
    char mqtt_data[1024];
    snprintf(mqtt_data, sizeof(mqtt_data),
        "{\"bid\": %u,"
        "\"hr_alert\": %d,"
        "\"spo2_alert\": %d"
    	"}+++\r\n",
        alertData->bid, alertData->hr_alert, alertData->spo2_alert);

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
    cat_m1_mqtt_checking = 0;
}

void send_Status_FallDetection(cat_m1_Status_FallDetection_t* fallData)
{
	cat_m1_mqtt_checking = 1;
    char mqtt_data[1024];
    snprintf(mqtt_data, sizeof(mqtt_data),
    	"{\"extAddress\": {\"low\": %u, \"high\": 0},"
        "\"type\": %d,"
        "\"value\": %d"
    	"}+++\r\n",
        fallData->bid, fallData->type, fallData->fall_detect);

//    if (send_at_command("AT#XMQTTPUB=\"DT/eHG4/Status/FallDetection\"\r\n"))
//    {
//        printf("AT command sent successfully.\n");
//    }
	if (send_at_command("AT#XMQTTPUB=\"/efwb/post/async\"\r\n"))
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
    cat_m1_mqtt_checking = 0;
}

void send_GPS_Location(cat_m1_Status_GPS_Location_t* location)
{
	cat_m1_mqtt_checking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
        "{\"bid\": %u,"
    	"\"data\": %s"
        "}+++\r\n",
        location->bid, cat_m1_at_cmd_rst_rx.gps);

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
    cat_m1_mqtt_checking = 0;
}

void send_Status_IMU(cat_m1_Status_IMU_t* imu_data)
{
	cat_m1_mqtt_checking = 1;
    char mqtt_data[1024];

    snprintf(mqtt_data, sizeof(mqtt_data),
        "{\"bid\": %u,"
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
		imu_data->bid, imu_data->acc_x, imu_data->acc_y, imu_data->acc_z,
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
    cat_m1_mqtt_checking = 0;
}

void nrf9160_Get_gps()
{
	send_at_command("AT#XMQTTCON=0\r\n");
	send_at_command("AT+CFUN=0\r\n");
	send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
	send_at_command("AT+CFUN=31\r\n");
	send_at_command("AT#XGPS=1,0,0,60\r\n");

	//send_at_command("AT+CFUN=0\r\n");
	//send_at_command("AT%XSYSTEMMODE=1,0,1,0\r\n");
	//send_at_command("AT+CFUN=31\r\n");
	//send_at_command("AT#XGPS=1,0,0,60\r\n");

	//send_at_command("AT#XGPS?\r\n");
	//nrf9160_checked = 2;
	cat_m1_gps_checking = 1;
}

void nrf9160_Get_gps_State()
{
	send_at_command("AT#XGPS?\r\n");
	osDelay(1000);
}

void nrf9160_Get_time()
{
	send_at_command("AT+CCLK?\r\n");
}

void catM1PWRGPIOInit()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	osDelay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}
