#include <gui/containers/setting_communicationcycle_selected.hpp>
#include "texts/TextKeysAndLanguages.hpp"

setting_communicationcycle_selected::setting_communicationcycle_selected()
{

}

void setting_communicationcycle_selected::initialize()
{
    setting_communicationcycle_selectedBase::initialize();
}

void setting_communicationcycle_selected::setElements(int16_t item)
{
	textArea1.invalidate();
	Unicode::snprintf(textArea1Buffer, TEXTAREA1_SIZE, "%d", item);
}
