/*
 * command_handler.c
 *
 *  Created on: May 2, 2025
 *      Author: D-triple
 */


#include "queue.h"
#include "command.h"
#include "main.h"
#include "usart.h"

void command_queue_handler(void){
	CommandItem item;
	extern CommandQueue cmd_q;

	while (CommandQueue_Pop(&cmd_q, &item))
	{
		switch (item.type)
		{
			case CMD_RX_UART:
				break;

			case CMD_TX_UART:
				HAL_UART_Transmit(&huart2, (uint8_t *)(item.data), strlen(item.data), HAL_MAX_DELAY);
				break;

			default:
				break;
		}
	}
}

