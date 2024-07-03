/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/homescreenwithbiodata_screen/HomeScreenWithBiodataViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

HomeScreenWithBiodataViewBase::HomeScreenWithBiodataViewBase() :
    buttonCallback(this, &HomeScreenWithBiodataViewBase::buttonCallbackHandler)
{
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    swipeContainer1.setXY(0, 0);
    swipeContainer1.setSwipeCutoff(50);
    swipeContainer1.setEndSwipeElasticWidth(50);

    BiometricData.setWidth(240);
    BiometricData.setHeight(280);
    background_1.setXY(0, 0);
    background_1.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    BiometricData.add(background_1);

    button1.setXY(15, 41);
    button1.setBitmaps(touchgfx::Bitmap(BITMAP_BIOBUTTON_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_29_ID));
    button1.setAction(buttonCallback);
    BiometricData.add(button1);

    steps.setPosition(15, 44, 100, 25);
    steps.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    steps.setLinespacing(0);
    steps.setTypedText(touchgfx::TypedText(T_STEPSTEXT));
    BiometricData.add(steps);

    curstepsvalue.setPosition(15, 84, 100, 37);
    curstepsvalue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curstepsvalue.setLinespacing(0);
    Unicode::snprintf(curstepsvalueBuffer, CURSTEPSVALUE_SIZE, "%s", touchgfx::TypedText(T_B_CURSTEPSVALUE).getText());
    curstepsvalue.setWildcard(curstepsvalueBuffer);
    curstepsvalue.setTypedText(touchgfx::TypedText(T_B_CURSTEPS));
    BiometricData.add(curstepsvalue);

    button2.setXY(126, 41);
    button2.setBitmaps(touchgfx::Bitmap(BITMAP_BIOBUTTON_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_29_ID));
    button2.setAction(buttonCallback);
    BiometricData.add(button2);

    hr.setPosition(126, 44, 100, 25);
    hr.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    hr.setLinespacing(0);
    hr.setTypedText(touchgfx::TypedText(T_HEARTRATETEXT));
    BiometricData.add(hr);

    curhrvalue.setPosition(126, 84, 100, 37);
    curhrvalue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curhrvalue.setLinespacing(0);
    Unicode::snprintf(curhrvalueBuffer, CURHRVALUE_SIZE, "%s", touchgfx::TypedText(T_B_CURHRVALUE).getText());
    curhrvalue.setWildcard(curhrvalueBuffer);
    curhrvalue.setTypedText(touchgfx::TypedText(T_B_CURHR));
    BiometricData.add(curhrvalue);

    button3.setXY(15, 157);
    button3.setBitmaps(touchgfx::Bitmap(BITMAP_BIOBUTTON_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_29_ID));
    button3.setAction(buttonCallback);
    BiometricData.add(button3);

    spo2.setPosition(15, 160, 100, 25);
    spo2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    spo2.setLinespacing(0);
    spo2.setTypedText(touchgfx::TypedText(T_SPO2TEXT));
    BiometricData.add(spo2);

    curSpo2value.setPosition(15, 199, 100, 37);
    curSpo2value.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curSpo2value.setLinespacing(0);
    Unicode::snprintf(curSpo2valueBuffer, CURSPO2VALUE_SIZE, "%s", touchgfx::TypedText(T_B_CURSPO2VALUE).getText());
    curSpo2value.setWildcard(curSpo2valueBuffer);
    curSpo2value.setTypedText(touchgfx::TypedText(T_B_SPO2));
    BiometricData.add(curSpo2value);

    button4.setXY(126, 157);
    button4.setBitmaps(touchgfx::Bitmap(BITMAP_BIOBUTTON_ID), touchgfx::Bitmap(BITMAP_RECTANGLE_29_ID));
    button4.setAction(buttonCallback);
    BiometricData.add(button4);

    sleep.setPosition(126, 160, 100, 25);
    sleep.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    sleep.setLinespacing(0);
    sleep.setTypedText(touchgfx::TypedText(T_SLEEPTEXT));
    BiometricData.add(sleep);

    curSleepvalue.setPosition(126, 183, 100, 77);
    curSleepvalue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    curSleepvalue.setLinespacing(0);
    touchgfx::Unicode::snprintf(curSleepvalueBuffer1, CURSLEEPVALUEBUFFER1_SIZE, "%s", touchgfx::TypedText(T_B_SLEEPHVALUE).getText());
    curSleepvalue.setWildcard1(curSleepvalueBuffer1);
    touchgfx::Unicode::snprintf(curSleepvalueBuffer2, CURSLEEPVALUEBUFFER2_SIZE, "%s", touchgfx::TypedText(T_B_SLEEPMVALUE).getText());
    curSleepvalue.setWildcard2(curSleepvalueBuffer2);
    curSleepvalue.setTypedText(touchgfx::TypedText(T_B_SLEEP));
    BiometricData.add(curSleepvalue);

    BiometricData_1.setPosition(0, 8, 240, 25);
    BiometricData_1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    BiometricData_1.setLinespacing(0);
    BiometricData_1.setTypedText(touchgfx::TypedText(T_BIOMETRICDATATEXT));
    BiometricData.add(BiometricData_1);

    swipeContainer1.add(BiometricData);

    HomeScreen.setWidth(240);
    HomeScreen.setHeight(280);
    background_2.setXY(0, 0);
    background_2.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    HomeScreen.add(background_2);

    digitalClock.setPosition(0, 72, 240, 98);
    digitalClock.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    digitalClock.setTypedText(touchgfx::TypedText(T_HOMESCREENCLOCK));
    digitalClock.displayLeadingZeroForHourIndicator(true);
    digitalClock.setDisplayMode(touchgfx::DigitalClock::DISPLAY_24_HOUR_NO_SECONDS);
    digitalClock.setTime24Hour(10, 10, 0);
    HomeScreen.add(digitalClock);

    date.setPosition(22, 52, 98, 24);
    date.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    date.setLinespacing(0);
    touchgfx::Unicode::snprintf(dateBuffer1, DATEBUFFER1_SIZE, "%s", touchgfx::TypedText(T_CURMONTH).getText());
    date.setWildcard1(dateBuffer1);
    touchgfx::Unicode::snprintf(dateBuffer2, DATEBUFFER2_SIZE, "%s", touchgfx::TypedText(T_CURDATE).getText());
    date.setWildcard2(dateBuffer2);
    date.setTypedText(touchgfx::TypedText(T_CURMONTHDAY));
    HomeScreen.add(date);

    year.setPosition(126, 52, 95, 24);
    year.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    year.setLinespacing(0);
    Unicode::snprintf(yearBuffer, YEAR_SIZE, "%s", touchgfx::TypedText(T_CURYEARVALUE).getText());
    year.setWildcard(yearBuffer);
    year.setTypedText(touchgfx::TypedText(T_CURYEAR));
    HomeScreen.add(year);

    textArea1.setPosition(47, 170, 73, 21);
    textArea1.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea1.setLinespacing(0);
    Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%s", touchgfx::TypedText(T_H_CURHRVALUE).getText());
    textArea1.setWildcard(textArea1Buffer);
    textArea1.setTypedText(touchgfx::TypedText(T_HOMEHR));
    HomeScreen.add(textArea1);

    image1.setXY(26, 174);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_MINIHEART_ID));
    HomeScreen.add(image1);

    image2.setXY(23, 201);
    image2.setBitmap(touchgfx::Bitmap(BITMAP_MINISPO2_ID));
    HomeScreen.add(image2);

    homecurspo2value.setPosition(47, 199, 73, 20);
    homecurspo2value.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    homecurspo2value.setLinespacing(0);
    Unicode::snprintf(homecurspo2valueBuffer, HOMECURSPO2VALUE_SIZE, "%s", touchgfx::TypedText(T_H_CURSPO2VALUE).getText());
    homecurspo2value.setWildcard(homecurspo2valueBuffer);
    homecurspo2value.setTypedText(touchgfx::TypedText(T_HOMESPO2));
    HomeScreen.add(homecurspo2value);

    image3.setXY(23, 229);
    image3.setBitmap(touchgfx::Bitmap(BITMAP_MINIFOOTPRINT_ID));
    HomeScreen.add(image3);

    textArea3.setPosition(47, 229, 130, 20);
    textArea3.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    textArea3.setLinespacing(0);
    Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%s", touchgfx::TypedText(T_H_CURSTEPSVALUE).getText());
    textArea3.setWildcard(textArea3Buffer);
    textArea3.setTypedText(touchgfx::TypedText(T_HOMESTEPS));
    HomeScreen.add(textArea3);

    swipeContainer1.add(HomeScreen);

    StepsScreen.setWidth(240);
    StepsScreen.setHeight(280);
    background_3.setXY(0, 0);
    background_3.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    StepsScreen.add(background_3);

    Steps.setPosition(0, 8, 240, 25);
    Steps.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Steps.setLinespacing(0);
    Steps.setTypedText(touchgfx::TypedText(T_STEPSTEXT));
    StepsScreen.add(Steps);

    StepValue.setPosition(0, 219, 240, 33);
    StepValue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    StepValue.setLinespacing(0);
    Unicode::snprintf(StepValueBuffer, STEPVALUE_SIZE, "%s", touchgfx::TypedText(T_CURSTEPSVALUE).getText());
    StepValue.setWildcard(StepValueBuffer);
    StepValue.setTypedText(touchgfx::TypedText(T_CURSTEPS));
    StepsScreen.add(StepValue);

    swipeContainer1.add(StepsScreen);

    HeartrateScreen.setWidth(240);
    HeartrateScreen.setHeight(280);
    background_4.setXY(0, 0);
    background_4.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    HeartrateScreen.add(background_4);

    Heartrate.setPosition(0, 8, 240, 25);
    Heartrate.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Heartrate.setLinespacing(0);
    Heartrate.setTypedText(touchgfx::TypedText(T_HEARTRATETEXT));
    HeartrateScreen.add(Heartrate);

    HeartrateValue.setPosition(0, 219, 240, 33);
    HeartrateValue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    HeartrateValue.setLinespacing(0);
    Unicode::snprintf(HeartrateValueBuffer, HEARTRATEVALUE_SIZE, "%s", touchgfx::TypedText(T_CURHRVALUE).getText());
    HeartrateValue.setWildcard(HeartrateValueBuffer);
    HeartrateValue.setTypedText(touchgfx::TypedText(T_CURHR));
    HeartrateScreen.add(HeartrateValue);

    swipeContainer1.add(HeartrateScreen);

    Spo2Screen.setWidth(240);
    Spo2Screen.setHeight(280);
    background_5.setXY(0, 0);
    background_5.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    Spo2Screen.add(background_5);

    Spo2.setPosition(0, 8, 240, 25);
    Spo2.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Spo2.setLinespacing(0);
    Spo2.setTypedText(touchgfx::TypedText(T_SPO2TEXT));
    Spo2Screen.add(Spo2);

    Spo2Value.setPosition(0, 219, 240, 33);
    Spo2Value.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Spo2Value.setLinespacing(0);
    Unicode::snprintf(Spo2ValueBuffer, SPO2VALUE_SIZE, "%s", touchgfx::TypedText(T_CURSPO2VALUE).getText());
    Spo2Value.setWildcard(Spo2ValueBuffer);
    Spo2Value.setTypedText(touchgfx::TypedText(T_CURSPO2));
    Spo2Screen.add(Spo2Value);

    swipeContainer1.add(Spo2Screen);

    SleepScreen.setWidth(240);
    SleepScreen.setHeight(280);
    background_6.setXY(0, 0);
    background_6.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    SleepScreen.add(background_6);

    Sleep.setPosition(0, 8, 240, 25);
    Sleep.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    Sleep.setLinespacing(0);
    Sleep.setTypedText(touchgfx::TypedText(T_SLEEPTEXT));
    SleepScreen.add(Sleep);

    SleepValue.setPosition(0, 219, 240, 33);
    SleepValue.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    SleepValue.setLinespacing(0);
    touchgfx::Unicode::snprintf(SleepValueBuffer1, SLEEPVALUEBUFFER1_SIZE, "%s", touchgfx::TypedText(T_CURSLEEPHVALUE).getText());
    SleepValue.setWildcard1(SleepValueBuffer1);
    touchgfx::Unicode::snprintf(SleepValueBuffer2, SLEEPVALUEBUFFER2_SIZE, "%s", touchgfx::TypedText(T_CURSLEEPMVALUE).getText());
    SleepValue.setWildcard2(SleepValueBuffer2);
    SleepValue.setTypedText(touchgfx::TypedText(T_CURSLEEP));
    SleepScreen.add(SleepValue);

    swipeContainer1.add(SleepScreen);

    swipeContainer1.setSelectedPage(1);
    add(swipeContainer1);

    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    button5.setXY(0, 0);
    button5.setBitmaps(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_NORMAL_ID), touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_WIDGETS_BUTTON_REGULAR_HEIGHT_50_MEDIUM_ROUNDED_PRESSED_ID));
    button5.setVisible(false);
    button5.setAction(buttonCallback);
    add(button5);
}

