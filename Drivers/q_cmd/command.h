/*
 * command.h
 *
 *  Created on: May 2, 2025
 *      Author: D-triple
 */

#ifndef INC_COMMAND_H_
#define INC_COMMAND_H_


typedef enum {
    CMD_NONE = 0,
    CMD_TX_UART,
    CMD_RX_UART
} CommandType;

void command_queue_handler(void);


#endif /* INC_COMMAND_H_ */
