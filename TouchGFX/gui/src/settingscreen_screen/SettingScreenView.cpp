#include <gui/settingscreen_screen/SettingScreenView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

SettingScreenView::SettingScreenView()
	: initialX(0), initialY(0)
{

}

void SettingScreenView::setupScreen()
{
    SettingScreenViewBase::setupScreen();
}

void SettingScreenView::tearDownScreen()
{
    SettingScreenViewBase::tearDownScreen();
}

void SettingScreenView::handleGestureEvent(const GestureEvent& evt)
{
	if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
	{
		int deltaX = evt.getVelocity();
		if (deltaX > 0) // 오른쪽으로 스와이프
		{
			// 스와이프 이벤트 처리
			presenter->notifySwipeRight();
		}
	}
	SettingScreenViewBase::handleGestureEvent(evt);
}

void SettingScreenView::handleSwipeRight()
{
	application().gotoswipedownfromHomeScreenWipeTransitionWest();
}
