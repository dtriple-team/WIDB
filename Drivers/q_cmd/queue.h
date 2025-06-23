/*
 * queue.h
 *
 *  Created on: Apr 30, 2025
 *      Author: D-triple
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>
#include "command.h"

#define CMD_QUEUE_SIZE   512
#define CMD_DATA_LEN     256

/* 명령 큐 항목 구조체 */
typedef struct {
    CommandType type;              // 명령 종류
    char data[CMD_DATA_LEN];       // 추가 문자열 (파라미터 등)
    uint8_t len;
} CommandItem;

/* 서클 큐 구조체 */
typedef struct {
    CommandItem buffer[CMD_QUEUE_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} CommandQueue;

/* 함수 정의 */
void CommandQueue_Init(CommandQueue *q);
bool CommandQueue_Push(CommandQueue *q, CommandType type, char *data, uint8_t len);
bool CommandQueue_Pop(CommandQueue *q, CommandItem *item);
bool CommandQueue_IsEmpty(const CommandQueue *q);
bool CommandQueue_IsFull(const CommandQueue *q);

/* 문자열 → 명령 매핑 함수 */
CommandType Parse_CommandType(const char *str);


#endif /* INC_QUEUE_H_ */
