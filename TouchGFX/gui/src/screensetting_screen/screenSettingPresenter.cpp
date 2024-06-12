#include <gui/screensetting_screen/screenSettingView.hpp>
#include <gui/screensetting_screen/screenSettingPresenter.hpp>

screenSettingPresenter::screenSettingPresenter(screenSettingView& v)
    : view(v)
{

}

void screenSettingPresenter::activate()
{

}

void screenSettingPresenter::deactivate()
{

}

void screenSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
