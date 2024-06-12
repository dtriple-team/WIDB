#include <gui/communicationcyclesetting_screen/communicationCycleSettingView.hpp>
#include <gui/communicationcyclesetting_screen/communicationCycleSettingPresenter.hpp>

communicationCycleSettingPresenter::communicationCycleSettingPresenter(communicationCycleSettingView& v)
    : view(v)
{

}

void communicationCycleSettingPresenter::activate()
{

}

void communicationCycleSettingPresenter::deactivate()
{

}

void communicationCycleSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}

