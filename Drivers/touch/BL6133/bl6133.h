/*
 * bl6133.h
 *
 *  Created on: Jun 7, 2024
 *      Author: D-triple
 */

#ifndef BL6133_BL6133_H_
#define BL6133_BL6133_H_
#include "i2c.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

enum GESTURE
{
    None = 0x00,
    SlideUp = 0x01,
    SlideDown = 0x02,
    SlideLeft = 0x03,
    SlideRight = 0x04,
    SingleTap = 0x05,
    DoubleTap = 0x0B,
    LongPress = 0x0C
};

// readTouchData 함수 선언
uint8_t readTouchData(uint8_t* data, uint8_t len);
uint8_t touchDetect(uint8_t* touchData);
int32_t read_x(uint8_t* touchData);
int32_t read_y(uint8_t* touchData);

#ifdef __cplusplus
}
#endif


#endif /* BL6133_BL6133_H_ */
