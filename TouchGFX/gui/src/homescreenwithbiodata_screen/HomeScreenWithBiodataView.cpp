#include <gui/homescreenwithbiodata_screen/HomeScreenWithBiodataView.hpp>
#include "texts/TextKeysAndLanguages.hpp"
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks
#include <ctime> //rkdalfks

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

	touchgfx::Unicode::snprintf(dateBuffer1, DATEBUFFER1_SIZE, "%02d", timeinfo->tm_mon+1);
	touchgfx::Unicode::snprintf(dateBuffer2, DATEBUFFER2_SIZE, "%02d", timeinfo->tm_mday);
	date.invalidate();

	Unicode::snprintf(yearBuffer, YEAR_SIZE, "%04d", timeinfo->tm_year+1900);
	year.invalidate();

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
	}
}

void HomeScreenWithBiodataView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
    if (evt.getType() == GestureEvent::SWIPE_VERTICAL)
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

void HomeScreenWithBiodataView::handleSwipeDown()
{
	application().gotoswipedownfromHomeScreenCoverTransitionNorth();
}

void HomeScreenWithBiodataView::handleSwipeUp()
{
	application().gotoNotificationScreenScreenCoverTransitionSouth();
}
