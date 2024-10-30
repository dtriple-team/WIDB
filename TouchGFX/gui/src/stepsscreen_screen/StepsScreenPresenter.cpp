#include <gui/stepsscreen_screen/StepsScreenView.hpp>
#include <gui/stepsscreen_screen/StepsScreenPresenter.hpp>

StepsScreenPresenter::StepsScreenPresenter(StepsScreenView& v)
    : view(v)
{

}

void StepsScreenPresenter::activate()
{

}

void StepsScreenPresenter::deactivate()
{

}

void StepsScreenPresenter::notifySwipeRight()
{
	view.handleSwipeRight();
}

void StepsScreenPresenter::notifySwipeLeft()
{
	view.handleSwipeLeft();
}
