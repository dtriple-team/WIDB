#ifndef INOUTVIEW_HPP
#define INOUTVIEW_HPP

#include <gui_generated/inout_screen/inoutViewBase.hpp>
#include <gui/inout_screen/inoutPresenter.hpp>

class inoutView : public inoutViewBase
{
public:
    inoutView();
    virtual ~inoutView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // INOUTVIEW_HPP
