#include <gui/flashlight_screen_screen/flashlight_screenView.hpp>

flashlight_screenView::flashlight_screenView()
{

}

void flashlight_screenView::setupScreen()
{
    flashlight_screenViewBase::setupScreen();
}

void flashlight_screenView::tearDownScreen()
{
    flashlight_screenViewBase::tearDownScreen();
}

extern uint8_t set_bLevel;
extern uint8_t before_bLevel;
extern uint8_t flashlightOn;
void flashlight_screenView::changeMaxBrightness(){
	before_bLevel = set_bLevel;
	set_bLevel = 16;
	flashlightOn = 1;
}

void flashlight_screenView::changeBeforeBrightness(){
	set_bLevel = before_bLevel;
	flashlightOn = 0;
}
