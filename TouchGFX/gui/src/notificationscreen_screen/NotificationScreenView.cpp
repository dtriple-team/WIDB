#include <gui/notificationscreen_screen/NotificationScreenView.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

NotificationScreenView::NotificationScreenView()
	: initialX(0), initialY(0)
{

}

void NotificationScreenView::setupScreen()
{
    NotificationScreenViewBase::setupScreen();
}

void NotificationScreenView::tearDownScreen()
{
    NotificationScreenViewBase::tearDownScreen();
}

void NotificationScreenView::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
    {
        int deltaY = evt.getVelocity();
        if (deltaY > 0)
        {
            presenter->notifySwipeDown();
        }
    }
    NotificationScreenViewBase::handleGestureEvent(evt);
}

void NotificationScreenView::handleSwipeDown()
{
    application().gotoHomeScreenWithBiodataScreenWipeTransitionNorth();
}
