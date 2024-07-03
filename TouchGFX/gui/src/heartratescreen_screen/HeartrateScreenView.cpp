#include <gui/heartratescreen_screen/HeartrateScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

extern uint16_t ssHr;

HeartrateScreenView::HeartrateScreenView()
	: initialX(0), initialY(0) //rkdalfks
{

}

void HeartrateScreenView::setupScreen()
{
    HeartrateScreenViewBase::setupScreen();
}

void HeartrateScreenView::tearDownScreen()
{
    HeartrateScreenViewBase::tearDownScreen();
}

void HeartrateScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
		int deltaX = evt.getVelocity();
		if(deltaX>0)
		{
			presenter->notifySwipeRight();
		}
	}
	HeartrateScreenViewBase::handleGestureEvent(evt);
}

void HeartrateScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

void HeartrateScreenView::changeHRVal(){
	timeTick++;

	if(timeTick%60 == 0){

		touchgfx::Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%02u", ssHr);
		textArea1.invalidate();
	}
}
