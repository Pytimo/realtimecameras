#ifndef __CFIRSTPERSONCAMERA_H__
#define __CFIRSTPERSONCAMERA_H__

#include "camera/cgamecamera.h"

namespace rtc {

class CFirstPersonCamera: public CGameCamera
{
public:

    explicit CFirstPersonCamera( Ogre::Camera * const pCamera, TCameraId const cameraId, bool const active );
    virtual ~CFirstPersonCamera();

    virtual void update( CControlManager const & controlManager, float const deltaTime );

private:

    float mWalkSpeed;
    float mTurnSpeed;
};

} // namespace

#endif //__CFIRSTPERSONCAMERA_H__