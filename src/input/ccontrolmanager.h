#ifndef __CCONTROLMANAGER_H__
#define __CCONTROLMANAGER_H__

#include "input/scontrollerdata.h"

namespace OIS {
    class Keyboard;
}

namespace rtc {

class CControlManager
{
public:

    enum EControllerId
    {
        kControllerId_0,
        kControllerId_1,
    };

    CControlManager();

    SControllerData & getControllerData(int const index)
    { 
        return mControllerData[index];
    }

    SControllerData const & getControllerData(int const index) const
    { 
        return mControllerData[index];
    }

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CControlManager )

    enum
    {
        kMaxControllers = 2
    };

    SControllerData mControllerData[kMaxControllers];
};

} // namespace

#endif // __CCONTROLMANAGER_H__