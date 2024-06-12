#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingView.hpp>
#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingPresenter.hpp>

screenbrightnessSettingPresenter::screenbrightnessSettingPresenter(screenbrightnessSettingView& v)
    : view(v)
{

}

void screenbrightnessSettingPresenter::activate()
{

}

void screenbrightnessSettingPresenter::deactivate()
{

}

void screenbrightnessSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}

void screenbrightnessSettingPresenter::updateSlider1Value(int value)
{
	model->setSlider1Value(value);
}

int screenbrightnessSettingPresenter::getSlider1Value() const
{
	return model->getSlider1Value();
}

