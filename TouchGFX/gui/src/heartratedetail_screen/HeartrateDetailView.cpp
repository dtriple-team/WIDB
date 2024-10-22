#include <gui/heartratedetail_screen/HeartrateDetailView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

HeartrateDetailView::HeartrateDetailView()
	: initialX(0), initialY(0)
{
}

void HeartrateDetailView::setupScreen()
{
    HeartrateDetailViewBase::setupScreen();
}

void HeartrateDetailView::tearDownScreen()
{
    HeartrateDetailViewBase::tearDownScreen();
}

//void HeartrateDetailView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
//	HeartrateDetailViewBase::handleGestureEvent(evt);
//}

void HeartrateDetailView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

#include "bl6133.h"
#define TICK_UPDATEHR_INTERVAL 60
extern GESTURE gesture;
uint32_t frameCountUpdateHrInterval_local = 0;
void HeartrateDetailView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}

	frameCountUpdateHrInterval_local++;
	if(frameCountUpdateHrInterval_local == TICK_UPDATEHR_INTERVAL)
	{
		extern uint8_t canDisplayPPG;
		if(!canDisplayPPG) return;

		canDisplayPPG = 0;

		extern uint16_t ssHr;

		touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
		heartrate_value.invalidate();
		frameCountUpdateHrInterval_local = 0;
	}
}
