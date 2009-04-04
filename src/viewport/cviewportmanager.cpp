#include "viewport/cviewportmanager.h"
#include "viewport/cviewport.h"
#include <algorithm>
//------------------------------------------------------------------------------------------
using namespace rtc;
//------------------------------------------------------------------------------------------
CViewportManager::CViewportManager()
:mViewportMap()
,mDeletionList()
,mHandleCounter( kInvalidViewportHandle )
{
}
//------------------------------------------------------------------------------------------
TViewportHandle const CViewportManager::createViewport(SViewportInfo const & viewportInfo, TCameraId const cameraId, bool const active)
{
    TViewportHandle const newHandle = mHandleCounter+1;

    if ( newHandle != kInvalidViewportHandle )
    {
        mHandleCounter = newHandle;

        if ( CViewport * const pViewport = new CViewport( newHandle, viewportInfo, cameraId, active ) )
        {
            mViewportMap.insert( TViewportMap::value_type(newHandle, pViewport) );
            return newHandle;
        }
        else
        {
            // couldn't create viewport
            // error handle here?
        }
    }

    return kInvalidViewportHandle;
}
//------------------------------------------------------------------------------------------
void CViewportManager::deleteViewport(TViewportHandle const handle)
{
    TViewportMap::iterator iter = mViewportMap.find( handle );

    if( iter != mViewportMap.end() )
    {
        TDeletionList::const_iterator listIter = std::find( mDeletionList.begin(), mDeletionList.end(), handle );

        if ( listIter == mDeletionList.end() )
        {
            // not already in the deletion list, add it
            mDeletionList.push_back( handle );
        }
    }
}
//------------------------------------------------------------------------------------------
void CViewportManager::clearDeletionList()
{
    for(TDeletionList::iterator iter = mDeletionList.begin(); iter != mDeletionList.end(); ++iter )
    {
        removeViewport(*iter);
    }
    mDeletionList.clear();
}
//------------------------------------------------------------------------------------------
void CViewportManager::removeViewport(TViewportHandle const handle)
{
    // remove viewport from map
    TViewportMap::iterator iter = mViewportMap.find( handle );

    if ( iter != mViewportMap.end() )
    {
        delete iter->second; // release viewport

        mViewportMap.erase( iter ); // remove entry from list
    }
}
//------------------------------------------------------------------------------------------
void CViewportManager::update(float const deltaTime)
{
}
//------------------------------------------------------------------------------------------
void CViewportManager::setActive(TViewportHandle const handle, bool const active)
{
    if ( CViewport * const pViewport = getViewport( handle ) )
    {
		pViewport->setActive(active);
    }
}
//------------------------------------------------------------------------------------------
void CViewportManager::setCamera(TViewportHandle const handle, TCameraId const cameraId)
{
    if ( CViewport * const pViewport = getViewport( handle ) )
    {
        pViewport->setCameraId( cameraId );
    }
}
//------------------------------------------------------------------------------------------
CViewport * CViewportManager::getViewport(TViewportHandle const handle)
{
    TViewportMap::iterator iter = mViewportMap.find( handle );
    return iter != mViewportMap.end() ? iter->second : NULL;
}
//------------------------------------------------------------------------------------------
CViewport const * const CViewportManager::getViewport(TViewportHandle const handle) const
{
    TViewportMap::const_iterator iter = mViewportMap.find( handle );
    return iter != mViewportMap.end() ? iter->second : NULL;
}
//------------------------------------------------------------------------------------------
