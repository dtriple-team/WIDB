#ifndef LTE_STATUS_CONTAINER_HPP
#define LTE_STATUS_CONTAINER_HPP

#include <gui_generated/containers/lte_status_containerBase.hpp>

class lte_status_container : public lte_status_containerBase
{
public:
    lte_status_container();
    virtual ~lte_status_container() {}

    virtual void initialize();
protected:
};

#endif // LTE_STATUS_CONTAINER_HPP
