#ifndef UNCHARGING_SCREENPRESENTER_HPP
#define UNCHARGING_SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class unCharging_screenView;

class unCharging_screenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    unCharging_screenPresenter(unCharging_screenView& v);

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

    virtual ~unCharging_screenPresenter() {}

private:
    unCharging_screenPresenter();

    unCharging_screenView& view;
};

#endif // UNCHARGING_SCREENPRESENTER_HPP
