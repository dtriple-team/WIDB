/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/containers/lte_status_containerBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

lte_status_containerBase::lte_status_containerBase()
{
    setWidth(65);
    setHeight(33);
    topleft_box.setPosition(0, 0, 65, 33);
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
    imageProgress1.setValue(0);
    imageProgress1.setAnchorAtZero(true);
    add(imageProgress1);

    extern uint8_t lteRSSI_0_4;
    imageProgress1.setValue(lteRSSI_0_4);
}

lte_status_containerBase::~lte_status_containerBase()
{

}

void lte_status_containerBase::initialize()
{

}