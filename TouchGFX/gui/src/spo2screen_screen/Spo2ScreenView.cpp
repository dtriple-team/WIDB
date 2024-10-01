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
        //}
    }
    Spo2ScreenViewBase::handleGestureEvent(evt);
}

void Spo2ScreenView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}

extern uint16_t ssSpo2;
void Spo2ScreenView::changeSpo2Val(){
	touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
	spo2_value.invalidate();
}

