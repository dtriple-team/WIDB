#ifndef DISPATCHORWAITVIEW_HPP
#define DISPATCHORWAITVIEW_HPP

#include <gui_generated/dispatchorwait_screen/dispatchorwaitViewBase.hpp>
#include <gui/dispatchorwait_screen/dispatchorwaitPresenter.hpp>

class dispatchorwaitView : public dispatchorwaitViewBase
{
public:
    dispatchorwaitView();
    virtual ~dispatchorwaitView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // DISPATCHORWAITVIEW_HPP
