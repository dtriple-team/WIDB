#ifndef HOMESCREENWITHBIODATAVIEW_HPP
#define HOMESCREENWITHBIODATAVIEW_HPP

#include <gui_generated/homescreenwithbiodata_screen/HomeScreenWithBiodataViewBase.hpp>
#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataPresenter.hpp>
#include <touchgfx/Unicode.hpp> //rkdalfks
#include <touchgfx/widgets/TextAreaWithWildcard.hpp> //rkdalfks
#include <ctime>

class HomeScreenWithBiodataView : public HomeScreenWithBiodataViewBase
{
public:
    HomeScreenWithBiodataView();
    virtual ~HomeScreenWithBiodataView() {}

    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleTickEvent();

#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks
#endif

    void handleSwipeDown(); //rkdalfks
    void handleSwipeLeft();

protected:

private: //rkdalfks
    int tickCounter;
    time_t lastUpdateTime;
    int digitalHours;
    int digitalMinutes;
    int digitalSeconds;

    int initialX;
    int initialY;
};

#endif // HOMESCREENWITHBIODATAVIEW_HPP
