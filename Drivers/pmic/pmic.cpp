#include <pmic.h>
#include <MAX20303.h>
#include "main.h"

//******************************************************************************
MAX20303 max20303;

int pmic_init()
{

	/* Wait for pmic to settle down */
	HAL_Delay(800);

	/*Set LDO1 to 1.8v*/
	max20303.LDO1Config();

	/*Set LDO2 to 3v*/
    max20303.LDO2Config();

	//max20303.BoostEnable();
	max20303.BuckBoostEnable();

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
