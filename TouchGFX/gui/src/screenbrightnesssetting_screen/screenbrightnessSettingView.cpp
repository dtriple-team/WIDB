#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingView.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

screenbrightnessSettingView::screenbrightnessSettingView()
	: slider1ChangedCallback(this, &screenbrightnessSettingView::slider1ChangedHandler),
	  initialX(0), initialY(0)
{

}

void screenbrightnessSettingView::setupScreen()
{
    screenbrightnessSettingViewBase::setupScreen();
    slider1.setValue(presenter->getSlider1Value());
    slider1.setNewValueCallback(slider1ChangedCallback);
}

void screenbrightnessSettingView::tearDownScreen()
{
    screenbrightnessSettingViewBase::tearDownScreen();
}

void screenbrightnessSettingView::handleGestureEvent(const GestureEvent& evt)
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
    screenbrightnessSettingViewBase::handleGestureEvent(evt);
}

void screenbrightnessSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoscreenSettingScreenWipeTransitionWest();
}

extern uint8_t set_bLevel;
void screenbrightnessSettingView::slider1ChangedHandler(const Slider& src, int value)
{
    presenter->updateSlider1Value(value);
    set_bLevel = value/6.67+1;
}
