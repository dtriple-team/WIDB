#ifndef INFORMATIONSETTINGPRESENTER_HPP
#define INFORMATIONSETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class informationSettingView;

class informationSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    informationSettingPresenter(informationSettingView& v);

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

    virtual ~informationSettingPresenter() {}

private:
    informationSettingPresenter();

    informationSettingView& view;
};

#endif // INFORMATIONSETTINGPRESENTER_HPP
