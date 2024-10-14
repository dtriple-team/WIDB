/*
 * BG770A-GL.h
 *
 *  Created on: Jun 11, 2024
 *      Author: D-triple
 */

#ifndef BLE_STM32WB5MMG_H_
#define BLE_STM32WB5MMG_H_

#include "../BLE/stm32wb_at/stm32wb_at_ble.h"
#include "cmsis_os2.h"

void stm32wb5mmg_init(void);
void stm32wb5mmg_adv_setting(stm32wb_at_BLE_ADV_DATA_t* param_BLE_DATA);
void stm32wb5mmg_adv(stm32wb_at_BLE_ADV_DATA_t* param_BLE_DATA);


#endif /* BLE_STM32WB5MMG_H_ */
