#ifndef CHARACTERKEYBOARDVIEW_HPP
#define CHARACTERKEYBOARDVIEW_HPP

#include <gui_generated/characterkeyboard_screen/characterKeyboardViewBase.hpp>
#include <gui/characterkeyboard_screen/characterKeyboardPresenter.hpp>

class characterKeyboardView : public characterKeyboardViewBase
{
public:
    characterKeyboardView();
    virtual ~characterKeyboardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // CHARACTERKEYBOARDVIEW_HPP
