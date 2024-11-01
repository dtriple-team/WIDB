#include <gui/stepsscreen_screen/StepsScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

StepsScreenView::StepsScreenView() //rkdalfks
	: initialX(0), initialY(0)
{

}

void StepsScreenView::setupScreen()
{
    StepsScreenViewBase::setupScreen();

    extern uint32_t ssWalk;
	touchgfx::Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%02u", ssWalk);
	steps_value.invalidate();
}

void StepsScreenView::tearDownScreen()
{
    StepsScreenViewBase::tearDownScreen();
}
#if defined(gui_simulation)
void StepsScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
	StepsScreenViewBase::handleGestureEvent(evt);
}
#endif

void StepsScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

void StepsScreenView::handleSwipeLeft() //rkdalfks
{
	application().gotoHeartrateScreenScreenWipeTransitionEast();
}

#if !defined(gui_simulation)
void StepsScreenView::changeStepVal(){
	extern uint32_t ssWalk;
	touchgfx::Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%02u", ssWalk);
	steps_value.invalidate();
}

#include "bl6133.h"
extern GESTURE gesture;
uint32_t frameCountInteraction3Interval_local = 0;
void StepsScreenView::handleTickEvent(){
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

	frameCountInteraction3Interval_local++;
	if(frameCountInteraction3Interval_local == 60)
	{
		//Interaction3
		//When every N tick call changeStepVal on StepsScreen
		//Call changeStepVal
		changeStepVal();
		frameCountInteraction3Interval_local = 0;
	}
}
#endif
