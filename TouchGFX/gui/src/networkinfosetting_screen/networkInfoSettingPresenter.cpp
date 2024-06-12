#include <gui/networkinfosetting_screen/networkInfoSettingView.hpp>
#include <gui/networkinfosetting_screen/networkInfoSettingPresenter.hpp>

networkInfoSettingPresenter::networkInfoSettingPresenter(networkInfoSettingView& v)
    : view(v)
{

}

void networkInfoSettingPresenter::activate()
{

}

void networkInfoSettingPresenter::deactivate()
{

}

void networkInfoSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
