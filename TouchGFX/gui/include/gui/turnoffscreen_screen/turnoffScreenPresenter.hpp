#ifndef TURNOFFSCREENPRESENTER_HPP
#define TURNOFFSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class turnoffScreenView;

class turnoffScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    turnoffScreenPresenter(turnoffScreenView& v);

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

    virtual ~turnoffScreenPresenter() {}

private:
    turnoffScreenPresenter();

    turnoffScreenView& view;
};

#endif // TURNOFFSCREENPRESENTER_HPP
