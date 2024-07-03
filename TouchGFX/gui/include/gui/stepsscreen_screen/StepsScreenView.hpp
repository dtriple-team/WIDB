#ifndef STEPSSCREENVIEW_HPP
#define STEPSSCREENVIEW_HPP

#include <gui_generated/stepsscreen_screen/StepsScreenViewBase.hpp>
#include <gui/stepsscreen_screen/StepsScreenPresenter.hpp>

class StepsScreenView : public StepsScreenViewBase
{
public:
    StepsScreenView();
    virtual ~StepsScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks

    void handleSwipeRight(); //rkdalfks

    void changeStepVal();
protected:

private: //rkdalfks
    int initialX; //rkdalfks
    int initialY; //rkdalfks

    uint8_t timeTick;
};

#endif // STEPSSCREENVIEW_HPP
