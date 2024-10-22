#include <gui/containers/batteryprogress_container.hpp>

batteryprogress_container::batteryprogress_container()
{

}

void batteryprogress_container::initialize()
{
    batteryprogress_containerBase::initialize();
}

#define TICK_UPDATEHR_INTERVAL 60
uint8_t batteryprogressContainerHrInterval_local = 0;
void batteryprogress_container::handleTickEvent(){

	batteryprogressContainerHrInterval_local++;
	if(batteryprogressContainerHrInterval_local == TICK_UPDATEHR_INTERVAL)
	{
		extern uint8_t battVal;
		batteryprogress.setValue(battVal);
		batteryprogress.invalidate();
		extern bool isCharging;
		chargingIMG.setVisible(isCharging);
		chargingIMG.invalidate();

	    batteryprogressContainerHrInterval_local = 0;
	}
}
