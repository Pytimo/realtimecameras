#ifndef __CVIEWPORTMANAGER_H__
#define __CVIEWPORTMANAGER_H__

#include "types/rtc_types.h"
#include "game/cgameentity.h"
#include <map>
#include <list>

namespace rtc {

class CViewport;

class CViewportManager: public CGameEntity
{
public:
    typedef std::map<TViewportHandle, CViewport*> TViewportMap;
    typedef std::list<TViewportHandle> TDeletionList;

    explicit                CViewportManager();
	TViewportHandle const	createViewport(SViewportInfo const & viewportInfo, TCameraId const cameraId, bool const active);
	void                    deleteViewport(TViewportHandle const handle);
	void                    update(float const deltaTime);
	//void					processInput(CInput const & input);
    void                    setActive(TViewportHandle const handle, bool const active);
    void                    setCamera(TViewportHandle const handle, TCameraId const cameraId);
	CViewport       *       getViewport(TViewportHandle const handle);
	CViewport const * const	getViewport(TViewportHandle const handle) const;

    TViewportMap       & getViewportMap()       { return mViewportMap; }
    TViewportMap const & getViewportMap() const { return mViewportMap; }

    TDeletionList       & getDeletionList()       { return mDeletionList; }
    TDeletionList const & getDeletionList() const { return mDeletionList; }

    // used by CRenderManager
    void clearDeletionList();

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CViewportManager )

    void removeViewport(TViewportHandle const handle);

    TViewportMap         mViewportMap;
    TDeletionList        mDeletionList;
    TViewportHandle      mHandleCounter;
};

} // namespace

#endif // __CVIEWPORTMANAGER_H__