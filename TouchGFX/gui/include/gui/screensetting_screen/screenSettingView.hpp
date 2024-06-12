#ifndef SCREENSETTINGVIEW_HPP
#define SCREENSETTINGVIEW_HPP

#include <gui_generated/screensetting_screen/screenSettingViewBase.hpp>
#include <gui/screensetting_screen/screenSettingPresenter.hpp>

class screenSettingView : public screenSettingViewBase
{
public:
    screenSettingView();
    virtual ~screenSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks

    void handleSwipeRight();

protected:

private: //rkdalfks
    int initialX;
    int initialY;
};

#endif // SCREENSETTINGVIEW_HPP
