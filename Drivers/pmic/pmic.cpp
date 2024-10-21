#include <pmic.h>
#include <MAX20303.h>
#include "main.h"

#include "cmsis_os2.h"

//******************************************************************************
MAX20303 max20303;

int pmic_init()
{
	uint8_t ret = 0;

	/* Wait for pmic to settle down */
	HAL_Delay(800);

	/*Set LDO1 to 1.8v*/
	ret |= max20303.LDO1Config(); // max 2V

	/*Set LDO2 to 3v*/
	ret |= max20303.LDO2Config();

	/*Set BK2 to 3.3v*/
	ret |= max20303.Buck2Config(); // LCD 3.3v

	//max20303.BoostEnable();
	ret |= max20303.BuckBoostEnable(); // 5V

	/* Wait for pmic to settle down */
	HAL_Delay(200);

    return 0;
}

int pmicSOCRead(unsigned char *batterylevel){
	int ret = 0;
	ret = max20303.Max20303_BatteryGauge(batterylevel);
	return ret;
}

int isBATTCharging(){
	int batteryChargeStatus = max20303.Battery_Status_Charger();
	return batteryChargeStatus;
}

void testHaptic(int hapticFrequencyHz, int hapticDuration, int hapticContinue){
	uint8_t ret = 0;
	do{
		ret = 0;
		ret |= max20303.Max20303_HapticSetting();
		ret |= max20303.Max20303_HapticSetFullScale();
		ret |= max20303.Max20303_HapticDrive0();
		ret |= max20303.Max20303_HapticDrive1();
	} while(ret != 0x00);

	max20303.Max20303_StartHapticPattern(hapticFrequencyHz, hapticDuration, hapticContinue);
}
