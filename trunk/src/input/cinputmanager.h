#ifndef __CINPUTMANAGER_H__
#define __CINPUTMANAGER_H__

#include "system/crtcframelistener.h"
#include "input/ccontrolmanager.h"

namespace OIS
{
    class Mouse;
    class Keyboard;
}

namespace rtc {

class CInputManager
{
public:
    explicit CInputManager();

    void processKeyboard( OIS::Keyboard & keyboard );
    void processMouse   ( OIS::Mouse const & mouse );

    CControlManager const & getControlManager() const { return mControlManager; }

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CInputManager )

    void buildInput( CControlManager::EControllerId const controllerId );

    CControlManager mControlManager;
    SControllerData mRawData;
};

} // namespace


#endif // __CINPUTMANAGER_H__