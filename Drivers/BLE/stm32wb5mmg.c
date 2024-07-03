#include <stm32wb5mmg.h>
#include <main.h>

#include "stm32wb_at.h"
#include "stm32wb_at_ble.h"
#include "stm32wb_at_client.h"
#include "ble_at_appli.h"

void stm32wb5mmg_init()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);

	// AT Client Example
	uint8_t status = 0;

	HAL_Delay(2000);
	status |= stm32wb_at_Init(&at_buffer[0], sizeof(at_buffer));
	status |= stm32wb_at_client_Init();

	/* Test the UART communication link with BLE module */
	status |= stm32wb_at_client_Query(BLE_TEST);
	HAL_Delay(1000);

	if(status != 0)
	{
		Error_Handler();
	}
	/* Send a BLE AT command to start the BLE P2P server application */
	stm32wb_at_BLE_SVC_t param_BLE_SVC;
	global_svc_index = 1;
	param_BLE_SVC.index = global_svc_index;
	stm32wb_at_client_Set(BLE_SVC, &param_BLE_SVC); // wait RX data from BLE chip

	HAL_Delay(1000);
}

void stm32wb5mmg_adv_setting(stm32wb_at_BLE_ADV_DATA_t* param_BLE_DATA)
{
//	// ADV parameter Setting
	uint8_t adv_flag = 0x04;
	const char* device_name = "DT-B";
	uint8_t manuf_data[31] = {0,};
	manuf_data[0] = 0x4C;
	manuf_data[1] = 0x00;
	manuf_data[2] = 0x02;
	manuf_data[3] = 0x16;
	manuf_data[4] = 0x13;
	dt_ble_adv_data_update(adv_flag, device_name, manuf_data, param_BLE_DATA);
}

void stm32wb5mmg_adv(stm32wb_at_BLE_ADV_DATA_t* param_BLE_DATA)
{
	// ADV
	param_BLE_DATA->adv_data[30] += 1;
	stm32wb_at_client_Set(BLE_ADV_DATA, param_BLE_DATA); // wait RX data from BLE chip
}
