#ifndef ENGLISHKEYBOARDPRESENTER_HPP
#define ENGLISHKEYBOARDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class englishKeyboardView;

class englishKeyboardPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    englishKeyboardPresenter(englishKeyboardView& v);

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

    virtual ~englishKeyboardPresenter() {}

private:
    englishKeyboardPresenter();

    englishKeyboardView& view;
};

#endif // ENGLISHKEYBOARDPRESENTER_HPP
