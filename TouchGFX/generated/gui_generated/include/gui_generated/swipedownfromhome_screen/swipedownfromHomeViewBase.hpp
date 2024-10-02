/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SWIPEDOWNFROMHOMEVIEWBASE_HPP
#define SWIPEDOWNFROMHOMEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/swipedownfromhome_screen/swipedownfromHomePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <gui/containers/batteryprogress_container.hpp>

class swipedownfromHomeViewBase : public touchgfx::View<swipedownfromHomePresenter>
{
public:
    swipedownfromHomeViewBase();
    virtual ~swipedownfromHomeViewBase();
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
    touchgfx::ToggleButton haptic_togglebutton;
    touchgfx::ToggleButton sound_togglebutton;
    touchgfx::Button setting_button;
    touchgfx::ToggleButton wifi_togglebutton;
    touchgfx::ToggleButton bluetooth_togglebutton;
    touchgfx::Button information_button;
    touchgfx::Button flashlight_button;
    touchgfx::Slider slider1;
    touchgfx::Image haptic_image;
    touchgfx::Image sound_image;
    touchgfx::Image setting_image;
    touchgfx::Image information_image;
    touchgfx::Image brightness_image;
    touchgfx::Image flashlight_image;
    touchgfx::Box topright_box;
    touchgfx::Box topleft_box;
    touchgfx::Button buttonfornothing;
    touchgfx::Image catm1_image;
    batteryprogress_container batteryprogress_container1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<swipedownfromHomeViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SWIPEDOWNFROMHOMEVIEWBASE_HPP
