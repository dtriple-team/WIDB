#include <gui/containers/setting_screenontime_selected.hpp>
#include "texts/TextKeysAndLanguages.hpp"

setting_screenontime_selected::setting_screenontime_selected()
{

}

void setting_screenontime_selected::initialize()
{
    setting_screenontime_selectedBase::initialize();
}

void setting_screenontime_selected::setElements(int16_t item)
{
	textArea1.invalidate();
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", item);
}
