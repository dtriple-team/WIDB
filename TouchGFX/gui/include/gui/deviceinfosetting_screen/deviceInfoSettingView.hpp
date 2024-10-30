#ifndef DEVICEINFOSETTINGVIEW_HPP
#define DEVICEINFOSETTINGVIEW_HPP

#include <gui_generated/deviceinfosetting_screen/deviceInfoSettingViewBase.hpp>
#include <gui/deviceinfosetting_screen/deviceInfoSettingPresenter.hpp>

class deviceInfoSettingView : public deviceInfoSettingViewBase
{
public:
    deviceInfoSettingView();
    virtual ~deviceInfoSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt);
#endif

    void handleSwipeRight();
#if !defined(gui_simulation)
    virtual void handleTickEvent();
#endif
protected:

private:
    int initialX;
    int initialY;
};

#endif // DEVICEINFOSETTINGVIEW_HPP
