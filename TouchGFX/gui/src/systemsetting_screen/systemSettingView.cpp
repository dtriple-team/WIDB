#include <gui/systemsetting_screen/systemSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

systemSettingView::systemSettingView()
	: initialX(0), initialY(0)
{

}

void systemSettingView::setupScreen()
{
    systemSettingViewBase::setupScreen();
}

void systemSettingView::tearDownScreen()
{
    systemSettingViewBase::tearDownScreen();
}

//void systemSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
//    systemSettingViewBase::handleGestureEvent(evt);
//}

void systemSettingView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoSettingScreenScreenWipeTransitionWest();
}

#include "bl6133.h"
extern GESTURE gesture;
void systemSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
