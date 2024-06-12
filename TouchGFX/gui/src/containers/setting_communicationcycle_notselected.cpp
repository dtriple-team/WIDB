#include <gui/containers/setting_communicationcycle_notselected.hpp>
#include "texts/TextKeysAndLanguages.hpp"

setting_communicationcycle_notselected::setting_communicationcycle_notselected()
{

}

void setting_communicationcycle_notselected::initialize()
{
    setting_communicationcycle_notselectedBase::initialize();
}

void setting_communicationcycle_notselected::setElements(int16_t item)
{
	textArea1.invalidate();
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", item);
}

