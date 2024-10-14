#ifndef INFORMATIONSETTINGVIEW_HPP
#define INFORMATIONSETTINGVIEW_HPP

#include <gui_generated/informationsetting_screen/informationSettingViewBase.hpp>
#include <gui/informationsetting_screen/informationSettingPresenter.hpp>

class informationSettingView : public informationSettingViewBase
{
public:
    informationSettingView();
    virtual ~informationSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
//    virtual void handleGestureEvent(const GestureEvent& evt);

    void handleSwipeRight();

    virtual void handleTickEvent();
protected:

private:
    int initialX;
    int initialY;
};

#endif // INFORMATIONSETTINGVIEW_HPP
