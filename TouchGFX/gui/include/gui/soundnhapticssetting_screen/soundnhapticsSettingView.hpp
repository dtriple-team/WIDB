#ifndef SOUNDNHAPTICSSETTINGVIEW_HPP
#define SOUNDNHAPTICSSETTINGVIEW_HPP

#include <gui_generated/soundnhapticssetting_screen/soundnhapticsSettingViewBase.hpp>
#include <gui/soundnhapticssetting_screen/soundnhapticsSettingPresenter.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>

class soundnhapticsSettingView : public soundnhapticsSettingViewBase
{
public:
    soundnhapticsSettingView();
    virtual ~soundnhapticsSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks

    void updateToggleButton1State(bool state);
    void updateToggleButton2State(bool state);

    void handleSwipeRight();
protected:
    Callback<soundnhapticsSettingView, const touchgfx::AbstractButton&> toggleButton1ClickedCallback;
    Callback<soundnhapticsSettingView, const touchgfx::AbstractButton&> toggleButton2ClickedCallback;
    void toggleButton1Clicked(const touchgfx::AbstractButton& source); //test
    void toggleButton2Clicked(const touchgfx::AbstractButton& source); //test

private: //rkdalfks
    int initialX;
    int initialY;
};

#endif // SOUNDNHAPTICSSETTINGVIEW_HPP
