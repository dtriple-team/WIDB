/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef NETWORKINFOSETTINGVIEWBASE_HPP
#define NETWORKINFOSETTINGVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/networkinfosetting_screen/networkInfoSettingPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>

class networkInfoSettingViewBase : public touchgfx::View<networkInfoSettingPresenter>
{
public:
    networkInfoSettingViewBase();
    virtual ~networkInfoSettingViewBase();
    virtual void setupScreen();
    virtual void transitionBegins();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background;
    touchgfx::TextArea networkinfo_label;
    touchgfx::TextAreaWithOneWildcard imei_label;
    touchgfx::TextAreaWithOneWildcard iccid_label;
    touchgfx::ImageProgress batteryprogress;

    /*
     * Wildcard Buffers
     */
    static const uint16_t IMEI_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar imei_labelBuffer[IMEI_LABEL_SIZE];
    static const uint16_t ICCID_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar iccid_labelBuffer[ICCID_LABEL_SIZE];

private:

};

#endif // NETWORKINFOSETTINGVIEWBASE_HPP
