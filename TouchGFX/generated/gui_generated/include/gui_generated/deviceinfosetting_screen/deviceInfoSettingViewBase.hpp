/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef DEVICEINFOSETTINGVIEWBASE_HPP
#define DEVICEINFOSETTINGVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/deviceinfosetting_screen/deviceInfoSettingPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <gui/containers/batteryprogress_container.hpp>

class deviceInfoSettingViewBase : public touchgfx::View<deviceInfoSettingPresenter>
{
public:
    deviceInfoSettingViewBase();
    virtual ~deviceInfoSettingViewBase();
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
    touchgfx::TextArea deviceinfo_label;
    touchgfx::TextAreaWithOneWildcard model_label;
    touchgfx::TextAreaWithOneWildcard version_label;
    touchgfx::TextAreaWithOneWildcard id_label;
    touchgfx::TextAreaWithOneWildcard serialnumber_label;
    touchgfx::TextAreaWithOneWildcard servicenumber_label;
    touchgfx::Button buttonfornothing;
    batteryprogress_container batteryprogress_container1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t MODEL_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar model_labelBuffer[MODEL_LABEL_SIZE];
    static const uint16_t VERSION_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar version_labelBuffer[VERSION_LABEL_SIZE];
    static const uint16_t ID_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar id_labelBuffer[ID_LABEL_SIZE];
    static const uint16_t SERIALNUMBER_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar serialnumber_labelBuffer[SERIALNUMBER_LABEL_SIZE];
    static const uint16_t SERVICENUMBER_LABEL_SIZE = 20;
    touchgfx::Unicode::UnicodeChar servicenumber_labelBuffer[SERVICENUMBER_LABEL_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<deviceInfoSettingViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // DEVICEINFOSETTINGVIEWBASE_HPP
