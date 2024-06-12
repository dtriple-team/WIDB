#ifndef FRONTENDAPPLICATION_HPP
#define FRONTENDAPPLICATION_HPP

#include <mvp/View.hpp> //rkdalfks
#include <mvp/Presenter.hpp> //rkdalfks
#include <touchgfx/hal/HAL.hpp> //rkdalfks
#include <touchgfx/Application.hpp> //rkdalfks
#include <gui_generated/common/FrontendApplicationBase.hpp>
#include <texts/TextKeysAndLanguages.hpp> //rkdalfks

class FrontendHeap;

using namespace touchgfx;

class FrontendApplication : public FrontendApplicationBase
{
public:
    FrontendApplication(Model& m, FrontendHeap& heap);
    virtual ~FrontendApplication() { }

    virtual void handleTickEvent();
private:
};

#endif // FRONTENDAPPLICATION_HPP
