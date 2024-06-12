#ifndef WIFISETTINGPRESENTER_HPP
#define WIFISETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class wifiSettingView;

class wifiSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    wifiSettingPresenter(wifiSettingView& v);

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

    virtual ~wifiSettingPresenter() {}

private:
    wifiSettingPresenter();

    wifiSettingView& view;
};

#endif // WIFISETTINGPRESENTER_HPP
