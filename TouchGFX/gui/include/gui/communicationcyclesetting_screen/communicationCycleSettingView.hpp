#ifndef COMMUNICATIONCYCLESETTINGVIEW_HPP
#define COMMUNICATIONCYCLESETTINGVIEW_HPP

#include <gui_generated/communicationcyclesetting_screen/communicationCycleSettingViewBase.hpp>
#include <gui/communicationcyclesetting_screen/communicationCycleSettingPresenter.hpp>

class communicationCycleSettingView : public communicationCycleSettingViewBase
{
public:
    communicationCycleSettingView();
    virtual ~communicationCycleSettingView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleGestureEvent(const GestureEvent& evt);

    void handleSwipeRight();

    virtual void scrollWheel1UpdateItem(setting_communicationcycle_notselected& item, int16_t itemIndex);
    virtual void scrollWheel1UpdateCenterItem(setting_communicationcycle_selected& item, int16_t itemIndex);
protected:
    Callback<communicationCycleSettingView, int16_t>scrollWheel1AnimateToCallback;
    void scrollWheel1AnimateToHandler(int16_t item);

private:
    int initialX;
    int initialY;
};

#endif // COMMUNICATIONCYCLESETTINGVIEW_HPP
