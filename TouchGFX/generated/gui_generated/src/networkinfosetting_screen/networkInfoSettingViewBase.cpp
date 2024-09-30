/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/networkinfosetting_screen/networkInfoSettingViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

networkInfoSettingViewBase::networkInfoSettingViewBase()
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    networkinfo_label.setPosition(0, 6, 240, 25);
    networkinfo_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    networkinfo_label.setLinespacing(0);
    networkinfo_label.setTypedText(touchgfx::TypedText(T_NETWORKINFO));
    add(networkinfo_label);

    imei_label.setPosition(0, 53, 240, 29);
    imei_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    imei_label.setLinespacing(0);
    Unicode::snprintf(imei_labelBuffer, IMEI_LABEL_SIZE, "%s", touchgfx::TypedText(T_IMEIVALUE).getText());
    imei_label.setWildcard(imei_labelBuffer);
    imei_label.setTypedText(touchgfx::TypedText(T_IMEI));
    add(imei_label);

    iccid_label.setPosition(0, 80, 240, 29);
    iccid_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    iccid_label.setLinespacing(0);
    Unicode::snprintf(iccid_labelBuffer, ICCID_LABEL_SIZE, "%s", touchgfx::TypedText(T_ICCIDVALUE).getText());
    iccid_label.setWildcard(iccid_labelBuffer);
    iccid_label.setTypedText(touchgfx::TypedText(T_ICCID));
    add(iccid_label);

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

networkInfoSettingViewBase::~networkInfoSettingViewBase()
{

}

void networkInfoSettingViewBase::setupScreen()
{

}
