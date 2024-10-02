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

    haptic_togglebutton.setXY(14, 51);
    haptic_togglebutton.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID));
    add(haptic_togglebutton);

    sound_togglebutton.setXY(87, 51);
    sound_togglebutton.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID));
    add(sound_togglebutton);

    setting_button.setXY(160, 51);
    setting_button.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID));
    setting_button.setAction(buttonCallback);
    add(setting_button);

    wifi_togglebutton.setXY(14, 124);
    wifi_togglebutton.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID));
    add(wifi_togglebutton);

    bluetooth_togglebutton.setXY(87, 124);
    bluetooth_togglebutton.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID));
    add(bluetooth_togglebutton);

    information_button.setXY(14, 197);
    information_button.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID));
    information_button.setAction(buttonCallback);
    add(information_button);

    flashlight_button.setXY(87, 197);
    flashlight_button.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BUTTON_PRESSED_ID));
    flashlight_button.setAction(buttonCallback);
    add(flashlight_button);

    slider1.setXY(161, 124);
    slider1.setBitmaps(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BRIGHTNESS_BACK_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BRIGHTNESS_ID), touchgfx::Bitmap(BITMAP_SWIPEDOWN_BRIGHTNESS_INDICATOR_ID));
    slider1.setupVerticalSlider(0, 0, 11, 1, 138);
    slider1.setValueRange(0, 100);
    slider1.setValue(50);
    add(slider1);

    haptic_image.setXY(23, 67);
    haptic_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_HAPTICICON_ID));
    add(haptic_image);

    sound_image.setXY(101, 65);
    sound_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_SOUNDICON_ID));
    add(sound_image);

    setting_image.setXY(175, 66);
    setting_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_SETTINGICON_ID));
    add(setting_image);

    information_image.setXY(25, 208);
    information_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_INFOICON_ID));
    add(information_image);

    brightness_image.setXY(173, 210);
    brightness_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_BRIGHTNESS_ICON_ID));
    add(brightness_image);

    flashlight_image.setXY(98, 208);
    flashlight_image.setBitmap(touchgfx::Bitmap(BITMAP_SWIPEDOWN_FLASHLIGHTICON_ID));
    add(flashlight_image);

    topright_box.setPosition(175, 0, 65, 33);
    topright_box.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topright_box);

    topleft_box.setPosition(0, 0, 65, 33);
    topleft_box.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topleft_box);

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

    catm1_image.setXY(11, 11);
    catm1_image.setBitmap(touchgfx::Bitmap(BITMAP_LTE_NOTCONNECTED_ID));
    add(catm1_image);
}

swipedownfromHomeViewBase::~swipedownfromHomeViewBase()
{

}

void swipedownfromHomeViewBase::setupScreen()
{
    transitionBegins();
}

void swipedownfromHomeViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &setting_button)
    {
        //movetoSetting
        //When setting_button clicked change screen to SettingScreen
        //Go to SettingScreen with screen transition towards North
        application().gotoSettingScreenScreenWipeTransitionNorth();
    }
    if (&src == &buttonfornothing)
    {
        //Interaction1
        //When buttonfornothing clicked change screen to HomeScreenWithBiodata
        //Go to HomeScreenWithBiodata with screen transition towards South
        application().gotoHomeScreenWithBiodataScreenWipeTransitionSouth();
    }
    if (&src == &information_button)
    {
        //Interaction2
        //When information_button clicked change screen to informationSetting
        //Go to informationSetting with screen transition towards North
        application().gotoinformationSettingScreenWipeTransitionNorth();
    }
    if (&src == &flashlight_button)
    {
        //flashlight
        //When flashlight_button clicked change screen to flashlight_screen
        //Go to flashlight_screen with no screen transition
        application().gotoflashlight_screenScreenNoTransition();
    }
}

void swipedownfromHomeViewBase::transitionBegins()
{
    //resetBATT
    //When screen transition begins execute C++ code
    //Execute C++ code
    extern uint8_t battVal;
    batteryprogress.setValue(battVal);
}
