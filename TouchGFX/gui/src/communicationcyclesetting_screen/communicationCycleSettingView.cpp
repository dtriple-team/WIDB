#include <gui/communicationcyclesetting_screen/communicationCycleSettingView.hpp>
#include "texts/TextKeysAndLanguages.hpp"
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

communicationCycleSettingView::communicationCycleSettingView()
	: scrollWheel1AnimateToCallback(this, &communicationCycleSettingView::scrollWheel1AnimateToHandler),
	  initialX(0), initialY(0)
{

}

void communicationCycleSettingView::setupScreen()
{
    communicationCycleSettingViewBase::setupScreen();
    scrollWheel1.setAnimateToCallback(scrollWheel1AnimateToCallback);
}

void communicationCycleSettingView::tearDownScreen()
{
    communicationCycleSettingViewBase::tearDownScreen();
}

void communicationCycleSettingView::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        int deltaX = evt.getVelocity();
        if (deltaX > 0)
        {
            presenter->notifySwipeRight();
        }
    }
    communicationCycleSettingViewBase::handleGestureEvent(evt);
}

void communicationCycleSettingView::handleSwipeRight()
{
    application().gotoSettingScreenScreenWipeTransitionWest();
}

void communicationCycleSettingView::scrollWheel1UpdateItem(setting_communicationcycle_notselected& item, int16_t itemIndex)
{
	item.setElements(5 * itemIndex * itemIndex + 15 * itemIndex + 10);
}

void communicationCycleSettingView::scrollWheel1UpdateCenterItem(setting_communicationcycle_selected& item, int16_t itemIndex)
{
	item.setElements(5 * itemIndex * itemIndex + 15 * itemIndex + 10);
}

void communicationCycleSettingView::scrollWheel1AnimateToHandler(int16_t item)
{

}
