#ifndef SOS_ALERTVIEW_HPP
#define SOS_ALERTVIEW_HPP

#include <gui_generated/sos_alert_screen/sos_alertViewBase.hpp>
#include <gui/sos_alert_screen/sos_alertPresenter.hpp>

class sos_alertView : public sos_alertViewBase
{
public:
    sos_alertView();
    virtual ~sos_alertView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
protected:
};

#endif // SOS_ALERTVIEW_HPP
