#ifndef SOUNDNHAPTICSSETTINGPRESENTER_HPP
#define SOUNDNHAPTICSSETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <touchgfx/Callback.hpp>

using namespace touchgfx;

class soundnhapticsSettingView;

class soundnhapticsSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    soundnhapticsSettingPresenter(soundnhapticsSettingView& v);

    virtual void activate();
    virtual void deactivate();
    virtual void notifySwipeRight();

    void updateToggleButton1State(bool state); //test
    bool getToggleButton1State() const; //test
    void onToggleButton1StateChanged(bool state);

    void updateToggleButton2State(bool state); //test
    bool getToggleButton2State() const; //test
    void onToggleButton2StateChanged(bool state);

    virtual ~soundnhapticsSettingPresenter() {}

private:
    soundnhapticsSettingPresenter();

    soundnhapticsSettingView& view;
};

#endif // SOUNDNHAPTICSSETTINGPRESENTER_HPP
