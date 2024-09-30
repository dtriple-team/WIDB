/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/falldetected_screen/fallDetectedViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

fallDetectedViewBase::fallDetectedViewBase()
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    textArea1.setPosition(0, 6, 240, 25);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    textArea1.setTypedText(touchgfx::TypedText(T_FALLSOCCURLABEL));
    add(textArea1);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    image1.setXY(75, 73);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_FALL_DETECTED_ICON_ID));
    add(image1);

    textArea2.setPosition(0, 208, 240, 29);
    textArea2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea2.setLinespacing(0);
    textArea2.setTypedText(touchgfx::TypedText(T_FALLDETECTIONTEXT));
    add(textArea2);

    topleft_box.setPosition(0, 0, 65, 33);
    topleft_box.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topleft_box);

    image2.setXY(11, 11);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_LTE_NOTCONNECTED_ID));
    add(image2);
}

fallDetectedViewBase::~fallDetectedViewBase()
{

}

void fallDetectedViewBase::setupScreen()
{

}

void fallDetectedViewBase::changeToFallDetected()
{
    //Interaction1
    //When changeToFallDetected is called change screen to fallDetected
    //Go to fallDetected with no screen transition
    application().gotofallDetectedScreenNoTransition();
}
