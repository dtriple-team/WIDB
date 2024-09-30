#include <gui/heartratedetail_screen/HeartrateDetailView.hpp>
#include <gui/heartratedetail_screen/HeartrateDetailPresenter.hpp>

HeartrateDetailPresenter::HeartrateDetailPresenter(HeartrateDetailView& v)
    : view(v)
{

}

void HeartrateDetailPresenter::activate()
{

}

void HeartrateDetailPresenter::deactivate()
{

}

void HeartrateDetailPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
