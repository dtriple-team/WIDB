#include <gui/soundnhapticssetting_screen/soundnhapticsSettingView.hpp>
#include <gui/soundnhapticssetting_screen/soundnhapticsSettingPresenter.hpp>

soundnhapticsSettingPresenter::soundnhapticsSettingPresenter(soundnhapticsSettingView& v)
    : view(v)
{
    model->getToggleButton1StateChangedCallback() = touchgfx::Callback<soundnhapticsSettingPresenter, bool>(this, &soundnhapticsSettingPresenter::onToggleButton1StateChanged); //test
    model->getToggleButton2StateChangedCallback() = touchgfx::Callback<soundnhapticsSettingPresenter, bool>(this, &soundnhapticsSettingPresenter::onToggleButton2StateChanged); //test
}

void soundnhapticsSettingPresenter::activate()
{

}

void soundnhapticsSettingPresenter::deactivate()
{

}

void soundnhapticsSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}

void soundnhapticsSettingPresenter::updateToggleButton1State(bool state)
{
    model->setToggleButton1State(state);
}

bool soundnhapticsSettingPresenter::getToggleButton1State() const
{
    return model->getToggleButton1State();
}

void soundnhapticsSettingPresenter::onToggleButton1StateChanged(bool state)
{
    view.updateToggleButton1State(state);
}

void soundnhapticsSettingPresenter::updateToggleButton2State(bool state)
{
    model->setToggleButton2State(state);
}

bool soundnhapticsSettingPresenter::getToggleButton2State() const
{
    return model->getToggleButton2State();
}

void soundnhapticsSettingPresenter::onToggleButton2StateChanged(bool state)
{
    view.updateToggleButton2State(state);
}
