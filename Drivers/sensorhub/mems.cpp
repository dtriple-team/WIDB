/*
 * mems.cpp
 *
 *  Created on: Jun 24, 2024
 *      Author: D-triple
 */


#include "mems.h"
#include "i2c.h"

//#include "app_FreeFallDetection.h"

void init_iis2mdc(){
	uint8_t err = 0;
	uint8_t tx_data[2] = {0,};

	tx_data[0] = IIS2MDC_CFG_REG_A;
	tx_data[1] = 0x20;
	err |= HAL_I2C_Master_Transmit(&hi2c1, IIS2MDC_ADDR_W, tx_data, 2, 100);

	tx_data[0] = IIS2MDC_CFG_REG_A;
	tx_data[1] = 0x80;
	err |= HAL_I2C_Master_Transmit(&hi2c1, IIS2MDC_ADDR_W, tx_data, 2, 100);

	tx_data[0] = IIS2MDC_CFG_REG_C;
	tx_data[1] = 0x01;
	err |= HAL_I2C_Master_Transmit(&hi2c1, IIS2MDC_ADDR_W, tx_data, 2, 100);
}

void read_iis2mdc(double* magnetX, double* magnetY, double* magnetZ, double* temp){
	uint8_t err = 0;
	uint8_t data[6] = {0,};
	uint8_t startRegAddr = 0;

	startRegAddr = IIS2MDC_OUTX_L_REG;
	err |= HAL_I2C_Mem_Read(&hi2c1, IIS2MDC_ADDR_W+1, (uint16_t)startRegAddr, 1, data, sizeof(data), 100);

	if(err == HAL_OK);
	else;

//	*magnetX = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
//	*magnetY = ((uint16_t)data[3])<<8 | ((uint16_t)data[2]);
//	*magnetZ = ((uint16_t)data[5])<<8 | ((uint16_t)data[4]);

	uint8_t magnetSensitivity = 15; // mgauss/LSB
	int16_t magnetValueX = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
	*magnetX = (1.0*magnetValueX)*(1.0*magnetSensitivity/10.0);
	int16_t magnetValueY = ((uint16_t)data[3])<<8 | ((uint16_t)data[2]);
	*magnetY = (1.0*magnetValueY)*(1.0*magnetSensitivity/10.0);
	int16_t magnetValueZ = ((uint16_t)data[5])<<8 | ((uint16_t)data[4]);
	*magnetZ = (1.0*magnetValueZ)*(1.0*magnetSensitivity/10.0);

//	uint8_t tempSensitivity = 8; // LSB/deg
//	int16_t tempValue = ((uint16_t)data[7])<<8 | ((uint16_t)data[6]);
//	*temp = (1.0*tempValue)/(1.0*tempSensitivity)+25; // deg

	startRegAddr = IIS2MDC_TEMP_OUT_L_REG;
	err |= HAL_I2C_Mem_Read(&hi2c1, IIS2MDC_ADDR_W+1, (uint16_t)startRegAddr, 1, data, 2, 100);

	if(err == HAL_OK);
	else;

	uint8_t tempSensitivity = 8; // LSB/deg
	int16_t tempValue = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
	*temp = (1.0*tempValue)/(1.0*tempSensitivity)+25; // deg


	return;
}
//
//void init_ism330dhcx(){
//	uint8_t err = 0;
//	uint8_t tx_data[2] = {0,};
//
//	tx_data[0] = ISM330DHCX_CTRL3_C;
//	tx_data[1] = 0x01; // SW reset
//	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);
//
//	tx_data[0] = ISM330DHCX_CTRL9_XL;
//	tx_data[1] = 0x02; // Device Configuration Enable (0: disable)
//	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);
//
//	tx_data[0] = ISM330DHCX_CTRL1_XL;
//	tx_data[1] = 0x62; // 416Hz ODR | LPF2_XL_EN
//	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);
//
//	tx_data[0] = ISM330DHCX_CTRL2_G;
//	tx_data[1] = 0x62; // 416Hz ODR | DFull Scale +-125dps
//	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);
//}

