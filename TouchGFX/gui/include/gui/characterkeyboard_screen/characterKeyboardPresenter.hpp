#ifndef CHARACTERKEYBOARDPRESENTER_HPP
#define CHARACTERKEYBOARDPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class characterKeyboardView;

class characterKeyboardPresenter : public touchgfx::Presenter, public ModelListener
{
public:
    characterKeyboardPresenter(characterKeyboardView& v);

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

    virtual ~characterKeyboardPresenter() {}

private:
    characterKeyboardPresenter();

    characterKeyboardView& view;
};

#endif // CHARACTERKEYBOARDPRESENTER_HPP
