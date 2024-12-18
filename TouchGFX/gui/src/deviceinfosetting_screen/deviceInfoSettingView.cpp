#include <gui/deviceinfosetting_screen/deviceInfoSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#include <stdio.h>
#include "nrf9160.h"
#include <string.h>

deviceInfoSettingView::deviceInfoSettingView()
	: initialX(0), initialY(0)
{

}

void deviceInfoSettingView::setupScreen()
{
    deviceInfoSettingViewBase::setupScreen();

#if !defined(gui_simulation)
    extern uint32_t deviceID;
    char model[6] = "eHG4M";
    char version[7] = "v1.0.0";
    extern cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
    char serviceNumber_ascii[16+1] = {0,};
    memcpy(serviceNumber_ascii, &cat_m1_at_cmd_rst.cnum[4], 16);
    uint64_t serviceNumber = atoi(serviceNumber_ascii);
//    char strDeviceID[10];
//
//    sprintf(strDeviceID, "%d", deviceID);

	Unicode::snprintf(model_labelBuffer, MODEL_LABEL_SIZE, model);
	model_label.invalidate();
	Unicode::snprintf(version_labelBuffer, VERSION_LABEL_SIZE, version);
	version_label.invalidate();
	Unicode::snprintf(id_labelBuffer, ID_LABEL_SIZE, "0x%.8x", deviceID);
	id_label.invalidate();
	Unicode::snprintf(servicenumber_labelBuffer, SERVICENUMBER_LABEL_SIZE, serviceNumber_ascii);
	servicenumber_label.invalidate();
#endif
}

void deviceInfoSettingView::tearDownScreen()
{
    deviceInfoSettingViewBase::tearDownScreen();
}

#if defined(gui_simulation)
void deviceInfoSettingView::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if (deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
        //}
    }
    deviceInfoSettingViewBase::handleGestureEvent(evt);
}
#endif

void deviceInfoSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoinformationSettingScreenWipeTransitionWest();
}

#if !defined(gui_simulation)
#include "bl6133.h"
extern GESTURE gesture;
void deviceInfoSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
#endif
