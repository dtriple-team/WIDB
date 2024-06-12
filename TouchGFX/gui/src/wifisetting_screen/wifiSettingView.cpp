#include <gui/wifisetting_screen/wifiSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

wifiSettingView::wifiSettingView()
	: initialX(0), initialY(0)
{

}

void wifiSettingView::setupScreen()
{
    wifiSettingViewBase::setupScreen();
}

void wifiSettingView::tearDownScreen()
{
    wifiSettingViewBase::tearDownScreen();
}

void wifiSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
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
    wifiSettingViewBase::handleGestureEvent(evt);
}

void wifiSettingView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoSettingScreenScreenWipeTransitionWest();
}
