/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screensetting_screen/screenSettingViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

screenSettingViewBase::screenSettingViewBase() :
    buttonCallback(this, &screenSettingViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    screen_label.setPosition(0, 6, 240, 25);
    screen_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    screen_label.setLinespacing(0);
    screen_label.setTypedText(touchgfx::TypedText(T_SCREEN));
    add(screen_label);

    ontimebutton_icon_back.setXY(14, 48);
    ontimebutton_icon_back.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ICONBACK_ID));
    add(ontimebutton_icon_back);

    brightnessbutton_icon_back.setXY(14, 109);
    brightnessbutton_icon_back.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ICONBACK_ID));
    add(brightnessbutton_icon_back);

    ontime_label.setPosition(66, 59, 140, 25);
    ontime_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    ontime_label.setLinespacing(0);
    ontime_label.setTypedText(touchgfx::TypedText(T_SCREENONTIMETEXT));
    add(ontime_label);

    brightness_label.setPosition(66, 120, 140, 25);
    brightness_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    brightness_label.setLinespacing(0);
    brightness_label.setTypedText(touchgfx::TypedText(T_SCREENBRIGHTNESSTEXT));
    add(brightness_label);

    ontime_arrow_image.setXY(211, 58);
    ontime_arrow_image.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    add(ontime_arrow_image);

    brightness_arrow_image.setXY(211, 120);
    brightness_arrow_image.setBitmap(touchgfx::Bitmap(BITMAP_RIGHT_ID));
    add(brightness_arrow_image);

    ontime_button.setXY(56, 43);
    ontime_button.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUNDED_INACTIVE_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUNDED_INACTIVE_ID));
    ontime_button.setAlpha(0);
    ontime_button.setAction(buttonCallback);
    add(ontime_button);

    brightness_button.setXY(56, 104);
    brightness_button.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUNDED_INACTIVE_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_SMALL_ROUNDED_INACTIVE_ID));
    brightness_button.setAlpha(0);
    brightness_button.setAction(buttonCallback);
    add(brightness_button);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    buttonfornothing.setXY(0, 0);
    buttonfornothing.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID));
    buttonfornothing.setVisible(false);
    buttonfornothing.setAction(buttonCallback);
    add(buttonfornothing);

    ontime_image.setXY(16, 50);
    ontime_image.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ONTIME_ICON_ID));
    add(ontime_image);

    brightness_image.setXY(17, 112);
    brightness_image.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_BRIGHTNESS_ICON_ID));
    add(brightness_image);
}

screenSettingViewBase::~screenSettingViewBase()
{

}

void screenSettingViewBase::setupScreen()
{
    transitionBegins();
}

void screenSettingViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &ontime_button)
    {
        //setscreenontime
        //When ontime_button clicked change screen to screenontimeSetting
        //Go to screenontimeSetting with screen transition towards East
        application().gotoscreenontimeSettingScreenCoverTransitionEast();
    }
    if (&src == &brightness_button)
    {
        //setscreenbrightness
        //When brightness_button clicked change screen to screenbrightnessSetting
        //Go to screenbrightnessSetting with screen transition towards East
        application().gotoscreenbrightnessSettingScreenCoverTransitionEast();
    }
    if (&src == &buttonfornothing)
    {
        //Interaction1
        //When buttonfornothing clicked change screen to SettingScreen
        //Go to SettingScreen with screen transition towards West
        application().gotoSettingScreenScreenWipeTransitionWest();
    }
}

void screenSettingViewBase::transitionBegins()
{
    //resetBATT
    //When screen transition begins execute C++ code
    //Execute C++ code
    extern uint8_t battVal;
    batteryprogress.setValue(battVal);
}
