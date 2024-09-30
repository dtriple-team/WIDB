#ifndef INITBLACKSCREENPRESENTER_HPP
#define INITBLACKSCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class initBlackScreenView;

class initBlackScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    initBlackScreenPresenter(initBlackScreenView& v);

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

    virtual ~initBlackScreenPresenter() {}

private:
    initBlackScreenPresenter();

    initBlackScreenView& view;
};

#endif // INITBLACKSCREENPRESENTER_HPP
