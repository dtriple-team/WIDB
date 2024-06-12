#include <gui/sleepscreen_screen/SleepScreenView.hpp>
#include <gui/sleepscreen_screen/SleepScreenPresenter.hpp>

SleepScreenPresenter::SleepScreenPresenter(SleepScreenView& v)
    : view(v)
{

}

void SleepScreenPresenter::activate()
{

}

void SleepScreenPresenter::deactivate()
{

}

void SleepScreenPresenter::notifySwipeRight()
{
    view.handleSwipeRight();
}

