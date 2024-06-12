#ifndef SETTING_COMMUNICATIONCYCLE_SELECTED_HPP
#define SETTING_COMMUNICATIONCYCLE_SELECTED_HPP

#include <gui_generated/containers/setting_communicationcycle_selectedBase.hpp>

class setting_communicationcycle_selected : public setting_communicationcycle_selectedBase
{
public:
    setting_communicationcycle_selected();
    virtual ~setting_communicationcycle_selected() {}

    virtual void initialize();
    virtual void setElements(int16_t item);
protected:
};

#endif // SETTING_COMMUNICATIONCYCLE_SELECTED_HPP
