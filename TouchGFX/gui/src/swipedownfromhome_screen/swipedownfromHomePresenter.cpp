#include <gui/swipedownfromhome_screen/swipedownfromHomePresenter.hpp>
#include <gui/swipedownfromhome_screen/swipedownfromHomeView.hpp>

swipedownfromHomePresenter::swipedownfromHomePresenter(swipedownfromHomeView& v)
    : view(v)
{
    model->getToggleButton1StateChangedCallback() = touchgfx::Callback<swipedownfromHomePresenter, bool>(this, &swipedownfromHomePresenter::onToggleButton1StateChanged); //test
    model->getToggleButton2StateChangedCallback() = touchgfx::Callback<swipedownfromHomePresenter, bool>(this, &swipedownfromHomePresenter::onToggleButton2StateChanged); //test
}

void swipedownfromHomePresenter::activate()
{
    // Activate code
}

void swipedownfromHomePresenter::deactivate()
{
    // Deactivate code
}

void swipedownfromHomePresenter::notifySwipeUp() //rkdalfks
{
	view.handleSwipeUp();
}

void swipedownfromHomePresenter::updateToggleButton1State(bool state)
{
    model->setToggleButton1State(state);
}

bool swipedownfromHomePresenter::getToggleButton1State() const
{
    return model->getToggleButton1State();
}

void swipedownfromHomePresenter::onToggleButton1StateChanged(bool state)
{
    view.updateToggleButton1State(state);
}

void swipedownfromHomePresenter::updateToggleButton2State(bool state)
{
    model->setToggleButton2State(state);
}

bool swipedownfromHomePresenter::getToggleButton2State() const
{
    return model->getToggleButton2State();
}

void swipedownfromHomePresenter::onToggleButton2StateChanged(bool state)
{
    view.updateToggleButton2State(state);
}

void swipedownfromHomePresenter::updateSlider1Value(int value)
{
	model->setSlider1Value(value);
}

int swipedownfromHomePresenter::getSlider1Value() const
{
	return model->getSlider1Value();
}
