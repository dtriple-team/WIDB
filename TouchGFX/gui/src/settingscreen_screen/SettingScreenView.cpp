#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

SettingScreenView::SettingScreenView()
	: initialX(0), initialY(0)
{

}

void SettingScreenView::setupScreen()
{
    SettingScreenViewBase::setupScreen();
}

void SettingScreenView::tearDownScreen()
{
    SettingScreenViewBase::tearDownScreen();
}

#if defined(gui_simulation)
void SettingScreenView::handleGestureEvent(const GestureEvent& evt)
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
	SettingScreenViewBase::handleGestureEvent(evt);
}
#endif

void SettingScreenView::handleSwipeRight()
{
	application().gotoswipedownfromHomeScreenWipeTransitionWest();
}
#if !defined(gui_simulation)
#include "bl6133.h"
extern GESTURE gesture;
void SettingScreenView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
#endif
