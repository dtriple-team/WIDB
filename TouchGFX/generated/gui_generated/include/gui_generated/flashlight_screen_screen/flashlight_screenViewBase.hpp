/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FLASHLIGHT_SCREENVIEWBASE_HPP
#define FLASHLIGHT_SCREENVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/flashlight_screen_screen/flashlight_screenPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/buttons/Buttons.hpp>

class flashlight_screenViewBase : public touchgfx::View<flashlight_screenPresenter>
{
public:
    flashlight_screenViewBase();
    virtual ~flashlight_screenViewBase();
    virtual void setupScreen();
    virtual void transitionBegins();

    /*
     * Custom Actions
     */
    virtual void changeMaxBrightness()
    {
        // Override and implement this function in Screen1
    }
    
    virtual void changeBeforeBrightness()
    {
        // Override and implement this function in Screen1
    }
    

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Box box1;
    touchgfx::Image flashlight_image;
    touchgfx::BoxWithBorderButtonStyle< touchgfx::ClickButtonTrigger >  flashlightBackBTN;

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<flashlight_screenViewBase, const touchgfx::AbstractButtonContainer&> flexButtonCallback;

    /*
     * Callback Handler Declarations
     */
    void flexButtonCallbackHandler(const touchgfx::AbstractButtonContainer& src);

};

#endif // FLASHLIGHT_SCREENVIEWBASE_HPP
