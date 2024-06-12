#ifndef SCREENSETTINGPRESENTER_HPP
#define SCREENSETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class screenSettingView;

class screenSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screenSettingPresenter(screenSettingView& v);

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

    virtual ~screenSettingPresenter() {}

private:
    screenSettingPresenter();

    screenSettingView& view;
};

#endif // SCREENSETTINGPRESENTER_HPP
