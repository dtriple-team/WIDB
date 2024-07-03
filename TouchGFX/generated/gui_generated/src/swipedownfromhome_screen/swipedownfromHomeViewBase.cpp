/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/swipedownfromhome_screen/swipedownfromHomeViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

swipedownfromHomeViewBase::swipedownfromHomeViewBase() :
    buttonCallback(this, &swipedownfromHomeViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    toggleButton1.setXY(14, 51);
    toggleButton1.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_13_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID));
    toggleButton1.forceState(true);
    add(toggleButton1);

    toggleButton2.setXY(87, 51);
    toggleButton2.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_13_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID));
    toggleButton2.forceState(true);
    add(toggleButton2);

    button1.setXY(160, 51);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_D_ID));
    button1.setAction(buttonCallback);
    add(button1);

    image1.setXY(23, 67);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_HAPTICICON_ID));
    add(image1);

    image2.setXY(101, 65);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_SOUNDICON_ID));
    add(image2);

    image3.setXY(175, 66);
    image3.setBitmap(touchgfx::Bitmap(BITMAP_SETTINGICON_ID));
    add(image3);

    button2.setXY(14, 124);
    button2.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_D_ID));
    add(button2);

    button3.setXY(87, 124);
    button3.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_D_ID));
    add(button3);

    button4.setXY(14, 197);
    button4.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_D_ID));
    add(button4);

    button5.setXY(87, 197);
    button5.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_12_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_12_D_ID));
    add(button5);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    slider1.setXY(161, 124);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_15_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_16_ID), touchgfx::Bitmap(BITMAP_LINE_10_ID));
    slider1.setupVerticalSlider(0, 0, 11, 1, 138);
    slider1.setValueRange(0, 15);
    slider1.setValue(15);
    add(slider1);

    image4.setXY(173, 210);
    image4.setBitmap(touchgfx::Bitmap(BITMAP_BRIGHTNESS_ID));
    add(image4);

    button6.setXY(0, 0);
    button6.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID));
    button6.setVisible(false);
    button6.setAction(buttonCallback);
    add(button6);
}

swipedownfromHomeViewBase::~swipedownfromHomeViewBase()
{

}

void swipedownfromHomeViewBase::setupScreen()
{

}

void swipedownfromHomeViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //movetoSetting
        //When button1 clicked change screen to SettingScreen
        //Go to SettingScreen with screen transition towards North
        application().gotoSettingScreenScreenWipeTransitionNorth();
    }
    if (&src == &button6)
    {
        //Interaction1
        //When button6 clicked change screen to HomeScreenWithBiodata
        //Go to HomeScreenWithBiodata with screen transition towards South
        application().gotoHomeScreenWithBiodataScreenWipeTransitionSouth();
    }
}
