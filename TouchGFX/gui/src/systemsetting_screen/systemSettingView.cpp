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

void systemSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
    systemSettingViewBase::handleGestureEvent(evt);
}

void systemSettingView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoSettingScreenScreenWipeTransitionWest();
}
