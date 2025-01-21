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

#include "cmsis_os2.h"

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
	uint8_t ret = 0;
	ret = HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, (uint8_t *)i2cbuffer_, (1+1), 10);

//	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 1);
//	HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &value, sizeof(uint8_t), 1);

	return ret;
}


//******************************************************************************
int MAX20303::readReg(registers_t reg, uint8_t &value)
{
	uint8_t uint_reg = reg;
	uint8_t ret = 0;

	ret |= HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 10);
	ret |= HAL_I2C_Master_Receive(&hi2c3, m_readAddress, &uint_reg, sizeof(uint_reg), 10);
	value = uint_reg;

	return ret;
}

//******************************************************************************
int MAX20303::readRegMulti(registers_t reg, uint8_t *value, uint8_t len){

	uint8_t uint_reg = reg;
	uint8_t ret = 0;

	ret |= HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, &uint_reg, sizeof(uint8_t), 1);
	ret |= HAL_I2C_Master_Receive(&hi2c3, m_readAddress, (uint8_t *)value, len, 100);

	return ret;
}

//******************************************************************************
int MAX20303::writeRegMulti(registers_t reg, uint8_t *value, uint8_t len){

	i2cbuffer_[0] = reg;
	memcpy(&i2cbuffer_[1], value, len);
	uint8_t ret = 0;

	ret |= HAL_I2C_Master_Transmit(&hi2c3, m_writeAddress, (uint8_t *)i2cbuffer_, (len+1), 10);

	return ret;
}

//******************************************************************************
int MAX20303::AppWrite(uint8_t dataoutlen){
	int ret;

	ret = writeRegMulti(MAX20303::REG_AP_DATOUT0, appdatainoutbuffer_, dataoutlen);
	ret |= writeReg(MAX20303::REG_AP_CMDOUT, appcmdoutvalue_);
	osDelay(10);
	ret |= readReg(MAX20303::REG_AP_RESPONSE, appcmdoutvalue_);

	if(ret != 0)
		return MAX20303_ERROR;

	return MAX20303_NO_ERROR;
}


