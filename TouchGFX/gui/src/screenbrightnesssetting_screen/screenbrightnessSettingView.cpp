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
#if defined(gui_simulation)
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
#endif

void screenbrightnessSettingView::handleSwipeRight()
{
    // 화면 전환 코드
    application().gotoscreenSettingScreenWipeTransitionWest();
}
#if !defined(gui_simulation)
extern uint8_t set_bLevel;

extern uint8_t before_bLevel;

#endif

void screenbrightnessSettingView::slider1ChangedHandler(const Slider& src, int value)
{
    presenter->updateSlider1Value(value);
#if !defined(gui_simulation)
    set_bLevel = value/6.67+1;

    before_bLevel = set_bLevel;

#endif

}

#if !defined(gui_simulation)

#include "bl6133.h"
extern GESTURE gesture;
void screenbrightnessSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
#endif
