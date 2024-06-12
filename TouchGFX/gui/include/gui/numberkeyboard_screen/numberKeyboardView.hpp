#ifndef NUMBERKEYBOARDVIEW_HPP
#define NUMBERKEYBOARDVIEW_HPP

#include <gui_generated/numberkeyboard_screen/numberKeyboardViewBase.hpp>
#include <gui/numberkeyboard_screen/numberKeyboardPresenter.hpp>

class numberKeyboardView : public numberKeyboardViewBase
{
public:
    numberKeyboardView();
    virtual ~numberKeyboardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // NUMBERKEYBOARDVIEW_HPP
