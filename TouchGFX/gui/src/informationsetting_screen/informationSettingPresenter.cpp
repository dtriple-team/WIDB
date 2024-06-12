#include <gui/informationsetting_screen/informationSettingView.hpp>
#include <gui/informationsetting_screen/informationSettingPresenter.hpp>

informationSettingPresenter::informationSettingPresenter(informationSettingView& v)
    : view(v)
{

}

void informationSettingPresenter::activate()
{

}

void informationSettingPresenter::deactivate()
{

}

void informationSettingPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
