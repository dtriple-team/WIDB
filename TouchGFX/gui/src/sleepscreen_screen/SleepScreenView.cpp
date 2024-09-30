#include <gui/sleepscreen_screen/SleepScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

SleepScreenView::SleepScreenView()
    : initialX(0), initialY(0) //rkdalfks
{
}

void SleepScreenView::setupScreen()
{
    SleepScreenViewBase::setupScreen();
}

void SleepScreenView::tearDownScreen()
{
    SleepScreenViewBase::tearDownScreen();
}

void SleepScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
    SleepScreenViewBase::handleGestureEvent(evt);
}

void SleepScreenView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}
