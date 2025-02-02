/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/stepsscreen_screen/StepsScreenViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

StepsScreenViewBase::StepsScreenViewBase() :
    buttonCallback(this, &StepsScreenViewBase::buttonCallbackHandler),
    frameCountInteraction3Interval(0)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    steps_label.setPosition(0, 4, 240, 30);
    steps_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    steps_label.setLinespacing(0);
    steps_label.setTypedText(touchgfx::TypedText(T_STEPSTEXT));
    add(steps_label);

    steps_value.setPosition(0, 215, 240, 45);
    steps_value.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    steps_value.setLinespacing(0);
    Unicode::snprintf(steps_valueBuffer, STEPS_VALUE_SIZE, "%s", touchgfx::TypedText(T_CURSTEPSVALUE).getText());
    steps_value.setWildcard(steps_valueBuffer);
    steps_value.setTypedText(touchgfx::TypedText(T_CURSTEPS));
    add(steps_value);

    topright_image.setPosition(185, 0, 55, 33);
    topright_image.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topright_image);

    steps_image.setXY(85, 90);
    steps_image.setBitmap(touchgfx::Bitmap(BITMAP_FOOTPRINT_ICON_ID));
    add(steps_image);

    steps_progress.setXY(30, 35);
    steps_progress.setProgressIndicatorPosition(0, 0, 180, 180);
    steps_progress.setRange(0, 100);
    steps_progress.setCenter(90, 90);
    steps_progress.setRadius(67.5f);
    steps_progress.setLineWidth(13);
    steps_progress.setStartEndAngle(0, 360);
    steps_progress.setCapPrecision(10);
    steps_progress.setBackground(touchgfx::Bitmap(BITMAP_FOOTPRINT_PROGRESSBAR_BACK_ID));
    steps_progressPainter.setColor(touchgfx::Color::getColorFromRGB(93, 211, 74));
    steps_progress.setPainter(steps_progressPainter);
    steps_progress.setValue(60);
    add(steps_progress);

    buttonfornothing.setXY(0, 0);
    buttonfornothing.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID));
    buttonfornothing.setVisible(false);
    buttonfornothing.setAction(buttonCallback);
    add(buttonfornothing);

    batteryprogress_container1.setXY(0, 0);
    add(batteryprogress_container1);

    lte_status_container1.setXY(0, 0);
    add(lte_status_container1);
}

StepsScreenViewBase::~StepsScreenViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void StepsScreenViewBase::setupScreen()
{
    batteryprogress_container1.initialize();
    lte_status_container1.initialize();
}

void StepsScreenViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &buttonfornothing)
    {
        //Interaction1
        //When buttonfornothing clicked change screen to HomeScreenWithBiodata
        //Go to HomeScreenWithBiodata with screen transition towards West
        application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
        //Interaction2
        //When buttonfornothing clicked change screen to HeartrateScreen
        //Go to HeartrateScreen with screen transition towards East
        application().gotoHeartrateScreenScreenWipeTransitionEast();
    }
}

void StepsScreenViewBase::handleTickEvent()
{
    //changeStepVal
    //When every N tick call changeStepVal on StepsScreen
    //Call changeStepVal
    changeStepVal();

    frameCountInteraction3Interval++;
    if(frameCountInteraction3Interval == TICK_INTERACTION3_INTERVAL)
    {
        //Interaction3
        //When every N tick call changeStepVal on StepsScreen
        //Call changeStepVal
        changeStepVal();
        frameCountInteraction3Interval = 0;
    }
}
