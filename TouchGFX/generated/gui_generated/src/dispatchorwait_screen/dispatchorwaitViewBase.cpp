/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/dispatchorwait_screen/dispatchorwaitViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

dispatchorwaitViewBase::dispatchorwaitViewBase()
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    typeofdisaster.setPosition(0, 6, 240, 25);
    typeofdisaster.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    typeofdisaster.setLinespacing(0);
    Unicode::snprintf(typeofdisasterBuffer, TYPEOFDISASTER_SIZE, "%s", touchgfx::TypedText(T_TYPE_OF_DISASTER).getText());
    typeofdisaster.setWildcard(typeofdisasterBuffer);
    typeofdisaster.setTypedText(touchgfx::TypedText(T_DISPATCHORWAITLABEL));
    add(typeofdisaster);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    textArea1.setPosition(0, 67, 240, 17);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setWildcard(touchgfx::TypedText(T_ADDRESS).getText());
    textArea1.setTypedText(touchgfx::TypedText(T_DISASTER_ADD));
    add(textArea1);

    button1.setXY(20, 125);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_DISPATCH_NOTPRESSED_ID), touchgfx::Bitmap(BITMAP_DISPATCH_PRESSED_ID));
    add(button1);

    button2.setXY(20, 198);
    button2.setBitmaps(touchgfx::Bitmap(BITMAP_RECTANGLE_31_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_31_D_ID));
    add(button2);

    textArea2.setPosition(20, 141, 200, 29);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T_DISPATCH_LABEL));
    add(textArea2);

    textArea2_1.setPosition(20, 214, 200, 29);
    textArea2_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2_1.setLinespacing(0);
    textArea2_1.setTypedText(touchgfx::TypedText(T_WAIT_LABEL));
    add(textArea2_1);
}

dispatchorwaitViewBase::~dispatchorwaitViewBase()
{

}

void dispatchorwaitViewBase::setupScreen()
{

}
