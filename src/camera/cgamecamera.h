#ifndef __CGAMECAMERA_H__
#define __CGAMECAMERA_H__

#include "types/rtc_types.h"

namespace Ogre {
    class Camera;
}

namespace rtc {

class CControlManager;

class CGameCamera
{
public:
    virtual ~CGameCamera();
    virtual void update( CControlManager const & controlManager, float const deltaTime ) = 0;
    
    void setActive( bool const active ) { mActive = active; }
    bool const isActive() const { return mActive; }

    TCameraId const getCameraId() const { return mCameraId; }

    Ogre::Camera       & getCamera()       { return *mpCamera; }
    Ogre::Camera const & getCamera() const { return *mpCamera; }

protected:
    // don't allow CGameCamera's to be created explicitly
    explicit CGameCamera( Ogre::Camera * const pCamera, TCameraId const cameraId, bool const active );

private:

    Ogre::Camera * mpCamera;
    TCameraId      mCameraId;
    bool           mActive;
};

} // namespace

#endif //__CGAMECAMERA_H__