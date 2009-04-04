#ifndef __CVIEWPORT_H__
#define __CVIEWPORT_H__

#include "types/rtc_types.h"

namespace Ogre {
    class Viewport;
}

namespace rtc {

class CViewport
{
public:

    explicit CViewport( TViewportHandle const handle, SViewportInfo const & viewportInfo, TCameraId const cameraId, bool const active );
    void setActive( bool const active ) { mIsActive = active; }
    void setCameraId( TCameraId const cameraId );
    void setViewportInfo( SViewportInfo const & viewportInfo );

    // meant only to be used by CRenderManager
    void setOgreViewport( Ogre::Viewport * const pViewport );

    bool            const   isActive() const { return mIsActive; }
    TViewportHandle const   getHandle() const { return mHandle; }
    TCameraId       const   getCameraId() const { return mCameraId; }
    SViewportInfo   const & getViewportInfo() const { return mViewportInfo; }

    bool const checkUpdate()
    { 
        // calling, clears variable (should be called once a frame)
        bool const needsUpdate = mNeedsUpdate;
        mNeedsUpdate = false;
        return needsUpdate;
    }

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CViewport )

    SViewportInfo     mViewportInfo;
    TViewportHandle   mHandle;
    TCameraId         mCameraId;
    Ogre::Viewport   *mpOgreViewport;
    bool              mIsActive;
    bool              mNeedsUpdate;
};

} // namespace

#endif // __CVIEWPORT_H__