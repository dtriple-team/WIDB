#ifndef SOS_ALERTPRESENTER_HPP
#define SOS_ALERTPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class sos_alertView;

class sos_alertPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    sos_alertPresenter(sos_alertView& v);

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

    virtual ~sos_alertPresenter() {}

private:
    sos_alertPresenter();

    sos_alertView& view;
};

#endif // SOS_ALERTPRESENTER_HPP
