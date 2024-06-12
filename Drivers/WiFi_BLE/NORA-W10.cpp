#include <NORA-W10.h>
#include <main.h>

void nora_w10_init()
{
	// PWR ON
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, GPIO_PIN_SET);
}
