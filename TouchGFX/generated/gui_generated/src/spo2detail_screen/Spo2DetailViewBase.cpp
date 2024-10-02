/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/spo2detail_screen/Spo2DetailViewBase.hpp>
#include <touchgfx/canvas_widget_renderer/CanvasWidgetRenderer.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>
#include <texts/TextKeysAndLanguages.hpp>

Spo2DetailViewBase::Spo2DetailViewBase() :
    frameCountUpdateSpo2Interval(0)
{
    touchgfx::CanvasWidgetRenderer::setupBuffer(canvasBuffer, CANVAS_BUFFER_SIZE);
    
    __background.setPosition(0, 0, 240, 280);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    background.setXY(0, 0);
    background.setBitmap(touchgfx::Bitmap(BITMAP_BACKGROUND_ID));
    add(background);

    spo2_label.setPosition(0, 6, 240, 25);
    spo2_label.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    spo2_label.setLinespacing(0);
    spo2_label.setTypedText(touchgfx::TypedText(T_SPO2TEXT));
    add(spo2_label);

    spo2_image.setXY(15, 33);
    spo2_image.setBitmap(touchgfx::Bitmap(BITMAP_WATERDROP_ID));
    add(spo2_image);

    spo2_value.setPosition(55, 42, 170, 25);
    spo2_value.setColor(touchgfx::Color::getColorFromRGB(255, 255, 255));
    spo2_value.setLinespacing(0);
    Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%s", touchgfx::TypedText(T_CURSPO2VALUE).getText());
    spo2_value.setWildcard(spo2_valueBuffer);
    spo2_value.setTypedText(touchgfx::TypedText(T_CURSPO2DETAIL));
    add(spo2_value);

    topright_image.setPosition(175, 0, 65, 33);
    topright_image.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topright_image);

    topleft_image.setPosition(0, 0, 65, 33);
    topleft_image.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(topleft_image);

    spo2_detail_graph.setPosition(20, 95, 200, 165);
    spo2_detail_graph.setScale(1);
    spo2_detail_graph.setGraphAreaMargin(0, 0, 0, 0);
    spo2_detail_graph.setGraphAreaPadding(0, 0, 0, 0);
    spo2_detail_graph.setGraphRangeY(0, 200);
    spo2_detail_graphLine1Painter.setColor(touchgfx::Color::getColorFromRGB(50, 142, 199));
    spo2_detail_graphLine1.setPainter(spo2_detail_graphLine1Painter);
    spo2_detail_graphLine1.setLineWidth(2);
    spo2_detail_graph.addGraphElement(spo2_detail_graphLine1);


    add(spo2_detail_graph);

    catm1_image.setXY(11, 11);
    catm1_image.setBitmap(touchgfx::Bitmap(BITMAP_LTE_NOTCONNECTED_ID));
    add(catm1_image);

    batteryprogress_container1.setXY(0, 0);
    add(batteryprogress_container1);
}

Spo2DetailViewBase::~Spo2DetailViewBase()
{
    touchgfx::CanvasWidgetRenderer::resetBuffer();
}

void Spo2DetailViewBase::setupScreen()
{
    batteryprogress_container1.initialize();
}

void Spo2DetailViewBase::handleTickEvent()
{
    frameCountUpdateSpo2Interval++;
    if(frameCountUpdateSpo2Interval == TICK_UPDATESPO2_INTERVAL)
    {
        //updateSpo2
        //When every N tick execute C++ code
        //Execute C++ code
        extern uint8_t canDisplayPPG;
        if(!canDisplayPPG) return;
        
        canDisplayPPG = 0;
        
        extern uint16_t ssSpo2;
        
        touchgfx::Unicode::snprintf(spo2_valueBuffer, SPO2_VALUE_SIZE, "%02u", ssSpo2);
        spo2_value.invalidate();
        frameCountUpdateSpo2Interval = 0;
    }
}
