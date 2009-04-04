#include "csample0framelistener.h"
#include "camera/cgamecamera.h"
#include "viewport/cviewport.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
using namespace Ogre;
//------------------------------------------------------------------------------------------
CSample0FrameListener::CSample0FrameListener(Ogre::SceneManager & sceneManager, RenderWindow & renderWindow)
:CRtcFrameListener( &renderWindow )
,mViewportList( kMaxCameras, kInvalidViewportHandle )
,mRenderManager( sceneManager, renderWindow )
,mInputManager( )
,mNumCameras( 0 )
{
    addCamera(); // create default camera
}
//------------------------------------------------------------------------------------------
void CSample0FrameListener::processUnbufferedKeyInput(FrameEvent const & evt)
{
    mInputManager.processKeyboard( *GetKeyboard() );
}
//------------------------------------------------------------------------------------------
void CSample0FrameListener::processUnbufferedMouseInput(FrameEvent const & evt)
{
    mInputManager.processMouse( *GetMouse() );
}
//------------------------------------------------------------------------------------------
bool const CSample0FrameListener::frameUpdate( FrameEvent const & evt )
{
    float const deltaTime = evt.timeSinceLastFrame;

    mRenderManager.getCameraManager().update( mInputManager.getControlManager(), deltaTime );

    SControllerData const & ctrlData = mInputManager.getControlManager().getControllerData( CControlManager::kControllerId_0);

    bool const keepRendering = ctrlData.buttons & kButton_ApplicationQuit ? false : true;

    if ( keepRendering )
    {
        if ( ctrlData.buttonsDown & kButton_Start)
        {
            addCamera();
        }
        else if ( ctrlData.buttonsDown & kButton_Back )
        {
            removeCamera();
        }

        mRenderManager.update();
    }

    return keepRendering;
}
//------------------------------------------------------------------------------------------
SViewportInfo const CSample0FrameListener::getViewportInfo( int const index, int const numCameras ) const
{
    SViewportInfo viewportInfo(0.0f, 0.0f, 1.0f, 1.0f);

	viewportInfo.left   = static_cast<float>(index % 2) * 0.5f;
	viewportInfo.top    = static_cast<float>(index / 2) * 0.5f;
    viewportInfo.width  = numCameras > 1 ? 0.5f : 1.0f;
    viewportInfo.height = numCameras > 2 ? 0.5f : 1.0f;

    return viewportInfo;
}
//------------------------------------------------------------------------------------------
void CSample0FrameListener::updateActiveViewports()
{
    CViewportManager & viewportMgr = mRenderManager.getViewportManager();

    for( int i=0; i<mNumCameras; ++i )
    {
        if ( CViewport * const pViewport = viewportMgr.getViewport( mViewportList[i] ) )
        {
            pViewport->setViewportInfo( getViewportInfo(i, mNumCameras) );
        }
    }
}
//------------------------------------------------------------------------------------------
void CSample0FrameListener::addCamera()
{
    if( mNumCameras < kMaxCameras )
    {
        CCameraManager   & cameraMgr   = mRenderManager.getCameraManager();
        CViewportManager & viewportMgr = mRenderManager.getViewportManager();

        std::stringstream cameraName("RTCCam");
        cameraName << mNumCameras;

        TCameraId const cameraId = cameraMgr.createCamera( cameraName.str(), CCameraManager::kCameraType_FirstPerson, true );

        if ( cameraId != kInvalidCameraId )
        {
            if ( CGameCamera * pCamera = cameraMgr.getCamera( cameraId ) )
            {
                int index = mNumCameras;
                TViewportHandle const viewportHandle = viewportMgr.createViewport( getViewportInfo(mNumCameras, mNumCameras+1), cameraId, true );

                if ( viewportHandle != kInvalidViewportHandle )
                {
                    mViewportList[mNumCameras] = viewportHandle;
                    ++mNumCameras; // update number of cameras
                    updateActiveViewports();
                }
            }
        }
        else
        {
            // hmm .. camera not found ... 
            // add error message here
        }
    }
}
//------------------------------------------------------------------------------------------
void CSample0FrameListener::removeCamera()
{
    if( mNumCameras > 1 )
    {
        CCameraManager   & cameraMgr   = mRenderManager.getCameraManager();
        CViewportManager & viewportMgr = mRenderManager.getViewportManager();

        TViewportHandle const viewportHandle = mViewportList[mNumCameras-1];

        if ( CViewport * const pViewport = viewportMgr.getViewport( viewportHandle ) )
        {
            cameraMgr.removeCamera( pViewport->getCameraId() ); // get rid of the camera

            viewportMgr.deleteViewport( viewportHandle );
            --mNumCameras; // update number of cameras
            updateActiveViewports(); // update viewport dimensions
        }
    }
}