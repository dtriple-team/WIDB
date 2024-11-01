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

#if defined(gui_simulation)
void HeartrateScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	const int swipeThreshold = 20;
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
    	int deltaX = evt.getVelocity();

    	if(abs(deltaX) > swipeThreshold)
    	{
    		if(deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
    		if(deltaX < 0)
			{
				presenter->notifySwipeLeft();
			}
    	}
	}
	HeartrateScreenViewBase::handleGestureEvent(evt);
}
#endif

void HeartrateScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoStepsScreenScreenWipeTransitionWest();
}

void HeartrateScreenView::handleSwipeLeft() //rkdalfks
{
	application().gotoSpo2ScreenScreenWipeTransitionEast();
}

#if !defined(gui_simulation)
extern uint16_t ssHr;
void HeartrateScreenView::changeHRVal(){
	touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
	heartrate_value.invalidate();
}

#include "bl6133.h"
extern GESTURE gesture;
uint32_t frameCountInteraction4Interval_local=0;
void HeartrateScreenView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
	else if(gesture == SlideLeft){
		presenter->notifySwipeLeft();
	}
	else if(gesture == SlideDown){
		application().gotoswipedownfromHomeScreenCoverTransitionNorth();
	}
	else if(gesture == LongPress){
		application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
	}

	frameCountInteraction4Interval_local++;
	if(frameCountInteraction4Interval_local == 60)
	{
		//Interaction4
		//When every N tick call changeHRVal on HeartrateScreen
		//Call changeHRVal
		changeHRVal();
		frameCountInteraction4Interval_local = 0;
	}
}
#endif
