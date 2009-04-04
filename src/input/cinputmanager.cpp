#include "input/cinputmanager.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
namespace
{
    struct SButtonMap
    {
        explicit SButtonMap( OIS::KeyCode const _keyCode, unsigned int const _buttonMask )
            :keyCode( _keyCode )
            ,buttonMask( _buttonMask )
        {
        }

        OIS::KeyCode const keyCode;
        unsigned int const buttonMask;
    };
    //------------------------------------------------------------------------------------------
    // This button map definition can be defined externally (i.e. read from a file), for now we'll 
    // define it in this manner.
    SButtonMap const skButtonMap[] =
    {
         SButtonMap( OIS::KC_UP,      kButton_Up )
        ,SButtonMap( OIS::KC_DOWN,    kButton_Down )
        ,SButtonMap( OIS::KC_LEFT,    kButton_Left )
        ,SButtonMap( OIS::KC_RIGHT,   kButton_Right )

        ,SButtonMap( OIS::KC_NUMPAD8, kButton_Up )
        ,SButtonMap( OIS::KC_NUMPAD2, kButton_Down )
        ,SButtonMap( OIS::KC_NUMPAD4, kButton_Left )
        ,SButtonMap( OIS::KC_NUMPAD6, kButton_Right )

        ,SButtonMap( OIS::KC_RETURN,  kButton_Start )
        ,SButtonMap( OIS::KC_BACK,    kButton_Back )

        ,SButtonMap( OIS::KC_ESCAPE,  kButton_ApplicationQuit )
    };
    int const skKeyboardMapSize = sizeof(skButtonMap)/sizeof(skButtonMap[0]);
}
//------------------------------------------------------------------------------------------
CInputManager::CInputManager()
:mControlManager()
,mRawData()
{
}
//------------------------------------------------------------------------------------------
void CInputManager::buildInput( CControlManager::EControllerId const controllerId )
{
    SControllerData & controller = mControlManager.getControllerData(controllerId);

    unsigned int const lastButtons = controller.buttons;
    unsigned int const buttons     = mRawData.buttons; // OR in other data

    controller.pointerX    = mRawData.pointerX;
    controller.pointerY    = mRawData.pointerY;
    controller.buttons     = buttons;
    controller.buttonsDown = BUTTONS_DOWN(lastButtons, buttons);
    controller.buttonsUp   = BUTTONS_UP(lastButtons, buttons);
}
//------------------------------------------------------------------------------------------
void CInputManager::processKeyboard( OIS::Keyboard & keyboard )
{
    mRawData.buttons = 0;

    for (int i=0; i<skKeyboardMapSize; ++i)
    {
        SButtonMap const & buttonMap = skButtonMap[i];

        if( keyboard.isKeyDown(buttonMap.keyCode) )
        {
            mRawData.buttons |= buttonMap.buttonMask;
        }
    }

    // keyboard is always mapped to kControllerId_0
    buildInput( CControlManager::kControllerId_0 );
}
//------------------------------------------------------------------------------------------
void CInputManager::processMouse( OIS::Mouse const & mouse )
{
    OIS::MouseState const & mouseState = mouse.getMouseState();

    mRawData.pointerX.absolute = mouseState.X.abs;
    mRawData.pointerY.absolute = mouseState.Y.abs;

    mRawData.pointerX.relative = mouseState.X.rel;
    mRawData.pointerY.relative = mouseState.Y.rel;
}
//------------------------------------------------------------------------------------------