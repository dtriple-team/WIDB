#include <gui/screenontimesetting_screen/screenontimeSettingView.hpp>
#include <gui/screenontimesetting_screen/screenontimeSettingPresenter.hpp>

screenontimeSettingPresenter::screenontimeSettingPresenter(screenontimeSettingView& v)
    : view(v)
{

}

void screenontimeSettingPresenter::activate()
{

}

void screenontimeSettingPresenter::deactivate()
{

}

void screenontimeSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
