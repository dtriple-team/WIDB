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

void languageSettingView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        int deltaX = evt.getVelocity();
        if (deltaX > 0) // 오른쪽으로 스와이프
        {
            // 스와이프 이벤트 처리
            presenter->notifySwipeRight();
        }
    }
    languageSettingViewBase::handleGestureEvent(evt);
}

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
	    }
	    else if (Texts::getLanguage() == GB)
	    {
	        radioButton1.setSelected(false);
	        radioButton2.setSelected(true);
	    }
	    radioButton1.invalidate();
	    radioButton2.invalidate();
}
