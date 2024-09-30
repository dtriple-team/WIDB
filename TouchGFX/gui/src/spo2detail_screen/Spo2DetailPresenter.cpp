#include <gui/spo2detail_screen/Spo2DetailView.hpp>
#include <gui/spo2detail_screen/Spo2DetailPresenter.hpp>

Spo2DetailPresenter::Spo2DetailPresenter(Spo2DetailView& v)
    : view(v)
{

}

void Spo2DetailPresenter::activate()
{

}

void Spo2DetailPresenter::deactivate()
{

}

void Spo2DetailPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}
