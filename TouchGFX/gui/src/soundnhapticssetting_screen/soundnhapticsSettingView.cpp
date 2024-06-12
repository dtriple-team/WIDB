#include <gui/soundnhapticssetting_screen/soundnhapticsSettingView.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

soundnhapticsSettingView::soundnhapticsSettingView()
	: toggleButton1ClickedCallback(this, &soundnhapticsSettingView::toggleButton1Clicked), //test
	  toggleButton2ClickedCallback(this, &soundnhapticsSettingView::toggleButton2Clicked),
	  initialX(0), initialY(0)
{

}

void soundnhapticsSettingView::setupScreen()
{
    soundnhapticsSettingViewBase::setupScreen();
    toggleButton1.setAction(toggleButton1ClickedCallback);
    toggleButton2.setAction(toggleButton2ClickedCallback);
    toggleButton1.forceState(presenter->getToggleButton1State()); //test
    toggleButton2.forceState(presenter->getToggleButton2State()); //test
}

void soundnhapticsSettingView::tearDownScreen()
{
    soundnhapticsSettingViewBase::tearDownScreen();
}

void soundnhapticsSettingView::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
        int deltaX = evt.getVelocity();
        if (deltaX > 0)
        {
            presenter->notifySwipeRight();
        }
    }
    soundnhapticsSettingViewBase::handleGestureEvent(evt);
}

void soundnhapticsSettingView::handleSwipeRight()
{
    application().gotoSettingScreenScreenWipeTransitionWest();
}

void soundnhapticsSettingView::toggleButton1Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = toggleButton1.getState();
    presenter->updateToggleButton1State(newState);
}

void soundnhapticsSettingView::updateToggleButton1State(bool state)
{
    toggleButton1.forceState(state);
}

void soundnhapticsSettingView::toggleButton2Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = toggleButton2.getState();
    presenter->updateToggleButton2State(newState);
}

void soundnhapticsSettingView::updateToggleButton2State(bool state)
{
    toggleButton2.forceState(state);
}
