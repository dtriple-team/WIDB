/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : STM32TouchController.cpp
  ******************************************************************************
  * This file was created by TouchGFX Generator 4.23.2. This file is only
  * generated once! Delete this file from your project and re-generate code
  * using STM32CubeMX or change this file manually to update it.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* USER CODE BEGIN STM32TouchController */

#include <STM32TouchController.hpp>

#include "bl6133.h"

extern uint8_t set_bLevel;
extern uint8_t brightness_count;

void STM32TouchController::init()
{
    /**
     * Initialize touch controller and driver
     *
     */
}
uint8_t touchData[6] = {0,};
GESTURE gesture = None;
GESTURE lastGesture = None;
extern uint8_t occurred_touchInterrupt;
uint8_t touchDetectFlag = 1;
bool STM32TouchController::sampleTouch(int32_t& x, int32_t& y)
{
    /**
     * By default sampleTouch returns false,
     * return true if a touch has been detected, otherwise false.
     *
     * Coordinates are passed to the caller by reference by x and y.
     *
     * This function is called by the TouchGFX framework.
     * By default sampleTouch is called every tick, this can be adjusted by HAL::setTouchSampleRate(int8_t);
     *
     */

	if(!occurred_touchInterrupt) return false; // ???àò ?ù∏?Ñ∞?üΩ?ä∏ ?ûò ?èô?ûë,.. ÏßùÏàò?äî ?ù¥?ÉÅ?ï®

	touchDetectFlag = touchDetect(touchData);
	if(!touchDetectFlag){
		brightness_count = 0;
	}

	//	uint8_t touchData[6] = {0,};
	uint8_t err = readTouchData(touchData, sizeof(touchData));
	occurred_touchInterrupt = 0;

	if(err) return false;

	gesture = static_cast<GESTURE>(touchData[0]);
	HAL_Delay(20); // debouncing
	switch(gesture){
		case None:
			x = read_x(touchData);
			y = read_y(touchData);
			break;
		case SingleTap:
			x = read_x(touchData);
			y = read_y(touchData);
			lastGesture = gesture;
			break;
		default: // slide interrupt
			lastGesture = gesture;
	}
	return true;

//	if(touchDetect(touchData)){
//		x = read_x(touchData);
//		y = read_y(touchData);
//		brightness_count = 0;
//
//		return true;
//	}
//	return false;

}

/* USER CODE END STM32TouchController */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
