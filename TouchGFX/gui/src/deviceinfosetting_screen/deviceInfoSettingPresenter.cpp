#include <gui/deviceinfosetting_screen/deviceInfoSettingView.hpp>
#include <gui/deviceinfosetting_screen/deviceInfoSettingPresenter.hpp>

deviceInfoSettingPresenter::deviceInfoSettingPresenter(deviceInfoSettingView& v)
    : view(v)
{

}

void deviceInfoSettingPresenter::activate()
{

}

void deviceInfoSettingPresenter::deactivate()
{

}

void deviceInfoSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
