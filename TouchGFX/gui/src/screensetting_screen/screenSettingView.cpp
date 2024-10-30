#include <gui/screensetting_screen/screenSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

screenSettingView::screenSettingView()
	: initialX(0), initialY(0) //rkdalfks
{

}

void screenSettingView::setupScreen()
{
    screenSettingViewBase::setupScreen();
}

void screenSettingView::tearDownScreen()
{
    screenSettingViewBase::tearDownScreen();
}

#if defined(gui_simulation)
void screenSettingView::handleGestureEvent(const GestureEvent& evt)
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
    screenSettingViewBase::handleGestureEvent(evt);
}
#endif

void screenSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoSettingScreenScreenWipeTransitionWest();
}

#if !defined(gui_simulation)
#include "bl6133.h"
extern GESTURE gesture;
void screenSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
#endif
