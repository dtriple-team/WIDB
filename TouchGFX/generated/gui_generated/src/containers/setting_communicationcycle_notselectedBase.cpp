/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/setting_communicationcycle_notselectedBase.hpp>
#include <touchgfx/Color.hpp>
#include <texts/TextKeysAndLanguages.hpp>

setting_communicationcycle_notselectedBase::setting_communicationcycle_notselectedBase()
{
    setWidth(197);
    setHeight(46);
    box1.setPosition(0, 0, 197, 46);
    box1.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(box1);

    textArea1.setPosition(0, 0, 197, 46);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(118, 118, 118));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T_NOTSELECTED_CYCLE).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T___SINGLEUSE_DVDQ));
    add(textArea1);
}

setting_communicationcycle_notselectedBase::~setting_communicationcycle_notselectedBase()
{

}

void setting_communicationcycle_notselectedBase::initialize()
{

}
