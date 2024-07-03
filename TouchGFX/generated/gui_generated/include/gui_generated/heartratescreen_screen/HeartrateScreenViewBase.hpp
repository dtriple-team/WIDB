/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef HEARTRATESCREENVIEWBASE_HPP
#define HEARTRATESCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/heartratescreen_screen/HeartrateScreenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>

class HeartrateScreenViewBase : public touchgfx::View<HeartrateScreenPresenter>
{
public:
    HeartrateScreenViewBase();
    virtual ~HeartrateScreenViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Virtual Action Handlers
     */
    virtual void changeHRVal()
    {
        // Override and implement this function in HeartrateScreen
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background;
    touchgfx::TextArea Heartrate;
    touchgfx::TextAreaWithOneWildcard textArea1;
    touchgfx::ImageProgress batteryprogress;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTAREA1_SIZE = 10;
    touchgfx::Unicode::UnicodeChar textArea1Buffer[TEXTAREA1_SIZE];

private:

};

#endif // HEARTRATESCREENVIEWBASE_HPP
