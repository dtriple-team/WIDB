/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/lte_status_containerBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

lte_status_containerBase::lte_status_containerBase()
{
    setWidth(55);
    setHeight(33);
    topleft_box.setPosition(0, 0, 55, 33);
    topleft_box.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topleft_box);

    lte_image.setXY(15, 11);
    lte_image.setBitmap(touchgfx::Bitmap(BITMAP_LTE_NOTCONNECTED_ID));
    add(lte_image);

    imageProgress1.setXY(15, 11);
    imageProgress1.setProgressIndicatorPosition(0, 0, 15, 12);
    imageProgress1.setRange(0, 4);
    imageProgress1.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    imageProgress1.setBackground(touchgfx::Bitmap(BITMAP_LTE_NOTCONNECTED_ID));
    imageProgress1.setBitmap(BITMAP_LTE_ID);
    imageProgress1.setValue(4);
    imageProgress1.setAnchorAtZero(true);
    add(imageProgress1);

    imageProgress2.setXY(35, 10);
    imageProgress2.setProgressIndicatorPosition(0, 0, 15, 15);
    imageProgress2.setRange(0, 1);
    imageProgress2.setDirection(touchgfx::AbstractDirectionProgress::RIGHT);
    imageProgress2.setBackground(touchgfx::Bitmap(BITMAP_GPS_NOTCONNECTED_ID));
    imageProgress2.setBitmap(BITMAP_GPS_CONNECTED_ID);
    imageProgress2.setValue(1);
    imageProgress2.setAnchorAtZero(true);
    add(imageProgress2);

    extern uint8_t lteRSSI_0_4;
	imageProgress1.setValue(lteRSSI_0_4);
	extern uint8_t gpsRSSI_0_1;
	imageProgress2.setValue(gpsRSSI_0_1);
}

lte_status_containerBase::~lte_status_containerBase()
{

}

void lte_status_containerBase::initialize()
{

}
