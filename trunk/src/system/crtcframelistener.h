#ifndef __CRTCFRAMELISTENER_H__
#define __CRTCFRAMELISTENER_H__

#include "Ogre.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

class CRtcFrameListener: public FrameListener, public WindowEventListener
{
public:
    enum EKeyboardMode
    {
        kKeyboardMode_NonBuffered,
        kKeyboardMode_Buffered
    };

    enum EMouseMode
    {
        kMouseMode_NonBuffered,
        kMouseMode_Buffered
    };

    enum EJoystickMode
    {
        kJoystickMode_NonBuffered,
        kJoystickMode_Buffered
    };

    explicit CRtcFrameListener( RenderWindow * pWindow, 
                                EKeyboardMode const keyboardMode = kKeyboardMode_NonBuffered,
                                EMouseMode const mouseMode = kMouseMode_NonBuffered,
                                EJoystickMode const joystickMode = kJoystickMode_NonBuffered );
    virtual ~CRtcFrameListener();

    virtual void windowClosed(RenderWindow* rw);
	virtual void windowResized(RenderWindow* rw);

    virtual bool frameRenderingQueued(FrameEvent const & evt);

    virtual void processUnbufferedKeyInput  (FrameEvent const & evt) = 0;
	virtual void processUnbufferedMouseInput(FrameEvent const & evt) = 0;

    virtual bool const frameUpdate(FrameEvent const & evt) = 0;

    void showDebugOverlay( bool const show );

protected:

    OIS::Mouse    *       GetMouse   ()       { return mpMouse; }
    OIS::Mouse    * const GetMouse   () const { return mpMouse; }
    OIS::Keyboard *       GetKeyboard()       { return mpKeyboard; }
    OIS::Keyboard * const GetKeyboard() const { return mpKeyboard; }

private:

    RenderWindow      * mpWindow;
    Overlay           * mpDebugOverlay;
	OIS::InputManager * mpInputManager;
	OIS::Mouse        * mpMouse;
	OIS::Keyboard     * mpKeyboard;
    OIS::JoyStick     * mpJoystick;
};

#endif // __CRTCFRAMELISTENER_H__