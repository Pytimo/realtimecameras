#include "camera/cfirstpersoncamera.h"
#include "input/ccontrolmanager.h"
#include "ogrecamera.h"
#include "ogrevector3.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
using namespace Ogre;
//------------------------------------------------------------------------------------------
CFirstPersonCamera::CFirstPersonCamera( Camera * const pCamera, TCameraId const cameraId, bool const active )
:CGameCamera( pCamera, cameraId, active )
,mWalkSpeed(100.0f)
,mTurnSpeed(10.0f)
{
    Camera & camera = getCamera();

    Vector3 const forward = camera.getDirection();
    Vector3 const position = Vector3(0, 50, 500);

    camera.setPosition( position );
    camera.lookAt( position+forward );
    camera.setNearClipDistance(5.0f);
}
//------------------------------------------------------------------------------------------
CFirstPersonCamera::~CFirstPersonCamera()
{
}
//------------------------------------------------------------------------------------------
void CFirstPersonCamera::update( CControlManager const & controlManager, float const deltaTime )
{
    Camera & camera = getCamera();

    Vector3 position = camera.getPosition();
    Vector3 forward = camera.getDirection();
    Vector3 right = camera.getRight();

    float const step = mWalkSpeed*deltaTime;

    SControllerData const & controllerData = controlManager.getControllerData(CControlManager::kControllerId_0);

    if ( controllerData.buttons & kButton_Up )
    {
        position += forward*step;
    }
    else if ( controllerData.buttons & kButton_Down )
    {
        position -= forward*step;
    }

    if ( controllerData.buttons & kButton_Left )
    {
        position -= right*step;
    }
    else if ( controllerData.buttons & kButton_Right )
    {
        position += right*step;
    }

    float const turnStep = mTurnSpeed*deltaTime;

    camera.yaw( Degree(-controllerData.pointerX.relative * turnStep) );
    camera.pitch( Degree(-controllerData.pointerY.relative * turnStep) );
    camera.setPosition(position);
}
//------------------------------------------------------------------------------------------
