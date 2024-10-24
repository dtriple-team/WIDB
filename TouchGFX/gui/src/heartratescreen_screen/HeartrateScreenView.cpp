#include <gui/heartratescreen_screen/HeartrateScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

HeartrateScreenView::HeartrateScreenView()
	: initialX(0), initialY(0) //rkdalfks
{

}

void HeartrateScreenView::setupScreen()
{
    HeartrateScreenViewBase::setupScreen();
}

void HeartrateScreenView::tearDownScreen()
{
    HeartrateScreenViewBase::tearDownScreen();
}

//void HeartrateScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
//{
//	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
//	{
//    	int deltaX = evt.getVelocity();
//        //int deltaY = evt.getVelocityY();
//
//        //if(abs(deltaX)>abs(deltaY))
//        //{
//			if(deltaX>0)
//			{
//				presenter->notifySwipeRight();
//			}
//        //}
//	}
//	HeartrateScreenViewBase::handleGestureEvent(evt);
//}

void HeartrateScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

extern uint16_t ssHr;
void HeartrateScreenView::changeHRVal(){
	touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
	heartrate_value.invalidate();
}

#include "bl6133.h"
extern GESTURE gesture;
void HeartrateScreenView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