void init_ism330dhcx(){ // 주석 설명 필요
	uint8_t err = 0;
	uint8_t tx_data[2] = {0,};

	tx_data[0] = ISM330DHCX_CTRL3_C;
	tx_data[1] = 0x41;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_CTRL9_XL;
	tx_data[1] = 0x02;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);



	tx_data[0] = ISM330DHCX_WAKE_UP_DUR;
	tx_data[1] = 0x06;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_FREE_FALL;
	tx_data[1] = 0x33;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_MD1_CFG;
	tx_data[1] = 0x10;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_INT1_CTRL;
	tx_data[1] = 0x10;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_TAP_CFG2;
	tx_data[1] = 0x80; // interrupt enable
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_TAP_THS_6D;
	tx_data[1] = 0x80; // interrupt enable
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_CTRL2_G;
	tx_data[1] = 0x62;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);

	tx_data[0] = ISM330DHCX_CTRL1_XL;
	tx_data[1] = 0x62;
	err |= HAL_I2C_Master_Transmit(&hi2c1, ISM330DHCX_ADDR_W, tx_data, 2, 100);
}

void read_ism330dhcx(uint16_t gyroSensi, uint8_t accSensi, double* temp, double* gyroX, double* gyroY, double* gyroZ, double* accX, double* accY, double* accZ){
	uint8_t err = 0;
	uint8_t data[14] = {0,};
	uint8_t startRegAddr = 0;

	// reset access to the embedded functions configuration registers
	err |= HAL_I2C_Mem_Write(&hi2c1, ISM330DHCX_ADDR_W, 0x01, 1, 0x00, 1, 100);

	startRegAddr = ISM330DHCX_OUT_TEMP_L;
	err |= HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_ADDR_W+1, (uint16_t)startRegAddr, 1, data, sizeof(data), 100);

	if(err == HAL_OK);
	else;

//	*temp = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
//
//	*gyroX = ((uint16_t)data[3])<<8 | ((uint16_t)data[2]);
//	*gyroY = ((uint16_t)data[5])<<8 | ((uint16_t)data[4]);
//	*gyroZ = ((uint16_t)data[7])<<8 | ((uint16_t)data[6]);
//
//	*accX = ((uint16_t)data[9])<<8 | ((uint16_t)data[8]);
//	*accY = ((uint16_t)data[11])<<8 | ((uint16_t)data[10]);
//	*accZ = ((uint16_t)data[13])<<8 | ((uint16_t)data[12]);

	uint16_t tempSensitivity = 256; // LSB/deg
	int16_t tempValue = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
	*temp = (1.0*tempValue)/(1.0*tempSensitivity)+25.0; // deg

	uint16_t unitGyroSensitivity = 4375; // mdps/LSB
	int16_t gyroValueX = ((uint16_t)data[3])<<8 | ((uint16_t)data[2]);
	*gyroX = (1.0*gyroValueX)*(1.0*unitGyroSensitivity/1000.0)*gyroSensi/125.0;
	int16_t gyroValueY = ((uint16_t)data[5])<<8 | ((uint16_t)data[4]);
	*gyroY = (1.0*gyroValueY)*(1.0*unitGyroSensitivity/1000.0)*gyroSensi/125.0;
	int16_t gyroValueZ = ((uint16_t)data[7])<<8 | ((uint16_t)data[6]);
	*gyroZ = (1.0*gyroValueZ)*(1.0*unitGyroSensitivity/1000.0)*gyroSensi/125.0;

	uint8_t unitAccSensitivity = 61; // mg/LSB
	int16_t accValueX = ((uint16_t)data[9])<<8 | ((uint16_t)data[8]);
	*accX = (1.0*accValueX)*(1.0*unitAccSensitivity/1000.0)*accSensi/2.0;
	int16_t accValueY = ((uint16_t)data[11])<<8 | ((uint16_t)data[10]);
	*accY = (1.0*accValueY)*(1.0*unitAccSensitivity/1000.0)*accSensi/2.0;
	int16_t accValueZ = ((uint16_t)data[13])<<8 | ((uint16_t)data[12]);
	*accZ = (1.0*accValueZ)*(1.0*unitAccSensitivity/1000.0)*accSensi/2.0;

	return;
}

