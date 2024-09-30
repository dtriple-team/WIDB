/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef HOMESCREENWITHBIODATAVIEWBASE_HPP
#define HOMESCREENWITHBIODATAVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataPresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/containers/SwipeContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/containers/clock/DigitalClock.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/containers/progress_indicators/CircleProgress.hpp>
#include <touchgfx/widgets/canvas/PainterRGB565.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/containers/progress_indicators/ImageProgress.hpp>

class HomeScreenWithBiodataViewBase : public touchgfx::View<HomeScreenWithBiodataPresenter>
{
public:
    HomeScreenWithBiodataViewBase();
    virtual ~HomeScreenWithBiodataViewBase();
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
    touchgfx::SwipeContainer swipeContainer1;
    touchgfx::Container HomeScreen;
    touchgfx::Image home_background;
    touchgfx::DigitalClock digitalClock;
    touchgfx::TextAreaWithTwoWildcards date_value;
    touchgfx::TextAreaWithOneWildcard year_value;
    touchgfx::Image home_heartrate_image;
    touchgfx::Image home_spo2_image;
    touchgfx::Image home_step_image;
    touchgfx::TextAreaWithOneWildcard home_heartrate_value;
    touchgfx::TextAreaWithOneWildcard home_spo2_value;
    touchgfx::TextAreaWithOneWildcard home_steps_value;
    touchgfx::Container StepsScreen;
    touchgfx::Image steps_background;
    touchgfx::TextArea steps_label;
    touchgfx::TextAreaWithOneWildcard step_value;
    touchgfx::Image steps_image;
    touchgfx::CircleProgress steps_progress;
    touchgfx::PainterRGB565 steps_progressPainter;
    touchgfx::Container HeartrateScreen;
    touchgfx::Image heartrate_background;
    touchgfx::TextArea heartrate_label;
    touchgfx::TextAreaWithOneWildcard heartrate_value;
    touchgfx::Button hr_detail_button;
    touchgfx::Container Spo2Screen;
    touchgfx::Image spo2_background;
    touchgfx::TextArea spo2_label;
    touchgfx::TextAreaWithOneWildcard spo2_value;
    touchgfx::Button spo2_detail_button;
    touchgfx::Container SleepScreen;
    touchgfx::Image background_6;
    touchgfx::TextArea sleep_label;
    touchgfx::TextAreaWithTwoWildcards sleeptime_value;
    touchgfx::Image sleep_image;
    touchgfx::CircleProgress sleep_progress;
    touchgfx::PainterRGB565 sleep_progressPainter;
    touchgfx::Box topleft_box;
    touchgfx::Box topright_box;
    touchgfx::ImageProgress batteryprogress;
    touchgfx::Button buttonfornothing;
    touchgfx::Image catm1_image;

    /*
     * Wildcard Buffers
     */
    static const uint16_t DATE_VALUEBUFFER1_SIZE = 3;
    touchgfx::Unicode::UnicodeChar date_valueBuffer1[DATE_VALUEBUFFER1_SIZE];
    static const uint16_t DATE_VALUEBUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar date_valueBuffer2[DATE_VALUEBUFFER2_SIZE];
    static const uint16_t YEAR_VALUE_SIZE = 5;
    touchgfx::Unicode::UnicodeChar year_valueBuffer[YEAR_VALUE_SIZE];
    static const uint16_t HOME_HEARTRATE_VALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar home_heartrate_valueBuffer[HOME_HEARTRATE_VALUE_SIZE];
    static const uint16_t HOME_SPO2_VALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar home_spo2_valueBuffer[HOME_SPO2_VALUE_SIZE];
    static const uint16_t HOME_STEPS_VALUE_SIZE = 10;
    touchgfx::Unicode::UnicodeChar home_steps_valueBuffer[HOME_STEPS_VALUE_SIZE];
    static const uint16_t STEP_VALUE_SIZE = 10;
    touchgfx::Unicode::UnicodeChar step_valueBuffer[STEP_VALUE_SIZE];
    static const uint16_t HEARTRATE_VALUE_SIZE = 5;
    touchgfx::Unicode::UnicodeChar heartrate_valueBuffer[HEARTRATE_VALUE_SIZE];
    static const uint16_t SPO2_VALUE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar spo2_valueBuffer[SPO2_VALUE_SIZE];
    static const uint16_t SLEEPTIME_VALUEBUFFER1_SIZE = 4;
    touchgfx::Unicode::UnicodeChar sleeptime_valueBuffer1[SLEEPTIME_VALUEBUFFER1_SIZE];
    static const uint16_t SLEEPTIME_VALUEBUFFER2_SIZE = 4;
    touchgfx::Unicode::UnicodeChar sleeptime_valueBuffer2[SLEEPTIME_VALUEBUFFER2_SIZE];

private:

    /*
     * Canvas Buffer Size
     */
    static const uint32_t CANVAS_BUFFER_SIZE = 3600;
    uint8_t canvasBuffer[CANVAS_BUFFER_SIZE];

    /*
     * Callback Declarations
     */
    touchgfx::Callback<HomeScreenWithBiodataViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // HOMESCREENWITHBIODATAVIEWBASE_HPP
