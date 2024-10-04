/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/batteryprogress_containerBase.hpp>
#include <images/BitmapDatabase.hpp>

batteryprogress_containerBase::batteryprogress_containerBase()
{
    setWidth(240);
    setHeight(23);
    batteryprogress.setXY(190, 8);
    batteryprogress.setProgressIndicatorPosition(2, 2, 27, 11);
    batteryprogress.setRange(0, 100);
    batteryprogress.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    batteryprogress.setBackground(touchgfx::Bitmap(BITMAP_GROUP_6_ID));
    batteryprogress.setBitmap(BITMAP_BATTPERCENTAGE_ID);
    batteryprogress.setValue(0);
    batteryprogress.setAnchorAtZero(true);
    add(batteryprogress);

    chargingIMG.setXY(198, 8);
    chargingIMG.setBitmap(touchgfx::Bitmap(BITMAP_CHARGE_ON_BATT_ID));
    chargingIMG.setVisible(false);
    add(chargingIMG);

    extern uint8_t battVal;
    batteryprogress.setValue(battVal);
	extern bool isCharging;
	chargingIMG.setVisible(isCharging);
}

batteryprogress_containerBase::~batteryprogress_containerBase()
{

}

void batteryprogress_containerBase::initialize()
{

}

void batteryprogress_containerBase::changeBATTVal()
{
    //updateBATT
    //When changeBATTVal is called execute C++ code
    //Execute C++ code
    extern uint8_t battVal;
    batteryprogress.setValue(battVal);
}

void batteryprogress_containerBase::batteryCharging()
{
    //charging
    //When batteryCharging is called execute C++ code
    //Execute C++ code
    remove(chargingIMG);
	setWidth(240);
	setHeight(23);
	chargingIMG.setXY(198, 8);
    chargingIMG.setBitmap(touchgfx::Bitmap(BITMAP_CHARGE_ON_BATT_ID));
	extern bool isCharging;
	chargingIMG.setVisible(isCharging);
	add(chargingIMG);

	chargingIMG.invalidate();
}
