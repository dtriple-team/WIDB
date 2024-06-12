#include <stm32wb5mmg.h>
#include <main.h>

void stm32wb5mmg_init()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
}
