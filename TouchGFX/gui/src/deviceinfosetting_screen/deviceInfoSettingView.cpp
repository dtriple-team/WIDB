#include <gui/deviceinfosetting_screen/deviceInfoSettingView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

deviceInfoSettingView::deviceInfoSettingView()
	: initialX(0), initialY(0)
{

}

void deviceInfoSettingView::setupScreen()
{
    deviceInfoSettingViewBase::setupScreen();
}

void deviceInfoSettingView::tearDownScreen()
{
    deviceInfoSettingViewBase::tearDownScreen();
}

void deviceInfoSettingView::handleGestureEvent(const GestureEvent& evt)
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
    deviceInfoSettingViewBase::handleGestureEvent(evt);
}

void deviceInfoSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoinformationSettingScreenWipeTransitionWest();
}
