#include <gui/swipedownfromhome_screen/swipedownfromHomeView.hpp>
#include <gui/model/Model.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/Utils.hpp>

#include <cstdlib>

swipedownfromHomeView::swipedownfromHomeView()
	: toggleButton1ClickedCallback(this, &swipedownfromHomeView::toggleButton1Clicked), //test
	  toggleButton2ClickedCallback(this, &swipedownfromHomeView::toggleButton2Clicked),
	  slider1ChangedCallback(this, &swipedownfromHomeView::slider1ChangedHandler),
	  initialX(0), initialY(0)
{

}

void swipedownfromHomeView::setupScreen()
{
    swipedownfromHomeViewBase::setupScreen();
    toggleButton1.setAction(toggleButton1ClickedCallback);
    toggleButton2.setAction(toggleButton2ClickedCallback);
    toggleButton1.forceState(presenter->getToggleButton1State()); //test
    toggleButton2.forceState(presenter->getToggleButton2State()); //test
    slider1.setValue(presenter->getSlider1Value());
    slider1.setNewValueCallback(slider1ChangedCallback);
}

void swipedownfromHomeView::tearDownScreen()
{
    swipedownfromHomeViewBase::tearDownScreen();
}

void swipedownfromHomeView::handleGestureEvent(const GestureEvent& evt)
{
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL && isDeltaYGreaterThanDeltaX)
    {
        int deltaY = evt.getVelocity();
        if (deltaY < 0)
        {
            presenter->notifySwipeUp();
        }
    }
    swipedownfromHomeViewBase::handleGestureEvent(evt);
}

void swipedownfromHomeView::handleDragEvent(const DragEvent& evt)
{
	int deltax = std::abs(evt.getDeltaX());
	int deltay = std::abs(evt.getDeltaY());
	if(deltay > deltax){
		isDeltaYGreaterThanDeltaX = 1;
	} else {
		isDeltaYGreaterThanDeltaX = 0;
	}
    swipedownfromHomeViewBase::handleDragEvent(evt);
}

void swipedownfromHomeView::handleSwipeUp()
{
    application().gotoHomeScreenWithBiodataScreenWipeTransitionSouth();
}

void swipedownfromHomeView::toggleButton1Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = toggleButton1.getState();
    presenter->updateToggleButton1State(newState);
}

void swipedownfromHomeView::updateToggleButton1State(bool state)
{
    toggleButton1.forceState(state);
}

void swipedownfromHomeView::toggleButton2Clicked(const touchgfx::AbstractButton& source)
{
    bool newState = toggleButton2.getState();
    presenter->updateToggleButton2State(newState);
}

void swipedownfromHomeView::updateToggleButton2State(bool state)
{
    toggleButton2.forceState(state);
}

extern uint8_t set_bLevel;
void swipedownfromHomeView::slider1ChangedHandler(const Slider& src, int value)
{
    presenter->updateSlider1Value(value);
    set_bLevel = value+1;
}
