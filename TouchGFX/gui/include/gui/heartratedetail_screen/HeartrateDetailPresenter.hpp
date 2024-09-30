#ifndef HEARTRATEDETAILPRESENTER_HPP
#define HEARTRATEDETAILPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeartrateDetailView;

class HeartrateDetailPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HeartrateDetailPresenter(HeartrateDetailView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual void notifySwipeRight(); //rkdalfks

    virtual ~HeartrateDetailPresenter() {}

private:
    HeartrateDetailPresenter();

    HeartrateDetailView& view;
};

#endif // HEARTRATEDETAILPRESENTER_HPP
