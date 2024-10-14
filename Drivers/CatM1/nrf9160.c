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
uint8_t cat_m1_connection_status = 0;
uint8_t cat_m1_gps_ret = 0;

uart_cat_m1_t uart_cat_m1_rx;
cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst_rx;

extern uint8_t wpmInitFlag;
uint8_t nrf9160_checked = 0;

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
	HAL_UART_Transmit_IT(&huart1, (uint8_t*)cmd, strlen(cmd));
	PRINT_INFO("TX CMD >>> %s\r\n",cmd);
    for (int attempt = 0; attempt < 10; attempt++)
    {
        if (receive_at_command_ret())
        {
            return true;
        }
        HAL_Delay(800);
    }
    return false;
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
    return false;
}

bool receive_response(void)
{
    // 버퍼가 비어 있지 않으면 데이터를 처리
    if (isEmpty(&uart_cat_m1_rx) == 0)
    {
        uart_cat_m1_rx.rxd = pop(&uart_cat_m1_rx);

        // '\r' 또는 '\n'이 수신되면 현재까지의 버퍼 내용을 처리
        if (uart_cat_m1_rx.rxd == '\r' || uart_cat_m1_rx.rxd == '\n')
        {
            // '\r' 또는 '\n'도 버퍼에 추가
            uart_cat_m1_buf[cat_m1_parse_cnt] = uart_cat_m1_rx.rxd;
            cat_m1_parse_cnt++;

            // 수신한 데이터를 출력 및 파싱
            PRINT_INFO("RX Data >>> %s\r\n", uart_cat_m1_buf);
            cat_m1_parse_process(uart_cat_m1_buf);

            // 버퍼 초기화 및 카운터 리셋
            memset(&uart_cat_m1_buf, 0, MINMEA_MAX_SENTENCE_LENGTH);
            cat_m1_parse_cnt = 0;
        } else
        {
            // '\r' 또는 '\n'이 아닌 문자들은 버퍼에 저장
            if (cat_m1_parse_cnt < MINMEA_MAX_SENTENCE_LENGTH - 1) {  // 버퍼 크기 제한 체크
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
			printf("cat_m1_boot_cnt >>> %d\r\n",cat_m1_boot_cnt);
			if (cat_m1_boot_cnt >= 2)
			{
				wpmInitFlag = 0;
				nrf9160_checked = 0;
				cat_m1_connection_status = 0;
				catM1PWRGPIOInit();
				send_at_command("AT+CFUN=0\r\n");
				send_at_command("AT+CFUN=1\r\n");
			}
		}
    	else if (strstr((char *)msg, "OK"))
        {
            printf("Response: OK\r\n");
            cat_m1_parse_ret = 1;
            cat_m1_error_cnt = 0;
        }
        else if (strstr((char *)msg, "ERROR"))
        {
            printf("Response: ERROR\r\n");
            cat_m1_parse_ret = 0;
            cat_m1_error_cnt++;
			if (cat_m1_error_cnt >= 5)
			{
				wpmInitFlag = 0;
				nrf9160_checked = 0;
				cat_m1_connection_status = 0;
				catM1PWRGPIOInit();
				send_at_command("AT+CFUN=0\r\n");
				send_at_command("AT+CFUN=1\r\n");
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
        printf("1>>>\r\n");
        int cops_length = strlen(value);
        //PRINT_INFO("COPS result >>> %d\r\n", cops_length);
        PRINT_INFO("COPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cops);

        if (cops_length == 14)
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
        printf("2>>>\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.cgdcont, (const char *)value);
        PRINT_INFO("CGDCONT result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cgdcont);
    }
    if (strstr(command, "%XICCID") != NULL)
    {
        printf("3>>>\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.iccid, (const char *)value);
        PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.iccid);
    }
    if (strstr(command, "%XMONITOR") != NULL)
    {
        printf("4>>>\r\n");
        strcpy(cat_m1_at_cmd_rst_rx.networkinfo, (const char *)value);
        PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.networkinfo);
    }
    if (strstr(command, "#XGPS") != NULL)
	{
		printf("5>>>\r\n");
		int gps_length = strlen(value);
		if (gps_length > 10)
        {
        	cat_m1_gps_ret = 1;
        }
        else
        {
        	cat_m1_gps_ret = 0;
        }
		strcpy(cat_m1_at_cmd_rst_rx.gps, (const char *)value);
		PRINT_INFO("GPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.gps);
	}
    if (strstr(command, "+CCLK") != NULL)
    {
        printf("6>>>\r\n");
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
}

void nrf9160_init()
{
    uart_init();
    PRINT_INFO("nRF9160 initialized\r\n");
}

void nrf9160_ready(void)
{
//	while (!wpmInitFlag)
//	{
		//cat_m1_send("AT\r\n");
		//cat_m1_recv("OK");
		if (receive_at_command_ret())
		{
			PRINT_INFO("Cat.M1 already available\r\n");
			wpmInitFlag = 1;
		}
		else if (send_at_command("AT\r\n"))
		{
			PRINT_INFO("Cat.M1 already available\r\n");
			wpmInitFlag = 1;
		}
	//	HAL_Delay(1000);
	//}
}

void nrf9160_check()
{
	HAL_Delay(100);
	if (send_at_command("AT+CFUN=1\r\n"))
	{
		//return true;
	}
	if (send_at_command("AT+CFUN?\r\n"))
	{
		//return true;
	}
	HAL_Delay(100);

	while(!cat_m1_connection_status)
	{
		send_at_command("AT+COPS?\r\n");
		HAL_Delay(500);
	}

	if (send_at_command("AT+CGDCONT?\r\n"))
	{
		//return true;
	}
	HAL_Delay(100);
	if (send_at_command("AT%XICCID\r\n"))
	{
		//return true;
	}
	HAL_Delay(1000);
	nrf9160_checked = 1;


//	PRINT_INFO("COPS result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cops);
//	PRINT_INFO("CGDCONT result >>> %s\r\n", cat_m1_at_cmd_rst_rx.cgdcont);
//	PRINT_INFO("ICCID result >>> %s\r\n", cat_m1_at_cmd_rst_rx.iccid);
}

void nrf9160_mqtt_setting()
{
	if (send_at_command("AT#XMQTTCFG="",300,1\r\n"))
	{
		//return true;
	}

//	if (send_at_command("AT#XMQTTCON=1,\"\",\"\",\"broker.hivemq.com\",1883\r\n"))
//	{
//		//return true;
//	}
//	if (send_at_command("AT#XMQTTSUB=\"topic/slm/sub\",0\r\n"))
//	{
//		//return true;
//	}
	if (send_at_command("AT#XMQTTCON=1,\"\",\"\",\"t-vsm.com\",18831\r\n"))
	{
		//return true;
	}
	nrf9160_checked = 2;
}

void nrf9160_mqtt_test()
{
	if (send_at_command("AT#XMQTTPUB=\"topic/slm/pub\",\"Hi~ from nRF9160\",0,0\r\n"))
	{
		//return true;
	}
	HAL_Delay(500);
}

void test_send_json_publish(void)
{
	send_at_command("AT%XMONITOR\r\n");
    // AT command to publish to the MQTT topic
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

    // Send the AT command first
    if (send_at_command(at_command))
    {
        printf("AT command sent successfully.\n");
    } else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    // Send the JSON message after the AT command is acknowledged
    if (send_at_command(json_message_networkinfo))
    {
        printf("JSON message sent successfully.\n");
    } else
    {
        printf("Failed to send JSON message.\n");
    }
    HAL_Delay(4000);
}

void send_json_publish(uint8_t shortAddress, uint8_t extAddressLow, uint8_t extAddressHigh,
		uint8_t capabilityInfoLow, uint8_t capabilityInfoHigh,
		uint8_t active, uint8_t pid,
		uint8_t ambienceTemp, uint8_t objectTemp, uint8_t rawData,
		uint8_t batteryLevel, uint8_t hrConfidence, uint8_t spo2Confidence,
		uint8_t hr, uint8_t spo2,
		uint8_t motionFlag, uint8_t scdState, uint8_t activity,
		uint8_t walkSteps, uint8_t runSteps, uint8_t x, uint8_t y, uint8_t z,
		uint8_t t, uint8_t h,
		uint8_t rssi, uint8_t reportingInterval, uint8_t pollingInterval)
{

    // AT command to publish to the MQTT topic
    const char *at_command = "AT#XMQTTPUB=\"/efwb/post/sync\"\r\n";

    // Construct the JSON message dynamically
    char mqtt_data[1024]; // Ensure this buffer is large enough for your JSON message
    snprintf(mqtt_data, sizeof(mqtt_data),
        "{\"shortAddress\": %d,"
        "\"extAddress\": {\"low\": %d, \"high\": %d, \"unsigned\": true},"
        "\"capabilityInfo\": {\"low\": %d, \"high\": %d, \"unsigned\": true},"
        "\"active\": \"%d\","
        "\"pid\": \"%d\","
        "\"temperaturesensor\": {\"ambienceTemp\": %d, \"objectTemp\": %d},"
        "\"lightsensor\": {\"rawData\": %d},"
        "\"bandData\": {"
            "\"start_byte\": 170,"
            "\"sample_count\": 6,"
            "\"fall_detect\": 0,"
            "\"battery_level\": %d,"
            "\"hrConfidence\": %d,"
            "\"spo2Confidence\": %d,"
            "\"hr\": %d,"
            "\"spo2\": %d,"
            "\"motionFlag\": %d,"
            "\"scdState\": %d,"
            "\"activity\": %d,"
            "\"walk_steps\": %d,"
            "\"run_steps\": %d,"
            "\"x\": %d,"
            "\"y\": %d,"
            "\"z\": %d,"
            "\"t\": %d,"
            "\"h\": %d"
        "},"
        "\"rssi\": %d,"
        "\"reportingInterval\": %d,"
        "\"pollingInterval\": \"%d\""
        "}+++\r\n",
        shortAddress, extAddressLow, extAddressHigh,
        capabilityInfoLow, capabilityInfoHigh,
        active, pid,
        ambienceTemp, objectTemp, rawData,
        batteryLevel, hrConfidence, spo2Confidence,
        hr, spo2,
        motionFlag, scdState, activity,
        walkSteps, runSteps, x, y, z,
        t, h,
        rssi, reportingInterval, pollingInterval);

    // Send the AT command first
    if (send_at_command(at_command))
    {
        printf("AT command sent successfully.\n");
    } else
    {
        printf("Failed to send AT command.\n");
        return;
    }

    // Send the JSON message after the AT command is acknowledged
    if (send_at_command(mqtt_data))
    {
        printf("JSON message sent successfully.\n");
    } else
    {
        printf("Failed to send JSON message.\n");
    }
    HAL_Delay(4000);
}

void nrf9160_Get_gps()
{
	send_at_command("AT+CFUN=0\r\n");
	send_at_command("AT%XSYSTEMMODE=0,0,1,0\r\n");
	send_at_command("AT+CFUN=31\r\n");
	send_at_command("AT#XGPS=1,0,0,0\r\n");
	//위 과정 한번만 실행
	if(cat_m1_gps_ret)
	{
		//#XGPS: 1,4 후 한번 더 #XGPS: 나오면 GPS 버퍼에 저장
		send_at_command("AT+CFUN=0\r\n");
		send_at_command("AT%XSYSTEMMODE=1,0,0,0\r\n");
		send_at_command("AT+CFUN=1\r\n");
	}
	nrf9160_checked = 2;
	//저장 이후 다시 AT+CFUN=1 변경
}

void nrf9160_Get_time()
{
	send_at_command("AT+CCLK?\r\n");
}

void catM1PWRGPIOInit()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}
