#include "render/crendermanager.h"
#include "viewport/cviewport.h"
#include "camera/cgamecamera.h"
#include "ogrerenderwindow.h"
#include "ogrecamera.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
CRenderManager::CRenderManager( Ogre::SceneManager & sceneManager, Ogre::RenderWindow & renderWindow )
:mCameraManager( sceneManager )
,mViewportManager()
,mViewportMap()
,mRenderWindow( renderWindow )
{
}
//------------------------------------------------------------------------------------------
CRenderManager::~CRenderManager()
{
    removeAllRenderWindows();
}
//------------------------------------------------------------------------------------------
void CRenderManager::removeAllRenderWindows()
{
    CViewportManager::TViewportMap viewportMap = mViewportManager.getViewportMap();

    for(CViewportManager::TViewportMap::iterator iter=viewportMap.begin(); iter!=viewportMap.end(); ++iter)
    {
        iter->second->setOgreViewport( NULL ); // remove reference to ogre viewport
        mRenderWindow.removeViewport( iter->first );
    }
}
//------------------------------------------------------------------------------------------
void CRenderManager::removeDeletedViewports()
{
    CViewportManager::TDeletionList deletionList = mViewportManager.getDeletionList();

    if ( !deletionList.empty() )
    {
        for(CViewportManager::TDeletionList::iterator iter=deletionList.begin(); iter!=deletionList.end(); ++iter)
        {
            TViewportHandle const viewportHandle = *iter;
            mViewportMap.erase(viewportHandle);
            mRenderWindow.removeViewport( viewportHandle );
        }
        mViewportManager.clearDeletionList();
    }
}
//------------------------------------------------------------------------------------------
void CRenderManager::update()
{
    removeDeletedViewports();

    CViewportManager::TViewportMap viewportMap = mViewportManager.getViewportMap();

    for(CViewportManager::TViewportMap::iterator iter=viewportMap.begin(); iter!=viewportMap.end(); ++iter)
    {
        updateRenderWindowList( *iter->second );
    }
}
//------------------------------------------------------------------------------------------
Ogre::Viewport * CRenderManager::getRenderViewport(TViewportHandle const handle) const
{
    TViewportMap::const_iterator iter = mViewportMap.find( handle );
    return iter != mViewportMap.end() ? iter->second : NULL;
}
//------------------------------------------------------------------------------------------
void CRenderManager::updateRenderWindowList( CViewport & viewport )
{
    TCameraId const cameraId = viewport.getCameraId();
    TViewportHandle const viewportHandle = viewport.getHandle();

    Ogre::Viewport * pOgreViewport = getRenderViewport(viewportHandle);

    if( viewport.isActive() )
    {
        if ( CGameCamera * const pGameCamera = mCameraManager.getCamera( cameraId ) )
        {
            // cameraId is valid, let's try to create the OGRE viewport
            Ogre::Camera & ogreCamera = pGameCamera->getCamera(); // grab OGRE camera

            SViewportInfo const &viewportInfo = viewport.getViewportInfo();

            if( pOgreViewport == NULL ) // not in render viewport list
            {
                if ( pOgreViewport = mRenderWindow.addViewport(&ogreCamera, 
														        viewportHandle, 
														        viewportInfo.left,
														        viewportInfo.top,
														        viewportInfo.width,
														        viewportInfo.height) )
                {
                    viewport.setOgreViewport( pOgreViewport ); // attach to viewport

                    pOgreViewport->setBackgroundColour( Ogre::ColourValue(0,0,0) );

                    Ogre::Real const aspectRatio = static_cast<Ogre::Real>(pOgreViewport->getActualWidth()) / static_cast<Ogre::Real>(pOgreViewport->getActualHeight());
                    ogreCamera.setAspectRatio(aspectRatio);
                    mViewportMap.insert( TViewportMap::value_type(viewportHandle, pOgreViewport) );
                }
            }
            else if ( viewport.checkUpdate() && pOgreViewport )
            {
                Ogre::Real const aspectRatio = static_cast<Ogre::Real>(pOgreViewport->getActualWidth()) / static_cast<Ogre::Real>(pOgreViewport->getActualHeight());
                ogreCamera.setAspectRatio(aspectRatio);
            }
        }
    }
    else if ( !viewport.isActive() && pOgreViewport )
    {
        // viewport is not active, but it is in the active list
        // remove it.
        viewport.setOgreViewport( NULL );
        mViewportMap.erase(viewportHandle);
        mRenderWindow.removeViewport( viewportHandle );
    }
}
//------------------------------------------------------------------------------------------