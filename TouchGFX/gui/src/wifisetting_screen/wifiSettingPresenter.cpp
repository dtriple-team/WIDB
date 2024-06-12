#include <gui/wifisetting_screen/wifiSettingView.hpp>
#include <gui/wifisetting_screen/wifiSettingPresenter.hpp>

wifiSettingPresenter::wifiSettingPresenter(wifiSettingView& v)
    : view(v)
{

}

void wifiSettingPresenter::activate()
{

}

void wifiSettingPresenter::deactivate()
{

}

void wifiSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
