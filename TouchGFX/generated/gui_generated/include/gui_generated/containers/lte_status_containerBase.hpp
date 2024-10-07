/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef LTE_STATUS_CONTAINERBASE_HPP
#define LTE_STATUS_CONTAINERBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>

class lte_status_containerBase : public touchgfx::Container
{
public:
    lte_status_containerBase();
    virtual ~lte_status_containerBase();
    virtual void initialize();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box topleft_box;
    touchgfx::Image lte_image;
    touchgfx::ImageProgress imageProgress1;

private:

};

#endif // LTE_STATUS_CONTAINERBASE_HPP