#ifndef SPO2DETAILVIEW_HPP
#define SPO2DETAILVIEW_HPP

#include <gui_generated/spo2detail_screen/Spo2DetailViewBase.hpp>
#include <gui/spo2detail_screen/Spo2DetailPresenter.hpp>

class Spo2DetailView : public Spo2DetailViewBase
{
public:
    Spo2DetailView();
    virtual ~Spo2DetailView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
#if defined(gui_simulation)
    virtual void handleGestureEvent(const GestureEvent& evt); //rkdalfks
#endif

    void handleSwipeRight(); //rkdalfks
#if !defined(gui_simulation)
    virtual void handleTickEvent();
#endif
protected:

private:
    int initialX;
    int initialY;
};

#endif // SPO2DETAILVIEW_HPP
