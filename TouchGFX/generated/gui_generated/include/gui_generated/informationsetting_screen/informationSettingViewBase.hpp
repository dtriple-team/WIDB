/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef INFORMATIONSETTINGVIEWBASE_HPP
#define INFORMATIONSETTINGVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/informationsetting_screen/informationSettingPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <gui/containers/batteryprogress_container.hpp>

class informationSettingViewBase : public touchgfx::View<informationSettingPresenter>
{
public:
    informationSettingViewBase();
    virtual ~informationSettingViewBase();
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
    touchgfx::TextArea information_label;
    touchgfx::Image device_icon_back;
    touchgfx::Image network_icon_back;
    touchgfx::TextArea device_label;
    touchgfx::TextArea network_label;
    touchgfx::Image device_arrow_image;
    touchgfx::Image network_arrow_image;
    touchgfx::Button device_button;
    touchgfx::Button network_button;
    touchgfx::Image device_image;
    touchgfx::Image network_image;
    batteryprogress_container batteryprogress_container1;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<informationSettingViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // INFORMATIONSETTINGVIEWBASE_HPP
