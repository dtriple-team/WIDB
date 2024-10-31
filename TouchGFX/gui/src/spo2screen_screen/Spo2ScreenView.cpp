#include <gui/spo2screen_screen/Spo2ScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks


Spo2ScreenView::Spo2ScreenView()
    : initialX(0), initialY(0) //rkdalfks
{
}

void Spo2ScreenView::setupScreen()
{
    Spo2ScreenViewBase::setupScreen();
}

void Spo2ScreenView::tearDownScreen()
{
    Spo2ScreenViewBase::tearDownScreen();
}
#if defined(gui_simulation)
void Spo2ScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
			if (deltaX < 0)
			{
				presenter->notifySwipeLeft();
			}
        //}
    }
    Spo2ScreenViewBase::handleGestureEvent(evt);
}
#endif

void Spo2ScreenView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoHeartrateScreenScreenWipeTransitionWest();
}

void Spo2ScreenView::handleSwipeLeft() //rkdalfks
{
    // 화면 전환 코드
    application().gotoHomeScreenWithBiodataScreenWipeTransitionEast();
}

#if !defined(gui_simulation)
extern uint16_t ssSpo2;
void Spo2ScreenView::changeSpo2Val(){
	touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
	spo2_value.invalidate();
}

#include "bl6133.h"
extern GESTURE gesture;
void Spo2ScreenView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
	else if(gesture == SlideLeft){
//		application().gotoHomeScreenWithBiodataScreen
	}
	else if(gesture == SlideDown){
		application().gotoswipedownfromHomeScreenCoverTransitionNorth();
	}
	else if(gesture == LongPress){
		application().gotoHomeScreenWithBiodataScreenSlideTransitionWest();
	}
}
#endif
