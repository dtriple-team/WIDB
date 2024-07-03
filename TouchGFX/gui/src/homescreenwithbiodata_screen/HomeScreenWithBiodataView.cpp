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

#include <cstdlib>

HomeScreenWithBiodataView::HomeScreenWithBiodataView()
	: tickCounter(0), lastUpdateTime(0), digitalHours(0), digitalMinutes(0), digitalSeconds(0),
	  initialX(0), initialY(0)
{
}

void HomeScreenWithBiodataView::setupScreen()
{
//    HomeScreenWithBiodataViewBase::setupScreen();
//
//	time(&lastUpdateTime);
//	struct tm* timeinfo = localtime(&lastUpdateTime);
//
//	touchgfx::Unicode::snprintf(dateBuffer1, DATEBUFFER1_SIZE, "%02d", timeinfo->tm_mon+1);
//	touchgfx::Unicode::snprintf(dateBuffer2, DATEBUFFER2_SIZE, "%02d", timeinfo->tm_mday);
//	date.invalidate();
//
//	Unicode::snprintf(yearBuffer, YEAR_SIZE, "%04d", timeinfo->tm_year+1900);
//	year.invalidate();
//
//	digitalClock.setTime24Hour(timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
//	digitalClock.invalidate();

	////////////// jh /////////////////

	HomeScreenWithBiodataViewBase::setupScreen();

	touchgfx::Unicode::snprintf(dateBuffer1, DATEBUFFER1_SIZE, "%02d", sDate.Month);
	touchgfx::Unicode::snprintf(dateBuffer2, DATEBUFFER2_SIZE, "%02d", sDate.Date);
	date.invalidate();

	Unicode::snprintf(yearBuffer, YEAR_SIZE, "%04d", sDate.Year+2000);
	year.invalidate();

	digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
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

		///////////// rkdalfks //////////////

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
		digitalClock.setTime24Hour(sTime.Hours, sTime.Minutes, sTime.Seconds);
		digitalClock.invalidate();

		touchgfx::Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%02u", ssHr);
		textArea1.invalidate();
		touchgfx::Unicode::snprintf(homecurspo2valueBuffer, HOMECURSPO2VALUE_SIZE, "%02u", ssSpo2);
		homecurspo2value.invalidate();
		touchgfx::Unicode::snprintf(textArea3Buffer, TEXTAREA3_SIZE, "%u", ssWalk);
		textArea3.invalidate();

		touchgfx::Unicode::snprintf(curhrvalueBuffer, CURHRVALUE_SIZE, "%02u", ssHr);
		curhrvalue.invalidate();
		touchgfx::Unicode::snprintf(curSpo2valueBuffer, CURSPO2VALUE_SIZE, "%02u", ssSpo2);
		curSpo2value.invalidate();
		touchgfx::Unicode::snprintf(curstepsvalueBuffer, CURSTEPSVALUE_SIZE, "%u", ssWalk);
		curstepsvalue.invalidate();

		touchgfx::Unicode::snprintf(HeartrateValueBuffer, HEARTRATEVALUE_SIZE, "%02u", ssHr);
		HeartrateValue.invalidate();
		touchgfx::Unicode::snprintf(Spo2ValueBuffer, SPO2VALUE_SIZE, "%02u", ssSpo2);
		Spo2Value.invalidate();
		touchgfx::Unicode::snprintf(StepValueBuffer, STEPVALUE_SIZE, "%u", ssWalk);
		StepValue.invalidate();
	}
}

void HomeScreenWithBiodataView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL && isDeltaYGreaterThanDeltaX)
    {
        int deltaY = evt.getVelocity();
        if (deltaY > 0)
        {
            presenter->notifySwipeDown();
        }
        else if (deltaY < 0)
        {
        	presenter->notifySwipeUp();
        }
    }
    HomeScreenWithBiodataViewBase::handleGestureEvent(evt);
}

void HomeScreenWithBiodataView::handleDragEvent(const DragEvent& evt)
{
	int deltax = std::abs(evt.getDeltaX());
	int deltay = std::abs(evt.getDeltaY());
	if(deltay > deltax){
		isDeltaYGreaterThanDeltaX = 1;
	} else {
		isDeltaYGreaterThanDeltaX = 0;
	}
	HomeScreenWithBiodataViewBase::handleDragEvent(evt);
}

void HomeScreenWithBiodataView::handleSwipeDown()
{
	application().gotoswipedownfromHomeScreenCoverTransitionNorth();
}

void HomeScreenWithBiodataView::handleSwipeUp()
{
	application().gotoNotificationScreenScreenCoverTransitionSouth();
}
