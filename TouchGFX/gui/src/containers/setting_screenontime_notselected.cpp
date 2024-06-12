#include <gui/containers/setting_screenontime_notselected.hpp>
#include "texts/TextKeysAndLanguages.hpp"

setting_screenontime_notselected::setting_screenontime_notselected()
{

}

void setting_screenontime_notselected::initialize()
{
    setting_screenontime_notselectedBase::initialize();
}

void setting_screenontime_notselected::setElements(int16_t item)
{
	textArea1.invalidate();
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", item);
}
