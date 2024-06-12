#ifndef SCREENBRIGHTNESSSETTINGVIEW_HPP
#define SCREENBRIGHTNESSSETTINGVIEW_HPP

#include <gui_generated/screenbrightnesssetting_screen/screenbrightnessSettingViewBase.hpp>
#include <gui/screenbrightnesssetting_screen/screenbrightnessSettingPresenter.hpp>

class screenbrightnessSettingView : public screenbrightnessSettingViewBase
{
public:
    screenbrightnessSettingView();
    virtual ~screenbrightnessSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt);

    void handleSwipeRight();

    void slider1Changed(int value);
protected:
    Callback<screenbrightnessSettingView, const Slider&, int> slider1ChangedCallback;
    void slider1ChangedHandler(const Slider& src, int value);

private:
    int initialX;
    int initialY;
};

#endif // SCREENBRIGHTNESSSETTINGVIEW_HPP
