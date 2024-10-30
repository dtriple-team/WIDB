#ifndef HEARTRATEDETAILVIEW_HPP
#define HEARTRATEDETAILVIEW_HPP

#include <gui_generated/heartratedetail_screen/HeartrateDetailViewBase.hpp>
#include <gui/heartratedetail_screen/HeartrateDetailPresenter.hpp>

class HeartrateDetailView : public HeartrateDetailViewBase
{
public:
    HeartrateDetailView();
    virtual ~HeartrateDetailView() {}
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

#endif // HEARTRATEDETAILVIEW_HPP
