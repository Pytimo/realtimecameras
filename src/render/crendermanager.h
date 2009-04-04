#ifndef __CRENDERMANAGER_H__
#define __CRENDERMANAGER_H__

#include "types/rtc_types.h"
#include "camera/ccameramanager.h"
#include "viewport/cviewportmanager.h"
#include <map>

namespace Ogre {
    class SceneManager;
    class RenderWindow;
    class Viewport;
    class Camera;
}

namespace rtc {

class CCameraManager;
class CViewportManager;
class CViewport;

class CRenderManager
{
public:

    explicit CRenderManager( Ogre::SceneManager & sceneManager, Ogre::RenderWindow & renderWindow  );
    ~CRenderManager();

    void update();

    CCameraManager       & getCameraManager()       { return mCameraManager; }
    CCameraManager const & getCameraManager() const { return mCameraManager; }

    CViewportManager       & getViewportManager()       { return mViewportManager; }
    CViewportManager const & getViewportManager() const { return mViewportManager; }

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CRenderManager )

    typedef std::map<TViewportHandle, Ogre::Viewport*> TViewportMap;

    Ogre::Viewport * getRenderViewport(TViewportHandle const handle) const;

    void removeDeletedViewports();
    void updateRenderWindowList( CViewport & viewport );
    void removeAllRenderWindows();

    CCameraManager       mCameraManager;
    CViewportManager     mViewportManager;
    TViewportMap         mViewportMap;
    Ogre::RenderWindow & mRenderWindow;
};

} // namespace

#endif // __CRENDERMANAGER_H__