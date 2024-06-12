#include <gui/systemsetting_screen/systemSettingView.hpp>
#include <gui/systemsetting_screen/systemSettingPresenter.hpp>

systemSettingPresenter::systemSettingPresenter(systemSettingView& v)
    : view(v)
{

}

void systemSettingPresenter::activate()
{

}

void systemSettingPresenter::deactivate()
{

}

void systemSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
