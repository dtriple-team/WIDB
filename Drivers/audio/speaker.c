/*
 * speaker.c
 *
 *  Created on: Oct 4, 2024
 *      Author: D-triple
 */

#include "speaker.h"
#include <main.h>
#include "dac.h"
#include "tim.h"

#define PI      3.141592
#define SAMPLES 1000 // 100Hz

uint16_t IV[SAMPLES];

void speaker_init(){
	// speaker power enable
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET);

	return;
}

void speaker_test_init(){
	uint16_t value;
	for(int i=0; i < SAMPLES; i++)
	{
		/* 360도(2PI) 를 200개의 샘플로 나누어서 1.8도씩 증가하면서 값을 구하면 -1 ~ 1 사이 값들이 나옴
		 * 따라서 sin(x) + 1 을 하면 0 ~ 2 사이 값이 나오며 이에 2048 을 곱하면 0 ~ 4096 사이의 값이 나옴
		 */
		value = (uint16_t)rint((sinf(((2*PI)/SAMPLES)*i)+1)*2048);
		IV[i] = value < 4096 ? value : 4095;
	}
}

void speaker_test(){

	for(int i=0; i < SAMPLES; i++)
	{
		HAL_DAC_SetValue(&hdac1, DAC_CHANNEL_2, DAC_ALIGN_12B_R, IV[i]);
		delay_us(100);
	}
}
