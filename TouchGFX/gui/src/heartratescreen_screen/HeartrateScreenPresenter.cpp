#include <gui/heartratescreen_screen/HeartrateScreenView.hpp>
#include <gui/heartratescreen_screen/HeartrateScreenPresenter.hpp>

HeartrateScreenPresenter::HeartrateScreenPresenter(HeartrateScreenView& v)
    : view(v)
{

}

void HeartrateScreenPresenter::activate()
{

}

void HeartrateScreenPresenter::deactivate()
{

}

void HeartrateScreenPresenter::notifySwipeRight() //rkdalfks
{
	view.handleSwipeRight();
}

void HeartrateScreenPresenter::notifySwipeLeft() //rkdalfks
{
	view.handleSwipeLeft();
}
