/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : TouchGFXHAL.cpp
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

#include <TouchGFXHAL.hpp>

/* USER CODE BEGIN TouchGFXHAL.cpp */

#include "spi.h"
#include <touchgfx/hal/OSWrappers.hpp>
#include "main.h"
#include <string.h>
extern uint8_t spiDMACplt;
uint8_t fps;

using namespace touchgfx;

//extern "C"
void touchgfxSignalVSync(void)
{
  /* VSync has occurred, increment TouchGFX engine vsync counter */
  touchgfx::HAL::getInstance()->vSync();
  /* VSync has occurred, signal TouchGFX engine */
  touchgfx::OSWrappers::signalVSync();
}

void TouchGFXHAL::initialize()
{
    // Calling parent implementation of initialize().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::initialize() must be called to initialize the framework.

    TouchGFXGeneratedHAL::initialize();
}

/**
 * Gets the frame buffer address used by the TFT controller.
 *
 * @return The address of the frame buffer currently being displayed on the TFT.
 */
uint16_t* TouchGFXHAL::getTFTFrameBuffer() const
{
    // Calling parent implementation of getTFTFrameBuffer().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    return TouchGFXGeneratedHAL::getTFTFrameBuffer();
}

/**
 * Sets the frame buffer address used by the TFT controller.
 *
 * @param [in] address New frame buffer address.
 */
void TouchGFXHAL::setTFTFrameBuffer(uint16_t* address)
{
    // Calling parent implementation of setTFTFrameBuffer(uint16_t* address).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::setTFTFrameBuffer(address);
}

/**
 * This function is called whenever the framework has performed a partial draw.
 *
 * @param rect The area of the screen that has been drawn, expressed in absolute coordinates.
 *
 * @see flushFrameBuffer().
 */
void TouchGFXHAL::flushFrameBuffer(const touchgfx::Rect& rect)
{
    // Calling parent implementation of flushFrameBuffer(const touchgfx::Rect& rect).
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.
    // Please note, HAL::flushFrameBuffer(const touchgfx::Rect& rect) must
    // be called to notify the touchgfx framework that flush has been performed.
    // To calculate he start adress of rect,
    // use advanceFrameBufferToRect(uint8_t* fbPtr, const touchgfx::Rect& rect)
    // defined in TouchGFXGeneratedHAL.cpp

	uint millis = HAL_GetTick();

    TouchGFXGeneratedHAL::flushFrameBuffer(rect);

    __IO uint16_t* ptr;
	uint32_t height;

	ptr = getClientFrameBuffer() + rect.x + (240)*rect.y;
	ST7789_SetAddressWindow(rect.x,rect.y,rect.x+rect.width-1,rect.y+rect.height-1);

	//////////////// SPI //////////////////

//	ST7789_Select();
//	ST7789_DC_Set();
//
//	for (height = 0; height < rect.height ; height++)
//	{
//	  for(int i = 0; i < rect.width; i++) {
//		uint8_t dat[2];
//		dat[0] = ptr[i] >> 8;
//		dat[1] = ptr[i];
//		HAL_SPI_Transmit(&ST7789_SPI_PORT, dat, 2, HAL_MAX_DELAY);
//	  }
//	  ptr += 240; // Display Width.
//	}
//	ST7789_UnSelect();

	//////////////// DMA 16bit Buffer ////////////////

	uint8_t *spiDmaTxBuff;
	spiDmaTxBuff = (uint8_t*)malloc(rect.height*rect.width*2+1);

	uint32_t spiDmaTxBuff_Addr = (uint32_t)&spiDmaTxBuff[0];

	for(int i=0; i<rect.height; i++){
		memcpy((uint8_t*)spiDmaTxBuff_Addr+1, (uint8_t*)ptr, rect.width*2);
		for(int j=0; j<rect.width; j++){
			*((uint8_t*)spiDmaTxBuff_Addr) = *((uint8_t*)ptr+1+(j*2));
			spiDmaTxBuff_Addr+=2;
		}
		ptr += 240;
	}

	ST7789_Select();
	ST7789_DC_Set();

	spiTxDMA_start((uint8_t*)spiDmaTxBuff, rect.height*rect.width*2);
	while(spiDMACplt != 2){
		taskDelay(10);
	}

	ST7789_UnSelect();

	free(spiDmaTxBuff);

	uint8_t max_fps = 40*1000000 / (240*280*16); // SPI Max Speed 40M < 64Mbit/s
	uint nowMillis = HAL_GetTick();
	if(nowMillis == millis) nowMillis++;
	uint8_t proc_fps = 1000/(nowMillis - millis);
	fps = proc_fps > max_fps ? max_fps : proc_fps;

	//////////////// DMA 240px Line///////////////

//	ST7789_Select();
//	ST7789_DC_Set();
//
//	for(int i=0; i<rect.height; i++){
//		for(int j=0; j<rect.width; j++){
//			ptr[j] = ptr[j]>>8 | ptr[j]<<8;
//		}
//
//		spiTxDMA_start((uint8_t*)ptr, rect.width*2);
//
//		while(spiDMACplt != 2);
//
//		for(int j=0; j<rect.width; j++){
//			ptr[j] = ptr[j]>>8 | ptr[j]<<8; // reset position
//		}
//		ptr += 240;
//
//	}
//
//	ST7789_UnSelect();

}

bool TouchGFXHAL::blockCopy(void* RESTRICT dest, const void* RESTRICT src, uint32_t numBytes)
{
    return TouchGFXGeneratedHAL::blockCopy(dest, src, numBytes);
}

/**
 * Configures the interrupts relevant for TouchGFX. This primarily entails setting
 * the interrupt priorities for the DMA and LCD interrupts.
 */
void TouchGFXHAL::configureInterrupts()
{
    // Calling parent implementation of configureInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::configureInterrupts();
}

/**
 * Used for enabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::enableInterrupts()
{
    // Calling parent implementation of enableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableInterrupts();
}

/**
 * Used for disabling interrupts set in configureInterrupts()
 */
void TouchGFXHAL::disableInterrupts()
{
    // Calling parent implementation of disableInterrupts().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::disableInterrupts();
}

/**
 * Configure the LCD controller to fire interrupts at VSYNC. Called automatically
 * once TouchGFX initialization has completed.
 */
void TouchGFXHAL::enableLCDControllerInterrupt()
{
    // Calling parent implementation of enableLCDControllerInterrupt().
    //
    // To overwrite the generated implementation, omit call to parent function
    // and implemented needed functionality here.

    TouchGFXGeneratedHAL::enableLCDControllerInterrupt();
}

bool TouchGFXHAL::beginFrame()
{
    return TouchGFXGeneratedHAL::beginFrame();
}

void TouchGFXHAL::endFrame()
{
    TouchGFXGeneratedHAL::endFrame();
}

/* USER CODE END TouchGFXHAL.cpp */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
