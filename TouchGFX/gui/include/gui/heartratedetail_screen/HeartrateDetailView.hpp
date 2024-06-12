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
protected:
};

#endif // HEARTRATEDETAILVIEW_HPP
