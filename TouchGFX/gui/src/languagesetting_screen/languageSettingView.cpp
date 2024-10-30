#include <gui/languagesetting_screen/languageSettingView.hpp>
#include <texts/TextKeysAndLanguages.hpp> //rkdalfks
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

languageSettingView::languageSettingView()
	: initialX(0), initialY(0)
{

}

void languageSettingView::setupScreen()
{
    languageSettingViewBase::setupScreen();

    updateLanguageSelection();
}

void languageSettingView::tearDownScreen()
{
    languageSettingViewBase::tearDownScreen();
}
#if defined(gui_simulation)
void languageSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if (deltaX > 0)
			{
				presenter->notifySwipeRight();
			}
        //}
    }
    languageSettingViewBase::handleGestureEvent(evt);
}
#endif

void languageSettingView::handleSwipeRight() //rkdalfks
{
    // 화면 전환 코드
    application().gotoSettingScreenScreenWipeTransitionWest();
}

void languageSettingView::updateLanguageSelection()
{
	if (Texts::getLanguage() == KOREAN)
	{
		radioButton1.setSelected(true);
		radioButton2.setSelected(false);
		radioButton3.setSelected(false);
	}
	else if (Texts::getLanguage() == GB)
	{
		radioButton1.setSelected(false);
		radioButton2.setSelected(true);
		radioButton3.setSelected(false);
	}
	else if (Texts::getLanguage() == SPANISH)
	{
		radioButton1.setSelected(false);
		radioButton2.setSelected(false);
		radioButton3.setSelected(true);
	}
	radioButton1.invalidate();
	radioButton2.invalidate();
	radioButton3.invalidate();
}

#if !defined(gui_simulation)
#include "bl6133.h"
extern GESTURE gesture;
void languageSettingView::handleTickEvent(){
	if(gesture == SlideRight){
		presenter->notifySwipeRight();
	}
}
#endif
