/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/languagesetting_screen/languageSettingViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

languageSettingViewBase::languageSettingViewBase() :
    radioButtonSelectedCallback(this, &languageSettingViewBase::radioButtonSelectedCallbackHandler)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    language_label.setPosition(0, 6, 240, 25);
    language_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    language_label.setLinespacing(0);
    language_label.setTypedText(touchgfx::TypedText(T_LANGUAGESCREEN));
    add(language_label);

    korean_icon_back.setXY(14, 48);
    korean_icon_back.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ICONBACK_ID));
    add(korean_icon_back);

    english_icon_back.setXY(14, 109);
    english_icon_back.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ICONBACK_ID));
    add(english_icon_back);

    spanish_icon_back.setXY(14, 170);
    spanish_icon_back.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ICONBACK_ID));
    add(spanish_icon_back);

    korean_label.setPosition(66, 59, 107, 20);
    korean_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    korean_label.setLinespacing(0);
    korean_label.setTypedText(touchgfx::TypedText(T_KOREAN));
    add(korean_label);

    english_label.setPosition(66, 120, 107, 20);
    english_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    english_label.setLinespacing(0);
    english_label.setTypedText(touchgfx::TypedText(T_ENGLISH));
    add(english_label);

    spanish_label.setPosition(66, 180, 107, 20);
    spanish_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    spanish_label.setLinespacing(0);
    spanish_label.setTypedText(touchgfx::TypedText(T_SPANISH));
    add(spanish_label);

    radioButtonGroup1.setRadioButtonSelectedHandler(radioButtonSelectedCallback);
    
    radioButton1.setXY(191, 56);
    radioButton1.setBitmaps(touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID));
    radioButton1.setSelected(true);
    radioButton1.setDeselectionEnabled(false);
    radioButtonGroup1.add(radioButton1);
    add(radioButton1);

    radioButton2.setXY(191, 117);
    radioButton2.setBitmaps(touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID));
    radioButton2.setSelected(false);
    radioButton2.setDeselectionEnabled(false);
    radioButtonGroup1.add(radioButton2);
    add(radioButton2);

    radioButton3.setXY(191, 178);
    radioButton3.setBitmaps(touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIONFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID), touchgfx::Bitmap(BITMAP_RADIOFILL_ID));
    radioButton3.setSelected(false);
    radioButton3.setDeselectionEnabled(false);
    radioButtonGroup1.add(radioButton3);
    add(radioButton3);

    korean_image.setXY(22, 55);
    korean_image.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_KOREAN_ICON_ID));
    add(korean_image);

    english_image.setXY(16, 111);
    english_image.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_ENGLISH_ICON_ID));
    add(english_image);

    spanish_image.setXY(17, 178);
    spanish_image.setBitmap(touchgfx::Bitmap(BITMAP_SET_SETTING_SPANISH_ICON_ID));
    add(spanish_image);

    batteryprogress_container1.setXY(0, 0);
    add(batteryprogress_container1);
}

languageSettingViewBase::~languageSettingViewBase()
{

}

void languageSettingViewBase::setupScreen()
{
    batteryprogress_container1.initialize();
}

void languageSettingViewBase::radioButtonSelectedCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &radioButton1)
    {
        //setLanguageToKorean
        //When radioButton1 selected set language Korean
        //Change language to Korean
        Texts::setLanguage(KOREAN);
        invalidate();
    }
    if (&src == &radioButton2)
    {
        //setLanguageToEnglish
        //When radioButton2 selected set language GB
        //Change language to GB
        Texts::setLanguage(GB);
        invalidate();
    }
    if (&src == &radioButton3)
    {
        //setLanguageToSpanish
        //When radioButton3 selected set language Spanish
        //Change language to Spanish
        Texts::setLanguage(SPANISH);
        invalidate();
    }
}