HomeScreenWithBiodataViewBase::~HomeScreenWithBiodataViewBase()
{

}

void HomeScreenWithBiodataViewBase::setupScreen()
{

}

void HomeScreenWithBiodataViewBase::buttonCallbackHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &button1)
    {
        //movetoSteps
        //When button1 clicked change screen to StepsScreen
        //Go to StepsScreen with screen transition towards East
        application().gotoStepsScreenScreenCoverTransitionEast();
    }
    if (&src == &button2)
    {
        //movetoHr
        //When button2 clicked change screen to HeartrateScreen
        //Go to HeartrateScreen with screen transition towards East
        application().gotoHeartrateScreenScreenCoverTransitionEast();
    }
    if (&src == &button3)
    {
        //movetoSpo2
        //When button3 clicked change screen to Spo2Screen
        //Go to Spo2Screen with screen transition towards East
        application().gotoSpo2ScreenScreenCoverTransitionEast();
    }
    if (&src == &button4)
    {
        //movetoSleep
        //When button4 clicked change screen to SleepScreen
        //Go to SleepScreen with screen transition towards East
        application().gotoSleepScreenScreenCoverTransitionEast();
    }
    if (&src == &button5)
    {
        //Interaction1
        //When button5 clicked change screen to swipedownfromHome
        //Go to swipedownfromHome with screen transition towards North
        application().gotoswipedownfromHomeScreenCoverTransitionNorth();
        //Interaction2
        //When button5 clicked change screen to NotificationScreen
        //Go to NotificationScreen with screen transition towards South
        application().gotoNotificationScreenScreenCoverTransitionSouth();
    }
}
