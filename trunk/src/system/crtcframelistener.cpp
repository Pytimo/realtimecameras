#include "system/crtcframelistener.h"

//------------------------------------------------------------------------------------------
using namespace OIS;
//------------------------------------------------------------------------------------------

CRtcFrameListener::CRtcFrameListener( RenderWindow * pWindow,
                                      EKeyboardMode const keyboardMode,
                                      EMouseMode const mouseMode, 
                                      EJoystickMode const joystickMode )
: mpWindow      ( pWindow )
, mpDebugOverlay( OverlayManager::getSingleton().getByName("Core/DebugOverlay") )
, mpInputManager( NULL )
, mpMouse       ( NULL )
, mpKeyboard    ( NULL )
, mpJoystick    ( NULL )
{
	LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	pWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mpInputManager = InputManager::createInputSystem( pl );

    //Create all devices (We only catch joystick exceptions here, as, most people have Key/Mouse)
    mpKeyboard = static_cast<Keyboard*>(mpInputManager->createInputObject( OISKeyboard, keyboardMode==kKeyboardMode_Buffered ));
    mpMouse    = static_cast<Mouse*>(mpInputManager->createInputObject( OISMouse, mouseMode==kMouseMode_Buffered ));

    try
    {
        mpJoystick = static_cast<JoyStick*>(mpInputManager->createInputObject( OISJoyStick, joystickMode==kJoystickMode_Buffered ));
    }

    catch(...)
    {
        mpJoystick = NULL;
    }

    //Set initial mouse clipping size
    windowResized(pWindow);

    //Register as a Window listener
    WindowEventUtilities::addWindowEventListener(pWindow, this);
}

//------------------------------------------------------------------------------------------

CRtcFrameListener::~CRtcFrameListener()
{
	//Remove ourself as a Window listener
	WindowEventUtilities::removeWindowEventListener(mpWindow, this);
	windowClosed(mpWindow);
}

//------------------------------------------------------------------------------------------

void CRtcFrameListener::windowClosed(RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mpWindow )
    {
        if( mpInputManager )
        {
            mpInputManager->destroyInputObject( mpMouse );
            mpInputManager->destroyInputObject( mpKeyboard );
            mpInputManager->destroyInputObject( mpJoystick );

            OIS::InputManager::destroyInputSystem(mpInputManager);
            mpInputManager = NULL;
        }
    }
}

//------------------------------------------------------------------------------------------

void CRtcFrameListener::windowResized(RenderWindow* rw)
{
	unsigned int width, height, depth;
	int left, top;
	
    rw->getMetrics(width, height, depth, left, top);

	OIS::MouseState const & mouseState = mpMouse->getMouseState();
	mouseState.width = width;
	mouseState.height = height;
}

//------------------------------------------------------------------------------------------

bool CRtcFrameListener::frameRenderingQueued(FrameEvent const & evt)
{
    if( mpWindow->isClosed() )
    {
        return false;
    }

    //Need to capture/update each device
    mpKeyboard->capture();
    mpMouse->capture();

    bool joystickBuffered = true;

    if( mpJoystick )
    {
        mpJoystick->capture();
        joystickBuffered = mpJoystick->buffered();
    }

    //Check if one of the devices is not buffered
    if( !mpMouse->buffered() || !mpKeyboard->buffered() )
    {
    }

    //Check to see which device is not buffered, and handle it
    if( !mpKeyboard->buffered() )
    {
	    processUnbufferedKeyInput(evt);
    }

    if( !mpMouse->buffered() )
    {
	    processUnbufferedMouseInput(evt);
    }

    if( !mpMouse->buffered() || !mpKeyboard->buffered() || !joystickBuffered )
    {
        // returns true to continue, false to stop
	    return frameUpdate( evt );
    }

	return true; // continue rendering
}

//------------------------------------------------------------------------------------------

void CRtcFrameListener::showDebugOverlay( bool const show )
{
    if ( mpDebugOverlay )
    {
        if ( show )
        {
            mpDebugOverlay->show();
        }
        else
        {
            mpDebugOverlay->hide();
        }
    }
}

//------------------------------------------------------------------------------------------