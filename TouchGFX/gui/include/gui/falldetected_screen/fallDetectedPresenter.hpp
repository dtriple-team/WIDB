#ifndef FALLDETECTEDPRESENTER_HPP
#define FALLDETECTEDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class fallDetectedView;

class fallDetectedPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    fallDetectedPresenter(fallDetectedView& v);

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

    virtual ~fallDetectedPresenter() {}

private:
    fallDetectedPresenter();

    fallDetectedView& view;
};

#endif // FALLDETECTEDPRESENTER_HPP
