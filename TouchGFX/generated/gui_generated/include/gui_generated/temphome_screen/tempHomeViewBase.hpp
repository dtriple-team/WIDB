/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef TEMPHOMEVIEWBASE_HPP
#define TEMPHOMEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/temphome_screen/tempHomePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>

class tempHomeViewBase : public touchgfx::View<tempHomePresenter>
{
public:
    tempHomeViewBase();
    virtual ~tempHomeViewBase();
    virtual void setupScreen();

    /*
     * Custom Actions
     */
    virtual void changeToHomeScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image background;

private:

};

#endif // TEMPHOMEVIEWBASE_HPP
