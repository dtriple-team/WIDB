#ifndef ENGLISHKEYBOARDVIEW_HPP
#define ENGLISHKEYBOARDVIEW_HPP

#include <gui_generated/englishkeyboard_screen/englishKeyboardViewBase.hpp>
#include <gui/englishkeyboard_screen/englishKeyboardPresenter.hpp>

class englishKeyboardView : public englishKeyboardViewBase
{
public:
    englishKeyboardView();
    virtual ~englishKeyboardView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // ENGLISHKEYBOARDVIEW_HPP
