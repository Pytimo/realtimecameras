#include "viewport/cviewport.h"
#include "ogreviewport.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
CViewport::CViewport( TViewportHandle const handle, SViewportInfo const & viewportInfo, TCameraId const cameraId, bool const active )
:mViewportInfo( viewportInfo )
,mHandle( handle )
,mCameraId( cameraId )
,mpOgreViewport( NULL )
,mIsActive( active )
,mNeedsUpdate(false)
{
}
//------------------------------------------------------------------------------------------
void CViewport::setCameraId( TCameraId const cameraId )
{
    mCameraId = cameraId;
}
//------------------------------------------------------------------------------------------
// meant only to be used by CRenderManager
void CViewport::setOgreViewport( Ogre::Viewport * const pViewport )
{ 
    mpOgreViewport = pViewport;
}
//------------------------------------------------------------------------------------------
void CViewport::setViewportInfo( SViewportInfo const & viewportInfo )
{
    mViewportInfo = viewportInfo;
    if (mpOgreViewport != NULL)
    {
        mpOgreViewport->setDimensions( viewportInfo.left, viewportInfo.top, viewportInfo.width, viewportInfo.height );
        mNeedsUpdate = true;
    }
}
//------------------------------------------------------------------------------------------
