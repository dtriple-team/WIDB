#ifndef SCREENBRIGHTNESSSETTINGPRESENTER_HPP
#define SCREENBRIGHTNESSSETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <touchgfx/Callback.hpp>

using namespace touchgfx;

class screenbrightnessSettingView;

class screenbrightnessSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    screenbrightnessSettingPresenter(screenbrightnessSettingView& v);

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

    void updateSlider1Value(int value); //test
    int getSlider1Value() const;

    virtual ~screenbrightnessSettingPresenter() {}

private:
    screenbrightnessSettingPresenter();

    screenbrightnessSettingView& view;
};

#endif // SCREENBRIGHTNESSSETTINGPRESENTER_HPP
