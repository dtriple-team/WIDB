/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/charging_screen_screen/charging_screenViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

charging_screenViewBase::charging_screenViewBase() :
    frameCountChangeHomeScreenInterval(0)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    textArea1.setPosition(0, 190, 240, 58);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_MNWB));
    add(textArea1);

    image1.setXY(51, 40);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_CHARGING_ID));
    add(image1);
}

charging_screenViewBase::~charging_screenViewBase()
{

}

void charging_screenViewBase::setupScreen()
{

}

void charging_screenViewBase::handleTickEvent()
{
    frameCountChangeHomeScreenInterval++;
    if(frameCountChangeHomeScreenInterval == 2500*TICK_CHANGEHOMESCREEN_INTERVAL)
    {
        //changeHomeScreen
        //When every N tick change screen to HomeScreenWithBiodata
        //Go to HomeScreenWithBiodata with no screen transition
        application().gotoHomeScreenWithBiodataScreenNoTransition();
        frameCountChangeHomeScreenInterval = 0;
    }
}

void charging_screenViewBase::changeChargeScreen()
{
    //chargingScreen
    //When changeChargeScreen is called change screen to charging_screen
    //Go to charging_screen with no screen transition
    application().gotocharging_screenScreenNoTransition();
}
