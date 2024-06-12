#ifndef DISPATCHORWAITPRESENTER_HPP
#define DISPATCHORWAITPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class dispatchorwaitView;

class dispatchorwaitPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    dispatchorwaitPresenter(dispatchorwaitView& v);

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

    virtual ~dispatchorwaitPresenter() {}

private:
    dispatchorwaitPresenter();

    dispatchorwaitView& view;
};

#endif // DISPATCHORWAITPRESENTER_HPP
