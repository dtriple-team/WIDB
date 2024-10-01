#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataView.hpp>
#include "texts/TextKeysAndLanguages.hpp"
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks
#include <ctime> //rkdalfks

#include "main.h"
extern RTC_TimeTypeDef sTime;
extern RTC_DateTypeDef sDate;

extern uint16_t ssHr;
extern uint16_t ssSpo2;
extern uint32_t ssWalk;

extern uint8_t canDisplayPPG;

#include <cstdlib>

HomeScreenWithBiodataView::HomeScreenWithBiodataView()
	: tickCounter(0), lastUpdateTime(0), digitalHours(0), digitalMinutes(0), digitalSeconds(0),
	  initialX(0), initialY(0)
{
}

void HomeScreenWithBiodataView::setupScreen()
{
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
}

void HomeScreenWithBiodataView::tearDownScreen()
{
    HomeScreenWithBiodataViewBase::tearDownScreen();
}

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

		////////////////// jh ///////////////////
//		digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
//		digitalClock.invalidate();

		if(!canDisplayPPG) return;

		canDisplayPPG = 0;

		touchgfx::Unicode::snprintf(home_heartrate_valueBuffer, HOME_HEARTRATE_VALUE_SIZE, "%02u", ssHr);
		home_heartrate_value.invalidate();
		touchgfx::Unicode::snprintf(home_spo2_valueBuffer, HOME_SPO2_VALUE_SIZE, "%02u", ssSpo2);
		home_spo2_value.invalidate();
		touchgfx::Unicode::snprintf(home_steps_valueBuffer, HOME_STEPS_VALUE_SIZE, "%u", ssWalk);
		home_steps_value.invalidate();

		touchgfx::Unicode::snprintf(heartrate_valueBuffer, HEARTRATE_VALUE_SIZE, "%02u", ssHr);
		heartrate_value.invalidate();
		touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
		spo2_value.invalidate();
		touchgfx::Unicode::snprintf(step_valueBuffer, STEP_VALUE_SIZE, "%u", ssWalk);
		step_value.invalidate();
	}
}

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
			if (deltaY > 20)
			{
				presenter->notifySwipeDown();
			}
    	}
    }
    HomeScreenWithBiodataViewBase::handleGestureEvent(evt);
}

void HomeScreenWithBiodataView::handleSwipeDown()
{
	application().gotoswipedownfromHomeScreenCoverTransitionNorth();
}
