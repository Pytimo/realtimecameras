#ifndef __CCAMERAMANAGER_H__
#define __CCAMERAMANAGER_H__

#include "types/rtc_types.h"
#include "ogreprerequisites.h"
#include <map>

namespace Ogre {
    class SceneManager;
}

namespace rtc {

class CGameCamera;
class CControlManager;

class CCameraManager
{
public:

    enum ECameraType
    {
        kCameraType_FirstPerson,

        kCameraType_Invalid = -1
    };

    explicit CCameraManager( Ogre::SceneManager & sceneManager );
    ~CCameraManager();

    TCameraId const createCamera( Ogre::String const & name, ECameraType const cameraType, bool const active );
    void removeCamera( TCameraId const cameraId );

    CGameCamera       *       getCamera( TCameraId const cameraId );
    CGameCamera const * const getCamera( TCameraId const cameraId ) const;

    void update( CControlManager const & controManager, float const deltaTime );
    void preThink();
    void think();
    void postThink();

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CCameraManager )

    typedef std::map<TCameraId, CGameCamera *> TCameraMap;

    Ogre::SceneManager & mSceneManager;
    TCameraMap           mCameraMap;
    TCameraId            mIdCounter;
};

} // namespace

#endif // __CCAMERAMANAGER_H__