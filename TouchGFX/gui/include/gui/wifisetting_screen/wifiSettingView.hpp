#ifndef WIFISETTINGVIEW_HPP
#define WIFISETTINGVIEW_HPP

#include <gui_generated/wifisetting_screen/wifiSettingViewBase.hpp>
#include <gui/wifisetting_screen/wifiSettingPresenter.hpp>

class wifiSettingView : public wifiSettingViewBase
{
public:
    wifiSettingView();
    virtual ~wifiSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt);

    void handleSwipeRight();
protected:

private:
    int initialX;
    int initialY;
};

#endif // WIFISETTINGVIEW_HPP
