/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/flashlight_screen_screen/flashlight_screenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

flashlight_screenViewBase::flashlight_screenViewBase() :
    flexButtonCallback(this, &flashlight_screenViewBase::flexButtonCallbackHandler)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    box1.setPosition(0, 0, 240, 280);
    box1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    add(box1);

    flashlight_image.setXY(98, 118);
    flashlight_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_FLASHLIGHTICON_ID));
    add(flashlight_image);

    flashlightBackBTN.setBoxWithBorderPosition(0, 0, 240, 280);
    flashlightBackBTN.setBorderSize(5);
    flashlightBackBTN.setBoxWithBorderColors(touchgfx::Color::getColorFromRGB(0, 102, 153), touchgfx::Color::getColorFromRGB(0, 153, 204), touchgfx::Color::getColorFromRGB(0, 51, 102), touchgfx::Color::getColorFromRGB(51, 102, 153));
    flashlightBackBTN.setAlpha(0);
    flashlightBackBTN.setAction(flexButtonCallback);
    flashlightBackBTN.setPosition(0, 0, 240, 280);
    add(flashlightBackBTN);
}

flashlight_screenViewBase::~flashlight_screenViewBase()
{

}

void flashlight_screenViewBase::setupScreen()
{
    transitionBegins();
}

void flashlight_screenViewBase::flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src)
{
    if (&src == &flashlightBackBTN)
    {
        //flashlightBack
        //When flashlightBackBTN clicked change screen to swipedownfromHome
        //Go to swipedownfromHome with no screen transition
        application().gotoswipedownfromHomeScreenNoTransition();
        //beforeBright
        //When flashlightBackBTN clicked call changeBeforeBrightness on flashlight_screen
        //Call changeBeforeBrightness
        changeBeforeBrightness();
    }
}

void flashlight_screenViewBase::transitionBegins()
{
    //maxBrightness
    //When screen transition begins call changeMaxBrightness on flashlight_screen
    //Call changeMaxBrightness
    changeMaxBrightness();
}

void flashlight_screenViewBase::handleTickEvent()
{
    //resetScreenOnTime
    //When every N tick execute C++ code
    //Execute C++ code
    //extern uint8_t brightness_count;
    //brightness_count = 0;
}
