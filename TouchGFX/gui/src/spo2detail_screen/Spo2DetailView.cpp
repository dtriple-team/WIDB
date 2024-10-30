#include <gui/spo2detail_screen/Spo2DetailView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

Spo2DetailView::Spo2DetailView()
{

}

void Spo2DetailView::setupScreen()
{
    Spo2DetailViewBase::setupScreen();
}

void Spo2DetailView::tearDownScreen()
{
    Spo2DetailViewBase::tearDownScreen();
}

#if defined(gui_simulation)
void Spo2DetailView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if(deltaX>0)
			{
				presenter->notifySwipeRight();
			}
        //}
	}
	Spo2DetailViewBase::handleGestureEvent(evt);
}
#endif

void Spo2DetailView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

#if !defined(gui_simulation)
#include "bl6133.h"
#define TICK_UPDATESPO2_INTERVAL 60
extern GESTURE gesture;
uint32_t frameCountUpdateSpo2Interval_local = 0;
void Spo2DetailView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}

	frameCountUpdateSpo2Interval_local++;
	if(frameCountUpdateSpo2Interval_local == TICK_UPDATESPO2_INTERVAL)
	{
		extern uint8_t canDisplayPPG;
		if(!canDisplayPPG) return;

		canDisplayPPG = 0;

		extern uint16_t ssSpo2;

		touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
		spo2_value.invalidate();
		frameCountUpdateSpo2Interval_local = 0;
	}
}
#endif
