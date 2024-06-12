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
    virtual void handleGestureEvent(const GestureEvent& evt);

    void handleSwipeRight();
protected:

private:
    int initialX;
    int initialY;
};

#endif // DEVICEINFOSETTINGVIEW_HPP
