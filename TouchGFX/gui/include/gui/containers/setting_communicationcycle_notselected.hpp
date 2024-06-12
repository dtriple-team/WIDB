#ifndef SETTING_COMMUNICATIONCYCLE_NOTSELECTED_HPP
#define SETTING_COMMUNICATIONCYCLE_NOTSELECTED_HPP

#include <gui_generated/containers/setting_communicationcycle_notselectedBase.hpp>

class setting_communicationcycle_notselected : public setting_communicationcycle_notselectedBase
{
public:
    setting_communicationcycle_notselected();
    virtual ~setting_communicationcycle_notselected() {}

    virtual void initialize();
    virtual void setElements(int16_t item);
protected:
};

#endif // SETTING_COMMUNICATIONCYCLE_NOTSELECTED_HPP
