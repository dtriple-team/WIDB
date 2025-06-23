/*
 * queue.c
 *
 *  Created on: Apr 30, 2025
 *      Author: D-triple
 */


#include "queue.h"
#include "command.h"
#include <string.h>
#include <stdbool.h>

void CommandQueue_Init(CommandQueue *q)
{
    q->head = q->tail = q->count = 0;
    for (int i = 0; i < CMD_QUEUE_SIZE; i++) {
        q->buffer[i].type = CMD_NONE;
        q->buffer[i].data[0] = '\0';
    }
}

bool CommandQueue_Push(CommandQueue *q, CommandType type, char *data, uint8_t len)
{
    if (CommandQueue_IsFull(q)) {
    	return false;
    }

    q->buffer[q->tail].type = type;
    q->buffer[q->tail].len = len;
    strncpy(q->buffer[q->tail].data, data, CMD_DATA_LEN - 1);
    q->buffer[q->tail].data[CMD_DATA_LEN - 1] = '\0';

    q->tail = (q->tail + 1) % CMD_QUEUE_SIZE;
    q->count++;
    return true;
}

bool CommandQueue_Pop(CommandQueue *q, CommandItem *item)
{
    if (CommandQueue_IsEmpty(q)) return false;

    *item = q->buffer[q->head];
    q->head = (q->head + 1) % CMD_QUEUE_SIZE;
    q->count--;
    return true;
}

bool CommandQueue_IsEmpty(const CommandQueue *q)
{
    return q->count == 0;
}

bool CommandQueue_IsFull(const CommandQueue *q)
{
    return q->count >= CMD_QUEUE_SIZE;
}

///* 명령 문자열 → 열거형 매핑 */
//CommandType Parse_CommandType(const char *str)
//{
//    if (strncmp(str, "LED ON", 6) == 0) return CMD_LED_ON;
//    if (strncmp(str, "LED OFF", 7) == 0) return CMD_LED_OFF;
//    if (strncmp(str, "STATUS", 6) == 0) return CMD_STATUS;
//
//    // 추가 명령은 여기서 확장
//    return CMD_UNKNOWN;
//}
