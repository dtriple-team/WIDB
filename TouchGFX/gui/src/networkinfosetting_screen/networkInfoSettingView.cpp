#include <gui/networkinfosetting_screen/networkInfoSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

networkInfoSettingView::networkInfoSettingView()
	: initialX(0), initialY(0)
{

}

void networkInfoSettingView::setupScreen()
{
    networkInfoSettingViewBase::setupScreen();
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