//void ism330dhcxINTEnable(){
//
//	// free-fall detect
//	uint8_t intrr_data[1] = {0,};
//	uint8_t is_free_fall_in_reg = 0;
//	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_ADDR_W+1, (uint16_t)ISM330DHCX_ALL_INT_SRC, 1, intrr_data, sizeof(intrr_data), 100);
//	if((uint8_t)intrr_data[0] & 0x01 == 0x01){
//		is_free_fall_in_reg = 1;
//	}
//
//	return;
//}

uint8_t whatKindInterrupt(){
	uint8_t intrr_data[1] = {0,};
	HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_ADDR_W+1, (uint16_t)ISM330DHCX_ALL_INT_SRC, 1, intrr_data, sizeof(intrr_data), 100);

	return intrr_data[0];
	/*
	 * In intrr_data[0]
	 * bit[5] change activity/inactivity
	 * bit[4] change position change ( position of portrait, landscape, face-up, face-down)
	 * bit[3] double tap
	 * bit[2] single tap
	 * bit[1] wake-up
	 * bit[0] free-fall
	 */
}

void read_ism330dhcx_stepCount(uint16_t *stepCount){
//	uint8_t err = 0;
//	uint8_t data[2] = {0,};
//	uint8_t startRegAddr = 0x62;
//
//	// Enable access to the embedded functions configuration registers
//	uint8_t wData[1] = {0x80};
//	err |= HAL_I2C_Mem_Write(&hi2c1, ISM330DHCX_ADDR_W, 0x0001, 1, wData, 1, 100);
//
//	startRegAddr = ISM330DHCX_OUT_TEMP_L;
//	err |= HAL_I2C_Mem_Read(&hi2c1, ISM330DHCX_ADDR_W+1, (uint16_t)startRegAddr, 1, data, sizeof(data), 100);
//
//	if(err == HAL_OK);
//	else;
//
//	*stepCount = ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);

	return;
}

void init_lps22hh(){
	uint8_t err = 0;
	uint8_t tx_data[2] = {0,};

	tx_data[0] = LPS22HH_CTRL_REG2;
	tx_data[1] = 0x04;
	err |= HAL_I2C_Master_Transmit(&hi2c1, LPS22HH_ADDR_W, tx_data, 2, 100);

	tx_data[0] = LPS22HH_CTRL_REG1;
	tx_data[1] = 0x50;
	err |= HAL_I2C_Master_Transmit(&hi2c1, LPS22HH_ADDR_W, tx_data, 2, 100);

}

void read_lps22hh(double* pressure, double* temp){
	uint8_t err = 0;
	uint8_t data[5] = {0,};
	uint8_t startRegAddr = 0;

	startRegAddr = LPS22HH_PRESSURE_OUT_XL;
	err |= HAL_I2C_Mem_Read(&hi2c1, LPS22HH_ADDR_W+1, (uint16_t)startRegAddr, 1, data, sizeof(data), 100);

	if(err == HAL_OK);
	else;

	uint16_t pressureSensitivity = 4096; // LSB/hPa
	uint32_t pressureValue = ((uint16_t)data[2])<<16 | ((uint16_t)data[1])<<8 | ((uint16_t)data[0]);
	*pressure = (1.0*pressureValue)/(1.0*pressureSensitivity); // hPa

	uint8_t tempSensitivity = 100; // LSB/deg
	int16_t tempValue = ((uint16_t)data[4])<<8 | ((uint16_t)data[3]);
	*temp = (1.0*tempValue)/(1.0*tempSensitivity); // deg

	return;
}
