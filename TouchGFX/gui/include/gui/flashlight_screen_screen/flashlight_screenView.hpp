#ifndef FLASHLIGHT_SCREENVIEW_HPP
#define FLASHLIGHT_SCREENVIEW_HPP

#include <gui_generated/flashlight_screen_screen/flashlight_screenViewBase.hpp>
#include <gui/flashlight_screen_screen/flashlight_screenPresenter.hpp>

class flashlight_screenView : public flashlight_screenViewBase
{
public:
    flashlight_screenView();
    virtual ~flashlight_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
#if !defined(gui_simulation)
    virtual void changeMaxBrightness();
    virtual void changeBeforeBrightness();
#endif
protected:
};

#endif // FLASHLIGHT_SCREENVIEW_HPP
