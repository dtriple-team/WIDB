/**
  ******************************************************************************
  * @file    ble_at_appli.c
  * @brief   Application of the BLE AT Client project
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "../../BLE/stm32wb_at/stm32wb_at.h"
#include "../../BLE/stm32wb_at/ble_at_appli.h"

#include "../../BLE/stm32wb_at/stm32wb_at.h"
#include "../../BLE/stm32wb_at/stm32wb_at_ble.h"
#include "../../BLE/stm32wb_at/stm32wb_at_client.h"

#define WIDB

#ifdef IOT_BOARD
	#define USING_UART huart4
#else if WIDB
	#define USING_UART huart2
#endif

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t received_byte;
static uint32_t tick_snapshot, tick_snapshot2;
uint8_t at_buffer[64];
uint8_t global_svc_index = 0;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

///**
//  * @brief  BSP Push Button callback
//  * @param  Button Specifies the pin connected EXTI line
//  * @retval None.
//  */
//void BSP_PB_Callback(Button_TypeDef Button)
//{
//  if (Button == BUTTON_USER)
//  {
//    if( (HAL_GetTick() - tick_snapshot2) > 4000)
//    {
//      if( (HAL_GetTick() - tick_snapshot) < 500)
//      {
//        uint8_t svc_index;
//
//        tick_snapshot2 = HAL_GetTick();
//        if(global_svc_index == 1)
//        {
//          svc_index = 2;
//        }
//        else
//        {
//          svc_index = 1;
//        }
//        /* Send a BLE_SVC command to select the service running */
//        stm32wb_at_BLE_SVC_t param_BLE_SVC;
//        param_BLE_SVC.index = svc_index;
//        stm32wb_at_client_Set(BLE_SVC, &param_BLE_SVC);
//
//        global_svc_index = svc_index;
//      }
//      else
//      {
//        tick_snapshot = HAL_GetTick();
//
//        /* Send a BLE_NOTIF_VAL command to notify BLE application */
//        stm32wb_at_BLE_NOTIF_VAL_t param_BLE_NOTIF_VAL;
//        if(global_svc_index == 1)
//        {
//          param_BLE_NOTIF_VAL.svc_index = 1;
//          param_BLE_NOTIF_VAL.char_index = 2;
//          param_BLE_NOTIF_VAL.val_tab[0] = 1;
//          param_BLE_NOTIF_VAL.val_tab_len = 1;
//        }
//        else
//        {
//          param_BLE_NOTIF_VAL.svc_index = 2;
//          param_BLE_NOTIF_VAL.char_index = 1;
//          param_BLE_NOTIF_VAL.val_tab[0] = 80 + (HAL_GetTick() % 60);
//          param_BLE_NOTIF_VAL.val_tab_len = 1;
//        }
//
//        stm32wb_at_client_Set(BLE_NOTIF_VAL, &param_BLE_NOTIF_VAL);
//      }
//    }
//  }
//
//  return;
//}

uint8_t stm32wb_at_BLE_SVC_cb(stm32wb_at_BLE_SVC_t *param)
{
  global_svc_index = param->index;

  return 0;
}

//uint8_t stm32wb_at_BLE_EVT_WRITE_cb(stm32wb_at_BLE_EVT_WRITE_t *param)
//{
//  if( (param->svc_index == 1) && (param->char_index == 2) )
//  {
//    if(param->val_tab[0] == 0)
//    {
//      BSP_LED_Off(LED_GREEN);
//    }
//    else
//    {
//      BSP_LED_On(LED_GREEN);
//    }
//  }
//
//  return 0;
//}

uint8_t stm32wb_at_BLE_EVT_CONN_cb(stm32wb_at_BLE_EVT_CONN_t *param)
{
  if(param->status != 0)
  {
    printf("A remote device is  now connected\n");
  }
  else
  {
    printf("The remote device is  now disconnected\n");
  }
  return 0;
}

/**
 * @brief  Triggers the reception of a byte
 * @param  pBuff pointer to the first byte to transmit
 * @param  Size byte count to transfer
 * @retval 0 in case of success, an error code otherwise
 */
uint8_t stm32wb_at_ll_Transmit(uint8_t *pBuff, uint16_t Size)
{
  uint8_t status;

  status = HAL_UART_Transmit(&USING_UART, pBuff, Size, 0xFFFF);
  printf("  TX: %s",pBuff);

//  if(Size >= 40){
//	  printf("  TX: (ADV) 0x%s",&pBuff[39]); // BLE_ADV_DATA TX val print
//  } else {
//	  printf("  TX: %s",pBuff);
//  }

  return status;
}

/**
 * @brief  Triggers the reception of a byte
 * @param  new_frame contains the length of a new frame received in rx buffer, else 0
 * @retval None
 */
void stm32wb_at_ll_Async_receive(uint8_t new_frame)
{
  if(new_frame != 0)
  {
    printf("  RX: %s\r\n",at_buffer);
  }
  HAL_UART_Receive_IT(&USING_UART, &received_byte, 1);

  return;
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of DMA Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */

/*//CatM1 UART RX Callback Duplication
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle)
{
  if((uint32_t)UartHandle->Instance == (uint32_t)USART2)
  {
    stm32wb_at_Received(received_byte);
  }

  return;
}
*/
void dt_ble_adv_data_update(uint8_t adv_flag, char* device_name, uint8_t* manuf_data, stm32wb_at_BLE_ADV_DATA_t* param_BLE_DATA){
	for(int i=0; i<sizeof(param_BLE_DATA->adv_data); i++){
		param_BLE_DATA->adv_data[i] = 0x00;
	}
	param_BLE_DATA->adv_data[0] = 0x02;
	param_BLE_DATA->adv_data[1] = 0x01;
	param_BLE_DATA->adv_data[2] = adv_flag;
	param_BLE_DATA->adv_data[3] = sizeof(device_name)+1;
	param_BLE_DATA->adv_data[4] = 0x09;
	for(int i=0; i<sizeof(device_name); i++){
		param_BLE_DATA->adv_data[i+5] = device_name[i];
	}
	uint8_t prefix_index = param_BLE_DATA->adv_data[0] + param_BLE_DATA->adv_data[3] + 2;
	param_BLE_DATA->adv_data[prefix_index] = sizeof(param_BLE_DATA->adv_data)-prefix_index-1;
	param_BLE_DATA->adv_data[++prefix_index] = 0xFF;
	for(int i=prefix_index+1; i<sizeof(param_BLE_DATA->adv_data); i++){
		param_BLE_DATA->adv_data[i] = manuf_data[i-(prefix_index+1)];
	}
}

