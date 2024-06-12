#ifndef FALLDETECTEDVIEW_HPP
#define FALLDETECTEDVIEW_HPP

#include <gui_generated/falldetected_screen/fallDetectedViewBase.hpp>
#include <gui/falldetected_screen/fallDetectedPresenter.hpp>

class fallDetectedView : public fallDetectedViewBase
{
public:
    fallDetectedView();
    virtual ~fallDetectedView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // FALLDETECTEDVIEW_HPP
