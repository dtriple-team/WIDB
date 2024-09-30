#ifndef INITBLACKSCREENVIEW_HPP
#define INITBLACKSCREENVIEW_HPP

#include <gui_generated/initblackscreen_screen/initBlackScreenViewBase.hpp>
#include <gui/initblackscreen_screen/initBlackScreenPresenter.hpp>

class initBlackScreenView : public initBlackScreenViewBase
{
public:
    initBlackScreenView();
    virtual ~initBlackScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // INITBLACKSCREENVIEW_HPP
