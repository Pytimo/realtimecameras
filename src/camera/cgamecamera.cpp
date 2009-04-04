#include "camera/cgamecamera.h"
#include "ogrecamera.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
CGameCamera::CGameCamera( Ogre::Camera * const pCamera, TCameraId const cameraId, bool const active )
:mpCamera ( pCamera )
,mCameraId( cameraId )
,mActive  ( active )
{
}
//------------------------------------------------------------------------------------------
CGameCamera::~CGameCamera()
{
    // no need to free camera (destroyed by scene manager)
}