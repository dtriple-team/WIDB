/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SETTINGSCREENVIEWBASE_HPP
#define SETTINGSCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/settingscreen_screen/SettingScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <gui/containers/batteryprogress_container.hpp>
#include <gui/containers/lte_status_container.hpp>

class SettingScreenViewBase : public touchgfx::View<SettingScreenPresenter>
{
public:
    SettingScreenViewBase();
    virtual ~SettingScreenViewBase();
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
    touchgfx::ScrollableContainer settingscrollablecontainer;
    touchgfx::Button screen_button;
    touchgfx::Button soundnhaptics_button;
    touchgfx::Button language_button;
    touchgfx::Button findmyphone_button;
    touchgfx::Button information_button;
    touchgfx::Button system_button;
    touchgfx::Image screenbutton_icon_back;
    touchgfx::Image snhbutton_icon_back;
    touchgfx::Image languagebutton_icon_back;
    touchgfx::Image phonebutton_icon_back;
    touchgfx::Image informationbutton_icon_back;
    touchgfx::Image systembutton_icon_back;
    touchgfx::TextArea screen_label;
    touchgfx::TextArea soundnhaptics_label;
    touchgfx::TextArea language_label;
    touchgfx::TextArea findmyphone_label;
    touchgfx::TextArea information_label;
    touchgfx::TextArea system_label;
    touchgfx::Box bottom_padding_box;
    touchgfx::Image screen_image;
    touchgfx::Image sound_image;
    touchgfx::Image language_image;
    touchgfx::Image phone_image;
    touchgfx::Image information_image;
    touchgfx::Image system_image;
    touchgfx::TextArea setting_label;
    touchgfx::Button buttonfornothing;
    batteryprogress_container batteryprogress_container1;
    lte_status_container lte_status_container1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<SettingScreenViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // SETTINGSCREENVIEWBASE_HPP
