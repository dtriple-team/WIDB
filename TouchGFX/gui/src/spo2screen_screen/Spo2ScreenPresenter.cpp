#include <gui/spo2screen_screen/Spo2ScreenView.hpp>
#include <gui/spo2screen_screen/Spo2ScreenPresenter.hpp>

Spo2ScreenPresenter::Spo2ScreenPresenter(Spo2ScreenView& v)
    : view(v)
{

}

void Spo2ScreenPresenter::activate()
{

}

void Spo2ScreenPresenter::deactivate()
{

}

void Spo2ScreenPresenter::notifySwipeRight() //rkdalfks
{
	view.handleSwipeRight();
}

void Spo2ScreenPresenter::notifySwipeLeft() //rkdalfks
{
	view.handleSwipeLeft();
}
