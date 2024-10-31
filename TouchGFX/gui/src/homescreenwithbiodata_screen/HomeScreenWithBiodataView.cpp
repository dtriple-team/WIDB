#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataView.hpp>
#include "texts/TextKeysAndLanguages.hpp"
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks
#include <ctime> //rkdalfks

#if !defined(gui_simulation)
#include "main.h"
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;
#endif

#include "stdio.h"

#include <cstdlib>

HomeScreenWithBiodataView::HomeScreenWithBiodataView()
	: tickCounter(0), lastUpdateTime(0), digitalHours(0), digitalMinutes(0), digitalSeconds(0),
	  initialX(0), initialY(0)
{
}

void HomeScreenWithBiodataView::setupScreen()
{
    //Texts::setLanguage(KOREAN);
#if defined(gui_simulation)
    HomeScreenWithBiodataViewBase::setupScreen();

	time(&lastUpdateTime);
	struct tm* timeinfo = localtime(&lastUpdateTime);

	touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", timeinfo->tm_mon+1);
	touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", timeinfo->tm_mday);
	date_value.invalidate();

	Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", timeinfo->tm_year+1900);
	year_value.invalidate();

	digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
	digitalClock.invalidate();
#endif

	////////////// jh /////////////////
#if !defined(gui_simulation)
	HomeScreenWithBiodataViewBase::setupScreen();

	touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", sDate.Month);
	touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", sDate.Date);
	date_value.invalidate();

	Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", sDate.Year+2000);
	year_value.invalidate();

	digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
	digitalClock.invalidate();
#endif

//	extern uint8_t battVal;
//	batteryprogress.setValue(battVal);
}

void HomeScreenWithBiodataView::tearDownScreen()
{
    HomeScreenWithBiodataViewBase::tearDownScreen();
}

#if defined(gui_simulation)
void HomeScreenWithBiodataView::handleTickEvent()
{
	tickCounter++;

		if (tickCounter % 60 == 0) // 1초마다 업데이트
		{
			time_t currentTime;
			time(&currentTime);

			double secondsPassed = difftime(currentTime, lastUpdateTime);

			if (secondsPassed >= 1)
			{
				struct tm* timeinfo = localtime(&currentTime);

				digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
				digitalClock.invalidate();

				lastUpdateTime = currentTime; // 업데이트된 시간 저장
			}
		}
}
#endif

#if !defined(gui_simulation)
#include "bl6133.h"
extern "C" {
	#include "nrf9160.h"
	#include "rtc.h"
}
extern GESTURE gesture;
extern uint8_t timeUpdateFlag;
catM1Time nowTimeinfo;

void HomeScreenWithBiodataView::handleTickEvent()
{
	tickCounter++;

	if (tickCounter % 60 == 0) // 1초마다 업데이트
	{
		time_t currentTime;
		time(&currentTime);

//		double secondsPassed = difftime(currentTime, lastUpdateTime);
//
//		if (secondsPassed >= 1)
//		{
//			struct tm* timeinfo = localtime(&currentTime);
//
//			digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//			digitalClock.invalidate();
//
//			lastUpdateTime = currentTime; // 업데이트된 시간 저장
//		}

		////////////////// jh ///////////////////
		struct tm* timeinfo;
		if(timeUpdateFlag){
			timeUpdateFlag = 0;
			nowTimeinfo = getCatM1Time();
			sDate.Year = (uint8_t)nowTimeinfo.year;
			sDate.Month = (uint8_t)nowTimeinfo.month;
			sDate.Date = (uint8_t)nowTimeinfo.day;
			sTime.Hours = (uint8_t)nowTimeinfo.hour;
			sTime.Minutes = (uint8_t)nowTimeinfo.min;
			sTime.Seconds = (uint8_t)nowTimeinfo.sec;

			HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
			HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
			int temp = 0;
		}
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		//PRINT_INFO("Current Time: %02u:%02u:%02u\n", sTime.Hours, sTime.Minutes, sTime.Seconds);
		//PRINT_INFO("Current Date: %04u-%02u-%02u\n", sDate.Year + 2000, sDate.Month, sDate.Date);

		touchgfx::Unicode::snprintf(date_valueBuffer1, DATE_VALUEBUFFER1_SIZE, "%02d", sDate.Month);
		touchgfx::Unicode::snprintf(date_valueBuffer2, DATE_VALUEBUFFER2_SIZE, "%02d", sDate.Date);
		date_value.invalidate();

		Unicode::snprintf(year_valueBuffer, YEAR_VALUE_SIZE, "%04d", sDate.Year+2000);
		year_value.invalidate();

		digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
		digitalClock.invalidate();

//		extern uint8_t battVal;
//		batteryprogress.setValue(battVal);

		extern uint8_t canDisplayPPG;
		if(!canDisplayPPG) return;

		canDisplayPPG = 0;

		extern uint16_t ssHr;
		extern uint16_t ssSpo2;
		extern uint32_t ssWalk;

		touchgfx::Unicode::snprintf(home_heartrate_valueBuffer, HOME_HEARTRATE_VALUE_SIZE, "%02u", ssHr);
		home_heartrate_value.invalidate();
		touchgfx::Unicode::snprintf(home_spo2_valueBuffer, HOME_SPO2_VALUE_SIZE, "%02u", ssSpo2);
		home_spo2_value.invalidate();
		touchgfx::Unicode::snprintf(home_steps_valueBuffer, HOME_STEPS_VALUE_SIZE, "%u", ssWalk);
		home_steps_value.invalidate();

//		touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
//		heartrate_value.invalidate();
//		touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
//		spo2_value.invalidate();
//		touchgfx::Unicode::snprintf(step_valueBuffer, STEP_VALUE_SIZE, "%u", ssWalk);
//		step_value.invalidate();
	}
    if(gesture == SlideDown){
    	presenter->notifySwipeDown();
    }
	else if(gesture == SlideLeft){
		presenter->notifySwipeLeft();
	}
}
#endif

#if defined(gui_simulation)
void HomeScreenWithBiodataView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	int deltaX = 0, deltaY = 0;
	const int swipeThreshold = 20;
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
    {
        deltaY = evt.getVelocity();
    }
    if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL)
    {
    	deltaX = evt.getVelocity();
    }

    if (evt.getType() == GestureEvent::SWIPE_VERTICAL && abs(deltaY)>abs(deltaX))
    {
    	if(abs(deltaY) > swipeThreshold)
    	{
			if (deltaY > -20)
			{
				presenter->notifySwipeDown();
			}
    	}
    }
    else if (evt.getType() == GestureEvent::SWIPE_HORIZONTAL && abs(deltaY)<abs(deltaX))
    {
    	if(abs(deltaX) > swipeThreshold)
		{
			if (deltaX < 0)
			{
				presenter->notifySwipeLeft();
			}
		}
    }
    HomeScreenWithBiodataViewBase::handleGestureEvent(evt);
}
#endif

void HomeScreenWithBiodataView::handleSwipeDown()
{
	application().gotoswipedownfromHomeScreenCoverTransitionNorth();
}

void HomeScreenWithBiodataView::handleSwipeLeft()
{
	application().gotoStepsScreenScreenSlideTransitionEast();
}
