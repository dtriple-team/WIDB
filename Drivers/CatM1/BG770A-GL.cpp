#include "BG770A-GL.h"
#include <main.h>

void bg770a_gl_init()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
}
