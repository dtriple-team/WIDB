#ifndef SPO2SCREENPRESENTER_HPP
#define SPO2SCREENPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class Spo2ScreenView;

class Spo2ScreenPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    Spo2ScreenPresenter(Spo2ScreenView& v);

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

    virtual ~Spo2ScreenPresenter() {}

private:
    Spo2ScreenPresenter();

    Spo2ScreenView& view;
};

#endif // SPO2SCREENPRESENTER_HPP
