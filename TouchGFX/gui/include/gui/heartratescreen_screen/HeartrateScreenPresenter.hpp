#ifndef HEARTRATESCREENPRESENTER_HPP
#define HEARTRATESCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeartrateScreenView;

class HeartrateScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HeartrateScreenPresenter(HeartrateScreenView& v);

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

    virtual void notifySwipeRight(); //rkdalfks
    virtual void notifySwipeLeft();

    virtual ~HeartrateScreenPresenter() {}

private:
    HeartrateScreenPresenter();

    HeartrateScreenView& view;
};

#endif // HEARTRATESCREENPRESENTER_HPP
