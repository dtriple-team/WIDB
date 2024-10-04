/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef CHARGING_SCREENVIEWBASE_HPP
#define CHARGING_SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/charging_screen_screen/charging_screenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class charging_screenViewBase : public touchgfx::View<charging_screenPresenter>
{
public:
    charging_screenViewBase();
    virtual ~charging_screenViewBase();
    virtual void setupScreen();
    virtual void handleTickEvent();

    /*
     * Custom Actions
     */
    virtual void changeChargeScreen();

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

#endif // CHARGING_SCREENVIEWBASE_HPP
