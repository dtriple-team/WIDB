#ifndef UNCHARGING_SCREENVIEW_HPP
#define UNCHARGING_SCREENVIEW_HPP

#include <gui_generated/uncharging_screen_screen/unCharging_screenViewBase.hpp>
#include <gui/uncharging_screen_screen/unCharging_screenPresenter.hpp>

class unCharging_screenView : public unCharging_screenViewBase
{
public:
    unCharging_screenView();
    virtual ~unCharging_screenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // UNCHARGING_SCREENVIEW_HPP
