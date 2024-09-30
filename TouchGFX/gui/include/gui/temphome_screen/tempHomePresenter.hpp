#ifndef TEMPHOMEPRESENTER_HPP
#define TEMPHOMEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class tempHomeView;

class tempHomePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    tempHomePresenter(tempHomeView& v);

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

    virtual ~tempHomePresenter() {}

private:
    tempHomePresenter();

    tempHomeView& view;
};

#endif // TEMPHOMEPRESENTER_HPP
