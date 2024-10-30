#ifndef STEPSSCREENPRESENTER_HPP
#define STEPSSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class StepsScreenView;

class StepsScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    StepsScreenPresenter(StepsScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void notifySwipeRight();
    virtual void notifySwipeLeft();

    virtual ~StepsScreenPresenter() {}

private:
    StepsScreenPresenter();

    StepsScreenView& view;
};

#endif // STEPSSCREENPRESENTER_HPP
