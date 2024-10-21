#include <gui/networkinfosetting_screen/networkInfoSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#include <nrf9160.h>
#include <stdio.h>

networkInfoSettingView::networkInfoSettingView()
	: initialX(0), initialY(0)
{

}

void networkInfoSettingView::setupScreen()
{
    networkInfoSettingViewBase::setupScreen();

    char imei[6];
    char iccid[20];

    extern cat_m1_at_cmd_rst_t cat_m1_at_cmd_rst;
    sprintf(imei, "%.5s", &(cat_m1_at_cmd_rst.cops[6]));
    sprintf(iccid, "%s", cat_m1_at_cmd_rst.iccid);

    Unicode::snprintf(imei_labelBuffer, IMEI_LABEL_SIZE, imei);
	imei_label.invalidate();
	Unicode::snprintf(iccid_labelBuffer, ICCID_LABEL_SIZE, iccid);
	iccid_label.invalidate();
}

void networkInfoSettingView::tearDownScreen()
{
    networkInfoSettingViewBase::tearDownScreen();
}

//void networkInfoSettingView::handleGestureEvent(const GestureEvent& evt)
//{
//    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
//    {
//    	int deltaX = evt.getVelocity();
//        //int deltaY = evt.getVelocityY();
//
//        //if(abs(deltaX)>abs(deltaY))
//        //{
//			if (deltaX > 0)
//			{
//				presenter->notifySwipeRight();
//			}
//        //}
//    }
//    networkInfoSettingViewBase::handleGestureEvent(evt);
//}

void networkInfoSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoinformationSettingScreenWipeTransitionWest();
}

#include "bl6133.h"
extern GESTURE gesture;
void networkInfoSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
