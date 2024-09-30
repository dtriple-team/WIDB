#ifndef HOMESCREENWITHBIODATAPRESENTER_HPP
#define HOMESCREENWITHBIODATAPRESENTER_HPP

#include <mvp/Presenter.hpp>
#include <gui/model/ModelListener.hpp>

using namespace touchgfx;

class HomeScreenWithBiodataView;

class HomeScreenWithBiodataPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HomeScreenWithBiodataPresenter(HomeScreenWithBiodataView& v);

    virtual void activate();
    virtual void deactivate();
    virtual void notifySwipeDown();

    virtual ~HomeScreenWithBiodataPresenter() {};

private:
    HomeScreenWithBiodataPresenter();

    HomeScreenWithBiodataView& view;
};

#endif // HOMESCREENWITHBIODATAPRESENTER_HPP
