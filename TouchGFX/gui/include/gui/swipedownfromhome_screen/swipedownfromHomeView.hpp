#ifndef SWIPEDOWNFROMHOMEVIEW_HPP
#define SWIPEDOWNFROMHOMEVIEW_HPP

#include <gui_generated/swipedownfromhome_screen/swipedownfromHomeViewBase.hpp>
#include <gui/swipedownfromhome_screen/swipedownfromHomePresenter.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>

class swipedownfromHomeView : public swipedownfromHomeViewBase
{
public:
    swipedownfromHomeView();
    virtual ~swipedownfromHomeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks

    void updateToggleButton1State(bool state); //test
    void updateToggleButton2State(bool state); //test

    void handleSwipeUp(); //rkdalfks

    void slider1Changed(int value);
protected:
    Callback<swipedownfromHomeView, const touchgfx::AbstractButton&> toggleButton1ClickedCallback; //test
    Callback<swipedownfromHomeView, const touchgfx::AbstractButton&> toggleButton2ClickedCallback; //test
    void toggleButton1Clicked(const touchgfx::AbstractButton& source); //test
    void toggleButton2Clicked(const touchgfx::AbstractButton& source); //test

    Callback<swipedownfromHomeView, const Slider&, int> slider1ChangedCallback;
    void slider1ChangedHandler(const Slider& src, int value);

private: //rkdalfks
    int initialX; //rkdalfks
    int initialY; //rkdaflks
};

#endif // SWIPEUPFROMHOMEVIEW_HPP
