#ifndef TURNOFFSCREENVIEW_HPP
#define TURNOFFSCREENVIEW_HPP

#include <gui_generated/turnoffscreen_screen/turnoffScreenViewBase.hpp>
#include <gui/turnoffscreen_screen/turnoffScreenPresenter.hpp>

class turnoffScreenView : public turnoffScreenViewBase
{
public:
    turnoffScreenView();
    virtual ~turnoffScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // TURNOFFSCREENVIEW_HPP
