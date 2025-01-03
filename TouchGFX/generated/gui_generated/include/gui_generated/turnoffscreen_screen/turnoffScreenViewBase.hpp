/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TURNOFFSCREENVIEWBASE_HPP
#define TURNOFFSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/turnoffscreen_screen/turnoffScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>

class turnoffScreenViewBase : public touchgfx::View<turnoffScreenPresenter>
{
public:
    turnoffScreenViewBase();
    virtual ~turnoffScreenViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background;
    touchgfx::TextArea yousure_label;
    touchgfx::Button no_button;
    touchgfx::Button yes_button;
    touchgfx::TextArea yes_label;
    touchgfx::TextArea no_label;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<turnoffScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // TURNOFFSCREENVIEWBASE_HPP
