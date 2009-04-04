#include "input/ccontrolmanager.h"
#include <memory.h>

//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
CControlManager::CControlManager()
{
    memset( mControllerData, 0, sizeof(mControllerData) );
}
//------------------------------------------------------------------------------------------
