#ifndef NETWORKINFOSETTINGPRESENTER_HPP
#define NETWORKINFOSETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class networkInfoSettingView;

class networkInfoSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    networkInfoSettingPresenter(networkInfoSettingView& v);

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

    virtual ~networkInfoSettingPresenter() {}

private:
    networkInfoSettingPresenter();

    networkInfoSettingView& view;
};

#endif // NETWORKINFOSETTINGPRESENTER_HPP
