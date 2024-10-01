#ifndef SPO2SCREENVIEW_HPP
#define SPO2SCREENVIEW_HPP

#include <gui_generated/spo2screen_screen/Spo2ScreenViewBase.hpp>
#include <gui/spo2screen_screen/Spo2ScreenPresenter.hpp>

class Spo2ScreenView : public Spo2ScreenViewBase
{
public:
    Spo2ScreenView();
    virtual ~Spo2ScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks

    void handleSwipeRight(); //rkdalfks

    virtual void changeSpo2Val();
protected:

private: //rkdalfks
    int initialX; //rkdalfks
    int initialY; //rkdalfks
};

#endif // SPO2SCREENVIEW_HPP
