#ifndef SLEEPSCREENVIEW_HPP
#define SLEEPSCREENVIEW_HPP

#include <gui_generated/sleepscreen_screen/SleepScreenViewBase.hpp>
#include <gui/sleepscreen_screen/SleepScreenPresenter.hpp>

class SleepScreenView : public SleepScreenViewBase
{
public:
    SleepScreenView();
    virtual ~SleepScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks
#endif

    void handleSwipeRight(); //rkdalfks
#if !defined(gui_simulation)
    virtual void handleTickEvent();
#endif
protected:

private: //rkdalfks
    int initialX; //rkdalfks
    int initialY; //rkdalfks
};

#endif // SLEEPSCREENVIEW_HPP
