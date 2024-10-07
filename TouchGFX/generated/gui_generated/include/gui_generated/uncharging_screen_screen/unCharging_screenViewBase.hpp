/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef UNCHARGING_SCREENVIEWBASE_HPP
#define UNCHARGING_SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/uncharging_screen_screen/unCharging_screenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class unCharging_screenViewBase : public touchgfx::View<unCharging_screenPresenter>
{
public:
    unCharging_screenViewBase();
    virtual ~unCharging_screenViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Custom Actions
     */
    virtual void changeUnChargeScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background;
    touchgfx::TextArea textArea1;
    touchgfx::Image image1;

private:

    /*
     * Tick Counter Declarations
     */
    static const uint32_t TICK_CHANGEHOMESCREEN_INTERVAL = 120;
    uint32_t frameCountChangeHomeScreenInterval;

};

#endif // UNCHARGING_SCREENVIEWBASE_HPP