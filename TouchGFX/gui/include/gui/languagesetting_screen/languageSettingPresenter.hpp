#ifndef LANGUAGESETTINGPRESENTER_HPP
#define LANGUAGESETTINGPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>
#include <texts/TextKeysAndLanguages.hpp>

using namespace touchgfx;

class languageSettingView;

class languageSettingPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    languageSettingPresenter(languageSettingView& v);

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

    virtual void notifySwipeRight();

    virtual ~languageSettingPresenter() {}

private:
    languageSettingPresenter();

    languageSettingView& view;
};

#endif // LANGUAGESETTINGPRESENTER_HPP
