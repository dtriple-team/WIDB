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
#ifndef __MAX20303_H_
#define __MAX20303_H_


#define MAX20303_SLAVE_ADDR		(0x50 >> 1)
#define MAX20303_SLAVE_WR_ADDR		((MAX20303_SLAVE_ADDR << 1))
#define MAX20303_SLAVE_RD_ADDR		((MAX20303_SLAVE_ADDR << 1) | 1)


#define MAX20303_NO_ERROR   0
#define MAX20303_ERROR      -1

#define MAX20303_I2C_ADDR_FUEL_GAUGE    0x6C

#define MAX20303_LDO_MIN_MV 800
#define MAX20303_LDO_MAX_MV 3600
#define MAX20303_LDO_STEP_MV 100

#define MAX20303_OFF_COMMAND 0xB2

#include <stdint.h>

class MAX20303
{

public:
	/**
	 * @brief   Register Addresses
	 * @details Enumerated MAX20303 register addresses
	 */
	enum registers_t {
		REG_HARDWARE_ID		= 0x00,		///< HardwareID Register
		REG_FIRMWARE_REV	= 0x01,		///< FirmwareID Register
		//					= 0x02,		///<
		REG_INT0			= 0x03,		///< Int0 Register
		REG_INT1			= 0x04,		///< Int1 Register
		REG_INT2			= 0x05,		///< Int2 Register
		REG_STATUS0			= 0x06,		///< Status Register 0
		REG_STATUS1			= 0x07,		///< Status Register 1
		REG_STATUS2			= 0x08,		///< Status Register 2
		REG_STATUS3			= 0x09,		///< Status Register 2
		//					= 0x0A,		///<
		REG_SYSTEM_ERROR	= 0x0B,		///< SystemError Register
		REG_INT_MASK0		= 0x0C,		///< IntMask0 Register
		REG_INT_MASK1		= 0x0D,		///< IntMask1 Register
		REG_INT_MASK2		= 0x0E,		///< IntMask1 Register
		REG_AP_DATOUT0		= 0x0F,     ///< APDataOut0 Register
		REG_AP_DATOUT1		= 0x10,     ///< APDataOut1 Register
		REG_AP_DATOUT2		= 0x11,     ///< APDataOut2 Register
		REG_AP_DATOUT3		= 0x12,     ///< APDataOut3 Register
		REG_AP_DATOUT4		= 0x13,     ///< APDataOut4 Register
		REG_AP_DATOUT5		= 0x14,     ///< APDataOut5 Register
		REG_AP_DATOUT6		= 0x15,     ///< APDataOut6 Register
		REG_AP_CMDOUT		= 0x17,     ///< APCmdOut Register
		REG_AP_RESPONSE		= 0x18,     ///< APResponse Register
		REG_AP_DATAIN0		= 0x19,
		REG_AP_DATAIN1		= 0x1A,
		REG_AP_DATAIN2		= 0x1B,
		REG_AP_DATAIN3		= 0x1C,
		REG_AP_DATAIN4		= 0x1D,
		REG_AP_DATAIN5		= 0x1E,
		//					= 0x1F,		///<
		REG_LDO_DIRECT		= 0x20,
		REG_MPC_DIRECTWRITE	= 0x21,
		REG_MPC_DIRECTRED	= 0x22,

		REG_LED_STEP_DIRECT	= 0x2C,
		REG_LED0_DIRECT		= 0x2D,
		REG_LED1_DIRECT		= 0x2E,
		REG_LED2_DIRECT		= 0x2F,


		REG_LDO1_CONFIG_WRITE = 0x40,
		REG_LDO1_CONFIG_READ  = 0x41,
		REG_LDO2_CONFIG_WRITE = 0x42,
		REG_LDO2_CONFIG_READ  = 0x43,

		// 레지스터 데이터 시트 참조 임의 추가 Dtriple yeh

		REG_HPT_DIRECT0 = 0x30,
		REG_HPT_DIRECT1 = 0x31,
		REG_HPT_RTI2CAMP = 0x32,
		REG_HPT_PATRAMADDR = 0x33,
		REG_HPT_CONFIG_WRITE0 = 0xA0,
		REG_HPT_CONFIG_SETFULLCALE = 0xB2,
		REG_HPT_LOCK_CONFIG = 0xA8,
		REG_HPT_LOCK_CONFIG_READ = 0xA9,
		REG_HPT_SET_MODE = 0xAD,

		REG_HPT_RAM_ADDR = 0x28,
		REG_HPT_RAM_DATA_H = 0x29,
		REG_HPT_RAM_DATA_M = 0x2A,
		REG_HPT_RAM_DATA_L = 0x2B,

