#include "ogrescenemanager.h"
#include "camera/ccameramanager.h"
#include "camera/cgamecamera.h"
#include "camera/cfirstpersoncamera.h"
#include "input/ccontrolmanager.h"

//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------

CCameraManager::CCameraManager( Ogre::SceneManager & sceneManager )
:mSceneManager( sceneManager )
,mCameraMap()
,mIdCounter( kInvalidCameraId ) 
{
}
//------------------------------------------------------------------------------------------
CCameraManager::~CCameraManager()
{
}
//------------------------------------------------------------------------------------------
TCameraId const CCameraManager::createCamera( Ogre::String const & name, ECameraType const cameraType, bool const active )
{
    if (Ogre::Camera * pOgreCamera = mSceneManager.createCamera(name) )
    {
        TCameraId const newId = mIdCounter+1;

        if ( newId != kInvalidCameraId )
        {
            switch( cameraType )
            {
                case kCameraType_FirstPerson:
                    if ( CFirstPersonCamera * const pCamera = new CFirstPersonCamera( pOgreCamera, newId, active ) )
                    {
                        mCameraMap.insert( TCameraMap::value_type( newId, pCamera) );
                        mIdCounter = newId; // store new id

                        return newId;
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return kInvalidCameraId;
}

//------------------------------------------------------------------------------------------
void CCameraManager::removeCamera( TCameraId const cameraId )
{
    // remove camera from list
    TCameraMap::iterator iter = mCameraMap.find( cameraId );

    if ( iter != mCameraMap.end() )
    {
        // need to remove ogre camera from scenemanager ...
        mSceneManager.destroyCamera( &iter->second->getCamera() );

        delete iter->second; // release camera

        mCameraMap.erase( iter ); // remove entry from list
    }
}
//------------------------------------------------------------------------------------------
CGameCamera * CCameraManager::getCamera( TCameraId const cameraId )
{
    TCameraMap::iterator iter = mCameraMap.find( cameraId );
    return iter != mCameraMap.end() ? iter->second : NULL;
}
//------------------------------------------------------------------------------------------
CGameCamera const * const CCameraManager::getCamera( TCameraId const cameraId ) const
{
    TCameraMap::const_iterator iter = mCameraMap.find( cameraId );
    return iter != mCameraMap.end() ? iter->second : NULL;
}
//------------------------------------------------------------------------------------------
void CCameraManager::update( CControlManager const & controlManager, float const deltaTime )
{
    // do any work to add or remove cameras here

    // update active camera logic
    for (TCameraMap::iterator iter = mCameraMap.begin(); iter != mCameraMap.end(); ++iter)
    {
        CGameCamera * const pCamera = iter->second;

        if (pCamera->isActive())
        {
            pCamera->update(controlManager, deltaTime);
        }
    }
}
//------------------------------------------------------------------------------------------
void CCameraManager::preThink()
{
}
//------------------------------------------------------------------------------------------
void CCameraManager::think()
{
}
//------------------------------------------------------------------------------------------
void CCameraManager::postThink()
{
}
//------------------------------------------------------------------------------------------
