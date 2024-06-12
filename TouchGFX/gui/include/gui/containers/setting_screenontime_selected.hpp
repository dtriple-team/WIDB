#ifndef SETTING_SCREENONTIME_SELECTED_HPP
#define SETTING_SCREENONTIME_SELECTED_HPP

#include <gui_generated/containers/setting_screenontime_selectedBase.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <texts/TextKeysAndLanguages.hpp>

class setting_screenontime_selected : public setting_screenontime_selectedBase
{
public:
    setting_screenontime_selected();
    virtual ~setting_screenontime_selected() {}

    virtual void initialize();
    virtual void setElements(int16_t item);

protected:

private:
};

#endif // SETTING_SCREENONTIME_SELECTED_HPP
