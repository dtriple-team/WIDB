#ifndef SETTING_SCREENONTIME_NOTSELECTED_HPP
#define SETTING_SCREENONTIME_NOTSELECTED_HPP

#include <gui_generated/containers/setting_screenontime_notselectedBase.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class setting_screenontime_notselected : public setting_screenontime_notselectedBase
{
public:
    setting_screenontime_notselected();
    virtual ~setting_screenontime_notselected() {}

    virtual void initialize();
    virtual void setElements(int16_t item);

protected:

private:
};

#endif // SETTING_SCREENONTIME_NOTSELECTED_HPP
