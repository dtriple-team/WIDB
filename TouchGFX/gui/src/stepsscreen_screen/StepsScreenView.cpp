#include <gui/stepsscreen_screen/StepsScreenView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

StepsScreenView::StepsScreenView() //rkdalfks
	: initialX(0), initialY(0)
{

}

void StepsScreenView::setupScreen()
{
    StepsScreenViewBase::setupScreen();
}

void StepsScreenView::tearDownScreen()
{
    StepsScreenViewBase::tearDownScreen();
}

void StepsScreenView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	if(evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
	{
		int deltaX = evt.getVelocity();
		if (deltaX > 0) // 오른쪽으로 스와이프
		{
			// 스와이프 이벤트 처리
			presenter->notifySwipeRight();
		}
	}
	StepsScreenViewBase::handleGestureEvent(evt);
}

void StepsScreenView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}
