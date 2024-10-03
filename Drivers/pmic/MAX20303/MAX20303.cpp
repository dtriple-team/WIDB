/*******************************************************************************
 * Copyright (C) 2018 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *******************************************************************************
 */

#include <MAX20303.h>

#include "I2C.h"
#include <stdint.h>
#include <string.h>

//******************************************************************************
//MAX20303::MAX20303(I2C *i2c):
//	m_i2c(i2c), m_writeAddress(MAX20303_SLAVE_WR_ADDR),
//	m_readAddress(MAX20303_SLAVE_RD_ADDR)
//{
//}
MAX20303::MAX20303(void):
	m_writeAddress(MAX20303_SLAVE_WR_ADDR),
	m_readAddress(MAX20303_SLAVE_RD_ADDR)
{
}


//******************************************************************************
MAX20303::~MAX20303(void)
{
  //empty block
}


//******************************************************************************
int MAX20303::LDO1Config()
{
	int32_t ret = 0;
	appcmdoutvalue_ = 0x40;
	appdatainoutbuffer_[0] = 0x05;
	appdatainoutbuffer_[1] = 0x34;
	AppWrite(2);

	return ret;
}

//******************************************************************************
int MAX20303::LDO2Config()
{
	int32_t ret = 0;
	appcmdoutvalue_ = 0x42;
	appdatainoutbuffer_[0] = 0x01;
	appdatainoutbuffer_[1] = 0x18;     // 0.9V + (0.1V * number)   =  3V
	AppWrite(2);

	return ret;
}


//******************************************************************************
int MAX20303::writeReg(registers_t reg, uint8_t value)
{
	uint8_t uint_reg = reg;
	i2cbuffer_[0] = reg;
	i2cbuffer_[1] = value;
	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, (uint8_t *)i2cbuffer_, (1+1), 1);

//	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 1);
//	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &value, sizeof(uint8_t), 1);

	return MAX20303_NO_ERROR;
}


//******************************************************************************
int MAX20303::readReg(registers_t reg, uint8_t &value)
{
	uint8_t uint_reg = reg;
	uint8_t ret = 0;

	ret |= HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 1);
	ret |= HAL_I2C_Master_Receive(&hi2c3, m_readAddress, &uint_reg, sizeof(uint_reg), 1);
	value = uint_reg;

	return ret;
}

//******************************************************************************
int MAX20303::readRegMulti(registers_t reg, uint8_t *value, uint8_t len){

	uint8_t uint_reg = reg;

	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 1);
	HAL_I2C_Master_Receive(&hi2c3, m_readAddress, (uint8_t *)value, len, 1);

	return MAX20303_NO_ERROR;
}

//******************************************************************************
int MAX20303::writeRegMulti(registers_t reg, uint8_t *value, uint8_t len){

	i2cbuffer_[0] = reg;
	memcpy(&i2cbuffer_[1], value, len);

	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, (uint8_t *)i2cbuffer_, (len+1), 1);

	return MAX20303_NO_ERROR;
}

//******************************************************************************
int MAX20303::AppWrite(uint8_t dataoutlen){
	int ret;

	ret = writeRegMulti(MAX20303::REG_AP_DATOUT0, appdatainoutbuffer_, dataoutlen);
	ret |= writeReg(MAX20303::REG_AP_CMDOUT, appcmdoutvalue_);
	HAL_Delay(10);
	ret |= readReg(MAX20303::REG_AP_RESPONSE, appcmdoutvalue_);

	if(ret != 0)
		return MAX20303_ERROR;

	return MAX20303_NO_ERROR;
}


//******************************************************************************
int MAX20303::AppRead(uint8_t datainlen){
	int ret;

	ret = writeReg(MAX20303::REG_AP_CMDOUT, appcmdoutvalue_);
	HAL_Delay(10);
	ret |= readRegMulti(MAX20303::REG_AP_RESPONSE, i2cbuffer_, datainlen);
	if(ret != 0)
		return MAX20303_ERROR;

	return MAX20303_NO_ERROR;
}

//******************************************************************************
int MAX20303::BuckBoostEnable(void)
{
	int ret = 0;

	ret |= writeReg( REG_AP_DATOUT0,  0x00);    // Reserved = 0x00
	ret |= writeReg( REG_AP_DATOUT1,  0x04);    // BBstlSet = 0b'100   Buck Boost Peak current Limit = 200mA
	ret |= writeReg( REG_AP_DATOUT2,  0x19);    // BBstVSet = 0b'11001  Buck Boost Output Voltage = 5V
	ret |= writeReg( REG_AP_DATOUT3,  0x01);    // BBstRipRed = 1 Ripple Reduction
	// BBstAct    = 1 Actively discharged in Hard-Reset or Enable Low
	// BBstPas    = 1 Passively discharged in Hard-Reset or Enable Low
	// BBstMd     = 1 Damping Enabled
	// BBstInd    = 0  Inductance is 4.7uH
	// BBstEn     = 0b'01 Enabled
	ret |= writeReg( REG_AP_CMDOUT, 0x70);
	if (ret != 0)
		return MAX20303_ERROR;

	return MAX20303_NO_ERROR;
}

//******************************************************************************
int MAX20303::Max20303_BatteryGauge(unsigned char *batterylevel)
{
	int ret = 0;
	uint8_t data[2];

	data[0] = 0x04; data[1] = 0x04;
	ret = HAL_I2C_Master_Transmit(&hi2c3, MAX20303_I2C_ADDR_FUEL_GAUGE,   data, 1, 1);
	if (ret != 0)
		return MAX20303_ERROR;
	ret = HAL_I2C_Master_Receive (&hi2c3, MAX20303_I2C_ADDR_FUEL_GAUGE+1, data, 2, 1);
	if (ret != 0)
		return MAX20303_ERROR;

	if(data[0]>100){
		data[0] = 100;
	} else if(data[0]<0){
		data[0] = 0;
	}
	*batterylevel = data[0];

	return 0;
}

//******************************************************************************
uint8_t MAX20303::Battery_Status_Charger()
{
	uint8_t rxData;
	uint8_t ret = 0;

	ret |= readReg(MAX20303::REG_STATUS0, rxData);
	if(ret != 0x00){
		return 0xFF;
	}

	uint8_t Statuscharger = rxData & 0x07;

	//return Statuscharger;

	switch (Statuscharger)
	{
	case 0b000:
		// printf("Charger off\n");
		return false;
		break;
	case 0b001:
		// printf("Charging suspended due to temperature\n");
		return true;
		break;
	case 0b010:
		// printf("Precharge in progress\n");
		return true;
		break;
	case 0b011:
		// printf("Fast-charge constant current in progress\n");
		return true;
		break;
	case 0b100:
		// printf("Fast-charge constant voltage in progress\n");
		return true;
		break;
	case 0b101:
		// printf("Maintain charge in progress\n");
		return true;
		break;
	case 0b110:
		// printf("Maintain charger timer done\n");
		return true;
		break;
	case 0b111:
		// printf("Charger fault condition\n");
		return true;
		break;
	default:
		// printf("Unknown charger status\n");
		return false;
		break;
	}
}
