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

void networkInfoSettingView::handleGestureEvent(const GestureEvent& evt)
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
    networkInfoSettingViewBase::handleGestureEvent(evt);
}

void networkInfoSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoinformationSettingScreenWipeTransitionWest();
}
