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
}

void StepsScreenView::tearDownScreen()
{
    StepsScreenViewBase::tearDownScreen();
}

//void StepsScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
//{
//	if(evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
//	{
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
//	}
//	StepsScreenViewBase::handleGestureEvent(evt);
//}

void StepsScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

extern uint32_t ssWalk;
void StepsScreenView::changeStepVal(){
	touchgfx::Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%02u", ssWalk);
	steps_value.invalidate();
}

#include "bl6133.h"
extern GESTURE gesture;
void StepsScreenView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