		/*
		REG_CHG_TMR = 0x0C,   ///< Charger Timers
		REG_BUCK1_CFG = 0x0D,   ///< Buck 1 Configuration
		REG_BUCK1_VSET = 0x0E,   ///< Buck 1 Voltage Setting
		REG_BUCK2_CFG = 0x0F,   ///< Buck 2 Configuration
		REG_BUCK2_VSET = 0x10,   ///< Buck 2 Voltage Setting
		REG_RSVD_11 = 0x11,   ///< Reserved 0x11
		REG_LDO1_CFG = 0x12,   ///< LDO 1 Configuration
		REG_LDO1_VSET = 0x13,   ///< LDO 1 Voltage Setting
		REG_LDO2_CFG = 0x14,   ///< LDO 2 Configuration
		REG_LDO2_VSET = 0x15,   ///< LDO 2 Voltage Setting
		REG_LDO3_CFG = 0x16,   ///< LDO 3 Configuration
		REG_LDO3_VSET = 0x17,   ///< LDO 3 Voltage Setting
		REG_THRM_CFG = 0x18,   ///< Thermistor Configuration
		REG_MON_CFG = 0x19,   ///< Monitor Multiplexer Configuration
		REG_BOOT_CFG = 0x1A,   ///< Boot Configuration
		REG_PIN_STATUS = 0x1B,   ///< Pin Status
		REG_BUCK_EXTRA = 0x1C,   ///< Additional Buck Settings
		REG_PWR_CFG = 0x1D,   ///< Power Configuration
		REG_NULL = 0x1E,   ///< Reserved 0x1E
		REG_PWR_OFF = 0x1F,   ///< Power Off Register
		*/

//		MAX20303_I2C_ADDR_FUEL_GAUGE = 0x6C
	};

	struct HapticPatternSample
	{
		uint8_t HptRAMAddr; // The RAM address in which the pattern sample is stored [7:0]
		uint8_t nLSx;		// Amplitude of the sample [1:0]
		uint8_t AmpSign;	// Sign of haptic amplitude in the current sample [1:0]
		uint8_t Amp;		// Sets the amplitude of pattern sample x as a 7-bit percentage of VFS and a 1-bit direction.
							// See HptVfs[7:0] in Table 131. [6:2]
		uint8_t Dur;		// Sets the duration of time the driver outputs the amplitude of the current sample in increments of 5ms [4:0]
		uint8_t Wait;		// Sets the duration of time the driver waits at zero amplitude before the next sample in increments of 5ms [4:0]
		uint8_t RPTx;		// Sets the number of times to repeat the sample before moving to the next sample in the pattern. If nLSx[1:0] = 11,
							// this sets the number of times to repeat the whole pattern. [3:0]
	};

	/**
	* @brief  Constructor using reference to I2C object
	* @param i2c - Reference to I2C object
	* @param slaveAddress - 7-bit I2C address
	*/
//	MAX20303(I2C *i2c);
	MAX20303();

	/** @brief Destructor */
	~MAX20303(void);

	int led0on(char enable);
	int led1on(char enable);
	int led2on(char enable);
	int BoostEnable(void);
	int BuckBoostEnable(void);

	/// @brief Enable the 1.8V output rail **/
	int LDO1Config(void);

	/// @brief Enable the 3V output rail **/
	int LDO2Config(void);


	int mv2bits(int mV);

	/** @brief Power Off the board
	 */
	int PowerOffthePMIC();

	/** @brief Power Off the board with 30ms delay
	 */
	int PowerOffDelaythePMIC();

	/** @brief Soft reset the PMIC
	 */
	int SoftResetthePMIC();

	/** @brief Hard reset the PMIC
	 */
	int HardResetthePMIC();

	/** @brief check if can communicate with max20303
	*/
	char CheckPMICHWID();

	/** @brief CheckPMICStatusRegisters
	*/
	int CheckPMICStatusRegisters(unsigned char buf_results[5]);

    int Max20303_BatteryGauge(unsigned char *batterylevel);

    int Buck2Config(void);

    // check if the battery is connected.
    // Warning: that function has 1000ms delay
    char Max20303_IsBattery_Connected();
	uint8_t Battery_Status_Charger();


	// dtirple yeh 햅틱 변수 추가
	int Max20303_HapticSetting();
	int Max20303_HapticSetFullScale();
	int Max20303_HapticDrive0();
	int Max20303_HapticDrive1();
	int Max20303_HapticStatus();
	int Max20303_HapticDriveStatus();
	int Max20303_HapticStart();
	int Max20303_HapticStop();
	int Max20303_HapticUnlock();

	void Max20303_StartHapticPattern(int hapticFrequencyHz, int hapticDuration, int hapticContinue);
	void writeHapticPatternSample(uint8_t ramAddress, HapticPatternSample sample);
	void setHapticPatternSample(const HapticPatternSample &sample);
	void createHapticPattern();
	void startHapticPatternFromRAM(uint8_t ramAddress);

private:

	int writeReg(registers_t reg, uint8_t value);
	int readReg(registers_t reg, uint8_t &value);

	int writeRegMulti(registers_t reg, uint8_t *value, uint8_t len);
	int readRegMulti(registers_t reg, uint8_t *value, uint8_t len);

//	/// I2C object
//	I2C  *m_i2c;

	/// Device slave addresses
	uint8_t m_writeAddress, m_readAddress;

	// Application Processor Interface Related Variables
	uint8_t i2cbuffer_[16];
	uint8_t appdatainoutbuffer_[8];
	uint8_t appcmdoutvalue_;

	// check if the battery is connected
	char m_battery_is_connected;

	/** @brief API Related Functions ***/

	/***
	 *  @brief  starts writing from ApResponse register 0x0F
	 *  check the datasheet to determine the value of dataoutlen
	 */
	int AppWrite(uint8_t dataoutlen);

	/** @brief starts reading from ApResponse register 0x18
	 *  check the datasheet to determine the value of datainlen
	 *  the result values are written into i2cbuffer
	 *
	*/
	int AppRead(uint8_t datainlen);
};

#endif /* __MAX20303_H_ */
