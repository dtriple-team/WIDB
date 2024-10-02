#ifndef BATTERYPROGRESS_CONTAINER_HPP
#define BATTERYPROGRESS_CONTAINER_HPP

#include <gui_generated/containers/batteryprogress_containerBase.hpp>

class batteryprogress_container : public batteryprogress_containerBase
{
public:
    batteryprogress_container();
    virtual ~batteryprogress_container() {}

    virtual void initialize();
protected:
};

#endif // BATTERYPROGRESS_CONTAINER_HPP
