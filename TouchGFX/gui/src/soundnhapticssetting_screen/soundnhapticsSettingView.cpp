#include <gui/soundnhapticssetting_screen/soundnhapticsSettingView.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

soundnhapticsSettingView::soundnhapticsSettingView()
	: toggleButton1ClickedCallback(this, &soundnhapticsSettingView::toggleButton1Clicked), //test
	  toggleButton2ClickedCallback(this, &soundnhapticsSettingView::toggleButton2Clicked),
	  initialX(0), initialY(0)
{

}

void soundnhapticsSettingView::setupScreen()
{
    soundnhapticsSettingViewBase::setupScreen();
    haptic_togglebutton.setAction(toggleButton1ClickedCallback);
    sound_togglebutton.setAction(toggleButton2ClickedCallback);
    haptic_togglebutton.forceState(presenter->getToggleButton1State()); //test
    sound_togglebutton.forceState(presenter->getToggleButton2State()); //test
}

void soundnhapticsSettingView::tearDownScreen()
{
    soundnhapticsSettingViewBase::tearDownScreen();
}

//void soundnhapticsSettingView::handleGestureEvent(const GestureEvent& evt)
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
//    soundnhapticsSettingViewBase::handleGestureEvent(evt);
//}

void soundnhapticsSettingView::handleSwipeRight()
{
    application().gotoSettingScreenScreenWipeTransitionWest();
}

void soundnhapticsSettingView::toggleButton1Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = haptic_togglebutton.getState();
    presenter->updateToggleButton1State(newState);

    extern uint8_t hapticFlag;
    hapticFlag = !hapticFlag;
}

void soundnhapticsSettingView::updateToggleButton1State(bool state)
{
	haptic_togglebutton.forceState(state);
}

void soundnhapticsSettingView::toggleButton2Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = sound_togglebutton.getState();
    presenter->updateToggleButton2State(newState);

    extern uint8_t soundFlag;
	soundFlag = !soundFlag;
}

void soundnhapticsSettingView::updateToggleButton2State(bool state)
{
	sound_togglebutton.forceState(state);
}

#include "bl6133.h"
extern GESTURE gesture;
void soundnhapticsSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
