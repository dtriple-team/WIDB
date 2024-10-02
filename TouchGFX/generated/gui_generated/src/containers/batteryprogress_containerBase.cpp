/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/batteryprogress_containerBase.hpp>
#include <images/BitmapDatabase.hpp>

batteryprogress_containerBase::batteryprogress_containerBase() :
    progressIndicatorValueUpdatedCallback(this, &batteryprogress_containerBase::progressIndicatorValueUpdatedCallbackHandler)
{
    setWidth(240);
    setHeight(23);
    batteryprogress.setXY(197, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(90);
    batteryprogress.setAnchorAtZero(true);
    batteryprogress.setValueSetAction(progressIndicatorValueUpdatedCallback);
    add(batteryprogress);
}

batteryprogress_containerBase::~batteryprogress_containerBase()
{

}

void batteryprogress_containerBase::initialize()
{

}

void batteryprogress_containerBase::progressIndicatorValueUpdatedCallbackHandler(const touchgfx::AbstractProgressIndicator& src)
{
    if (&src == &batteryprogress)
    {
        //updateBATT
        //When batteryprogress progress indicator value updated execute C++ code
        //Execute C++ code
        //extern uint8_t battVal;
        //batteryprogress.setValue(battVal);
    }
}