//******************************************************************************
int MAX20303::AppRead(uint8_t datainlen){
	int ret;

	ret = writeReg(MAX20303::REG_AP_CMDOUT, appcmdoutvalue_);
	osDelay(10);
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
	ret = HAL_I2C_Master_Transmit(&hi2c3, MAX20303_I2C_ADDR_FUEL_GAUGE,   data, 1, 10);
	if (ret != 0)
		return MAX20303_ERROR;
	ret = HAL_I2C_Master_Receive (&hi2c3, MAX20303_I2C_ADDR_FUEL_GAUGE+1, data, 2, 10);
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

//******************************Haptic****************************************
int MAX20303::Max20303_HapticSetting(void) // 햅틱모드 설정 Dtriple yeh
{
	int32_t ret = 0;
	appcmdoutvalue_ = REG_HPT_CONFIG_WRITE0;
	osDelay(100);
	appdatainoutbuffer_[0] = 0x0A; // 리니어 모터 0x0E, dc모터 0x0A 로 설정
	appdatainoutbuffer_[1] = 0xD0; // 역기전력 추측
	appdatainoutbuffer_[2] = 0x17; // 제로크로싱 비교기 감속 활성화[7], 제로크로싱 이벤트 캡처 필터 활성화[4]
	appdatainoutbuffer_[3] = 0x03; //
	appdatainoutbuffer_[4] = 0x45;
	appdatainoutbuffer_[5] = 0x01;
	ret |= AppWrite(6);
	return ret;
}

int MAX20303::Max20303_HapticSetFullScale(void) // 햅틱모드 설정 Dtriple yeh
{
	int32_t ret = 0;
	appcmdoutvalue_ = REG_HPT_CONFIG_SETFULLCALE;
	osDelay(100);

	appdatainoutbuffer_[0] = 0xBD; // 전압 조절
	AppWrite(1);
	return ret;
}

int MAX20303::Max20303_HapticDrive0(void) // 햅틱 드라이브모드 설정 Dtriple yeh
{
	return writeReg(REG_HPT_DIRECT0, 0b00000001);
}

int MAX20303::Max20303_HapticDrive1(void) // 햅틱 드라이브모드 설정 Dtriple yeh
{
	return writeReg(REG_HPT_DIRECT1, 0b00100110); // ExtTrig off, RamEn off, HptDrvEn on, Enable RTI2C mode Drivemod set[4:0]
										   // writeReg(REG_HPT_DIRECT1, 0b01110010); // ExtTrig off, RamEn on, HptDrvEn on, Enable RAMHPI mode Drivemod set[4:0]
}

int MAX20303::Max20303_HapticStart(void) // 햅틱 구동 Dtriple yeh
{
	return writeReg(REG_HPT_RTI2CAMP, 0b11100100); // 정방향 회전, 3V2
}

int MAX20303::Max20303_HapticStop(void) // 햅틱 구동 멈춤 Dtriple yeh
{
	return writeReg(REG_HPT_RTI2CAMP, 0b10000000); // 정방향 회전, 0V
}

int MAX20303::Max20303_HapticStatus() // Dtriple yeh 햅틱 설정 레지스터 읽기
{
	int ret;
	unsigned char data[6];
	ret = writeReg(MAX20303::REG_AP_CMDOUT, 0xA1); //)0xA1 햅틱 설정 읽기 레지스터
	osDelay(9);
	ret = readReg(MAX20303::REG_AP_DATAIN0, data[0]);
	ret = readReg(MAX20303::REG_AP_DATAIN1, data[1]);
	ret = readReg(MAX20303::REG_AP_DATAIN2, data[2]);
	ret = readReg(MAX20303::REG_AP_DATAIN3, data[3]);
	ret = readReg(MAX20303::REG_AP_DATAIN4, data[4]);
	ret = readReg(MAX20303::REG_AP_DATAIN5, data[5]);
	if (ret != 0)
	{
//		printf("Max20303_HapticStatus has failed\r\n");
	}

	return 0;
}

int MAX20303::Max20303_HapticDriveStatus() // 햅틱 드라이브모드 설정 읽기 Dtriple yeh
{
	int ret;
	unsigned char data[4];

	ret = readReg(MAX20303::REG_HPT_DIRECT1, data[0]);
	ret |= readReg(MAX20303::REG_HPT_LOCK_CONFIG, data[1]);
	ret |= readReg(MAX20303::REG_HPT_RTI2CAMP, data[2]);
	ret |= readReg(MAX20303::REG_HPT_SET_MODE, data[3]);
	if (ret != 0)
	{
//		printf("Max20303_Haptic Drive Status has failed\r\n");
	}
	return 0;
}

void MAX20303::Max20303_StartHapticPattern(int hapticFrequencyHz, int hapticDuration, int hapticContinue)
{

	for (int i = 0; i < hapticContinue; i++)
	{

		writeReg(REG_HPT_RTI2CAMP, 0b11111111);
		osDelay(hapticDuration);
		writeReg(REG_HPT_RTI2CAMP, 0b10000000);

		osDelay(1000 / hapticFrequencyHz);
	}
}

void MAX20303::setHapticPatternSample(const HapticPatternSample &sample)
{
	// Write data to the specified RAM address using the structure fields
	writeReg(REG_HPT_RAM_ADDR, sample.HptRAMAddr);
	writeReg(REG_HPT_RAM_DATA_H, ((sample.nLSx & 0b11) << 6) | ((sample.AmpSign & 0b1) << 5) | ((sample.Amp & 0b1111100) >> 2));
	writeReg(REG_HPT_RAM_DATA_M, ((sample.Amp & 0b11) << 6) | ((sample.Dur & 0b111110) << 1) | ((sample.Wait & 0b1) << 7) | ((sample.Wait & 0b11110000) >> 4));
	writeReg(REG_HPT_RAM_DATA_L, ((sample.Wait & 0b1111) << 4) | (sample.RPTx & 0b1111));
}

void MAX20303::createHapticPattern()
{
	writeReg(REG_HPT_DIRECT1, 0b01110010); // ExtTrig off, RamEn on, HptDrvEn on, Enable RAMHPI mode Drivemod set[4:0]
	osDelay(100);
	writeReg(REG_HPT_RAM_ADDR, 0b00000001);
	osDelay(100);
	writeReg(REG_HPT_RAM_DATA_H, 0b00010111);
	osDelay(100);
	writeReg(REG_HPT_RAM_DATA_M, 0b01111100);
	osDelay(100);
	writeReg(REG_HPT_RAM_DATA_L, 0b00101111);

	// REG_HPT_RAM_DATA_H: 11 0 11111
	// REG_HPT_RAM_DATA_M : 11 11110 0
	// REG_HPT_RAM_DATA_L : 0001 1111

	// HptVfs[7:0] : 10111101

	// Define haptic pattern samples
	// HapticPatternSample samples[] = {
	// 	{0b00000001, 0b00, 0b0, 0b11111, 0b11110, 0b00001, 0b0001}, // Sample 1
	// 	{0b00000010, 0b10, 0b1, 0b11000, 0b10000, 0b1010, 0b0001},	// Sample 2
	// 	{0b00000011, 0b11, 0b0, 0b10000, 0b01000, 0b0110, 0b0001},	// Sample 3
	// 	{0b00000100, 0b11, 0b1, 0b10000, 0b10000, 0b1010, 0b0001},	// Sample 4
	// 	{0b00000101, 0b00, 0b0, 0b01000, 0b00100, 0b0000, 0b0001},	// Sample 5
	// 	{0b00000110, 0b01, 0b1, 0b01110, 0b01000, 0b1010, 0b0001},	// Sample 6
	// 	{0b00000111, 0b10, 0b0, 0b10010, 0b01100, 0b0101, 0b0001},	// Sample 7
	// 	{0b00001000, 0b11, 0b1, 0b11010, 0b01010, 0b1101, 0b0001}	// Sample 8
	// 																// Add more samples as needed
	// };

	// // Write samples to RAM at specified addresses
	// for (int i = 0; i < sizeof(samples) / sizeof(samples[0]); ++i)
	// {
	// 	setHapticPatternSample(samples[i]);
	// }
}

void MAX20303::startHapticPatternFromRAM(uint8_t ramAddress)
{
	// // Trigger the haptic pattern stored in the specified RAM address
	// writeReg(REG_HPT_PATRAMADDR, ramAddress);

	// readRegMulti(REG_HPT_RAM_DATA_H, i2cbuffer_, 3);
	uint8_t haptic_data[2];
	writeReg(REG_HPT_PATRAMADDR, ramAddress);
	// wait_ms(100);
	readRegMulti(REG_HPT_RAM_DATA_H, haptic_data, 3);

	// writeReg(REG_HPT_DIRECT1, 0b11110010); // ExtTrig on, RamEn on, HptDrvEn on, Enable RAMHPI mode Drivemod set[4:0]
}
//******************************************************************************

int MAX20303::Buck2Config()
{
	int32_t ret = 0;
	appcmdoutvalue_ = 0x3A;
	appdatainoutbuffer_[0] = 0x00;
//	appdatainoutbuffer_[1] = 0x32; // 3.3V (0.05v step 0.8~3.95V)
	appdatainoutbuffer_[1] = 0x14; // 1.8V (0.05v step 0.8~3.95V)
	appdatainoutbuffer_[2] = 0x3F; // over 3V & max 375mA limit
	appdatainoutbuffer_[3] = 0x01;
	AppWrite(4);

	return ret;
}
