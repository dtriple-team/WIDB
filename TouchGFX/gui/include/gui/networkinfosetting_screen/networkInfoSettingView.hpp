#ifndef NETWORKINFOSETTINGVIEW_HPP
#define NETWORKINFOSETTINGVIEW_HPP

#include <gui_generated/networkinfosetting_screen/networkInfoSettingViewBase.hpp>
#include <gui/networkinfosetting_screen/networkInfoSettingPresenter.hpp>

class networkInfoSettingView : public networkInfoSettingViewBase
{
public:
    networkInfoSettingView();
    virtual ~networkInfoSettingView() {}
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

#endif // NETWORKINFOSETTINGVIEW_HPP
