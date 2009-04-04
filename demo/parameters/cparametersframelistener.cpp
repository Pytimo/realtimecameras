#include "cparametersframelistener.h"
#include "camera/cgamecamera.h"
#include "viewport/cviewport.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
using namespace Ogre;
//------------------------------------------------------------------------------------------
namespace
{
    char const * const skFOVElement         = "RTC/Parameters/FOV";
    char const * const skAspectRatioElement = "RTC/Parameters/Aspect";

    Real const skMinFOV = 45.0f;
    Real const skMaxFOV = 90.0f;
    Real const skFOVChangeSpeed = 5.0f;
    Real const skMinAspectRatio = 0.5f;
    Real const skMaxAspectRatio = 2.0f;

    Real const get_key_press( OIS::Keyboard & keyboard, OIS::KeyCode const decrKey, OIS::KeyCode const incrKey )
    {
        return keyboard.isKeyDown(decrKey) ? -1.0f : keyboard.isKeyDown(incrKey) ? 1.0f : 0.0f;
    }
}
//------------------------------------------------------------------------------------------
CParametersFrameListener::CParametersFrameListener(Ogre::SceneManager & sceneManager, RenderWindow & renderWindow)
:CRtcFrameListener( &renderWindow )
,mRenderManager( sceneManager, renderWindow )
,mInputManager( )
,mParametersOverlay( OverlayManager::getSingleton().getByName("RTC/Parameters") )
,mFOV( 60.0f )
,mAspectRatio( 0.0f )
,mCameraId( 0 )
{
    mParametersOverlay->show();
    createCamera(); // create default camera
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::processUnbufferedKeyInput(FrameEvent const & evt)
{
    mInputManager.processKeyboard( *GetKeyboard() );
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::processUnbufferedMouseInput(FrameEvent const & evt)
{
    mInputManager.processMouse( *GetMouse() );
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::updateOverlay(  Ogre::Camera & ogreCamera )
{
    OverlayManager::getSingleton().getOverlayElement(skFOVElement)->setCaption(String("[Q/W] FOV: ")+StringConverter::toString(ogreCamera.getFOVy().valueDegrees()));
    OverlayManager::getSingleton().getOverlayElement(skAspectRatioElement)->setCaption(String("[A/S] Aspect: ")+StringConverter::toString(ogreCamera.getAspectRatio()));
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::updateFOV( Ogre::Camera & ogreCamera, Real const deltaTime )
{
    Real const leftRight = get_key_press( *GetKeyboard(), OIS::KC_Q, OIS::KC_W );

    if( leftRight != 0.0f )
    {
        Real fovy = ogreCamera.getFOVy().valueDegrees() + (leftRight*skFOVChangeSpeed*deltaTime);

        if (fovy > skMaxFOV)
        {
            fovy = skMaxFOV;
        }
        else if (fovy < skMinFOV)
        {
            fovy = skMinFOV;
        }

        ogreCamera.setFOVy( Ogre::Radian(Ogre::Degree(fovy).valueRadians()) );
        OverlayManager::getSingleton().getOverlayElement(skFOVElement)->setCaption(String("[Q/W] FOV: ")+StringConverter::toString( fovy ));
    }
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::updateAspectRatio( Ogre::Camera & ogreCamera, Real const deltaTime )
{
    Real const leftRight = get_key_press( *GetKeyboard(), OIS::KC_A, OIS::KC_S );

    if( leftRight != 0.0f )
    {
        Real aspect = ogreCamera.getAspectRatio() + (deltaTime*leftRight);

        if (aspect > skMaxAspectRatio)
        {
            aspect = skMaxAspectRatio;
        }
        else if (aspect < skMinAspectRatio)
        {
            aspect = skMinAspectRatio;
        }

        ogreCamera.setAspectRatio( aspect );
        OverlayManager::getSingleton().getOverlayElement(skAspectRatioElement)->setCaption(String("[A/S] Aspect: ")+StringConverter::toString(ogreCamera.getAspectRatio()));
    }
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::updateParameters( Real const deltaTime )
{
    if ( rtc::CGameCamera * const pGameCamera = mRenderManager.getCameraManager().getCamera( mCameraId ) )
    {
        Ogre::Camera & ogreCamera = pGameCamera->getCamera();

        updateFOV( ogreCamera, deltaTime );
        updateAspectRatio( ogreCamera, deltaTime );
    }
}
//------------------------------------------------------------------------------------------
bool const CParametersFrameListener::frameUpdate( FrameEvent const & evt )
{
    Real const deltaTime = evt.timeSinceLastFrame;

    mRenderManager.getCameraManager().update( mInputManager.getControlManager(), deltaTime );

    SControllerData const & ctrlData = mInputManager.getControlManager().getControllerData( CControlManager::kControllerId_0 );

    bool const keepRendering = ctrlData.buttons & kButton_ApplicationQuit ? false : true;

    if ( keepRendering )
    {
        updateParameters( deltaTime );
        mRenderManager.update();
    }

    return keepRendering;
}
//------------------------------------------------------------------------------------------
void CParametersFrameListener::createCamera()
{
    CCameraManager   & cameraMgr   = mRenderManager.getCameraManager();
    CViewportManager & viewportMgr = mRenderManager.getViewportManager();

    std::stringstream const cameraName("RTC_Camera");

    mCameraId = cameraMgr.createCamera( cameraName.str(), CCameraManager::kCameraType_FirstPerson, true );

    if ( mCameraId != kInvalidCameraId )
    {
        if ( CGameCamera * pCamera = cameraMgr.getCamera( mCameraId ) )
        {
            viewportMgr.createViewport( SViewportInfo(0.0f, 0.0f, 1.0f, 1.0f), mCameraId, true );
            updateOverlay( pCamera->getCamera() );
        }
    }
}
//------------------------------------------------------------------------------------------