#ifndef TEMPHOMEVIEW_HPP
#define TEMPHOMEVIEW_HPP

#include <gui_generated/temphome_screen/tempHomeViewBase.hpp>
#include <gui/temphome_screen/tempHomePresenter.hpp>

class tempHomeView : public tempHomeViewBase
{
public:
    tempHomeView();
    virtual ~tempHomeView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // TEMPHOMEVIEW_HPP
