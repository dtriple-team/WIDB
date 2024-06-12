/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screenbrightnesssetting_screen/screenbrightnessSettingViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

screenbrightnessSettingViewBase::screenbrightnessSettingViewBase()
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    screenbrightness.setPosition(0, 6, 240, 25);
    screenbrightness.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    screenbrightness.setLinespacing(0);
    screenbrightness.setTypedText(touchgfx::TypedText(T_SCREENBRIGHTNESS));
    add(screenbrightness);

    slider1.setXY(67, 39);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_40_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_41_ID), touchgfx::Bitmap(BITMAP_LINE_10_ID));
    slider1.setupVerticalSlider(0, 0, 31, 0, 226);
    slider1.setValueRange(0, 100);
    slider1.setValue(50);
    add(slider1);

    image1.setXY(87, 179);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_BRIGHTNESS2_ID));
    add(image1);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);
}

screenbrightnessSettingViewBase::~screenbrightnessSettingViewBase()
{

}

void screenbrightnessSettingViewBase::setupScreen()
{

}
