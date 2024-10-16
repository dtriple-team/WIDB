/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREENSETTINGVIEWBASE_HPP
#define SCREENSETTINGVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screensetting_screen/screenSettingPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <gui/containers/batteryprogress_container.hpp>

class screenSettingViewBase : public touchgfx::View<screenSettingPresenter>
{
public:
    screenSettingViewBase();
    virtual ~screenSettingViewBase();
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
    touchgfx::TextArea screen_label;
    touchgfx::Image ontimebutton_icon_back;
    touchgfx::Image brightnessbutton_icon_back;
    touchgfx::TextArea ontime_label;
    touchgfx::TextArea brightness_label;
    touchgfx::Image ontime_arrow_image;
    touchgfx::Image brightness_arrow_image;
    touchgfx::Button ontime_button;
    touchgfx::Button brightness_button;
    touchgfx::Button buttonfornothing;
    touchgfx::Image ontime_image;
    touchgfx::Image brightness_image;
    batteryprogress_container batteryprogress_container1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<screenSettingViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SCREENSETTINGVIEWBASE_HPP
