#include <gui/containers/lte_status_container.hpp>

lte_status_container::lte_status_container()
{

}

void lte_status_container::initialize()
{
    lte_status_containerBase::initialize();
}

#define TICK_UPDATEHR_INTERVAL 60
uint8_t lteStatusContainerHrInterval_local = 0;
void lte_status_container::handleTickEvent(){

	lteStatusContainerHrInterval_local++;
	if(lteStatusContainerHrInterval_local == TICK_UPDATEHR_INTERVAL)
	{
	    extern uint8_t lteRSSI_0_4;
	    imageProgress1.setValue(lteRSSI_0_4);
	    imageProgress1.invalidate();

	    lteStatusContainerHrInterval_local = 0;
	}
}
