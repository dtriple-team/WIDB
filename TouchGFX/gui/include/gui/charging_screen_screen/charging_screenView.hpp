#ifndef CHARGING_SCREENVIEW_HPP
#define CHARGING_SCREENVIEW_HPP

#include <gui_generated/charging_screen_screen/charging_screenViewBase.hpp>
#include <gui/charging_screen_screen/charging_screenPresenter.hpp>

class charging_screenView : public charging_screenViewBase
{
public:
    charging_screenView();
    virtual ~charging_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CHARGING_SCREENVIEW_HPP
