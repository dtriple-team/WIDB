#include <gui/spo2detail_screen/Spo2DetailView.hpp>
#include <touchgfx/Color.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Utils.hpp> //rkdalfks

Spo2DetailView::Spo2DetailView()
{

}

void Spo2DetailView::setupScreen()
{
    Spo2DetailViewBase::setupScreen();
}

void Spo2DetailView::tearDownScreen()
{
    Spo2DetailViewBase::tearDownScreen();
}

void Spo2DetailView::handleGestureEvent(const GestureEvent& evt) //rkdalfks
{
	if (evt.getType()==GestureEvent::SWIPE_HORIZONTAL)
	{
    	int deltaX = evt.getVelocity();
        //int deltaY = evt.getVelocityY();

        //if(abs(deltaX)>abs(deltaY))
        //{
			if(deltaX>0)
			{
				presenter->notifySwipeRight();
			}
        //}
	}
	Spo2DetailViewBase::handleGestureEvent(evt);
}

void Spo2DetailView::handleSwipeRight() //rkdalfks
{
	application().gotoHomeScreenWithBiodataScreenWipeTransitionWest();
}
