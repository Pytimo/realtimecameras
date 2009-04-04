#ifndef __CSAMPLE0FRAMELISTENER_H__
#define __CSAMPLE0FRAMELISTENER_H__

#include "system/crtcframelistener.h"
#include "render/crendermanager.h"
#include "input/cinputmanager.h"
#include "types/rtc_types.h"
#include <vector>

class CSample0FrameListener: public CRtcFrameListener
{
public:
    explicit CSample0FrameListener(Ogre::SceneManager & sceneManager, RenderWindow & renderWindow);

    virtual void processUnbufferedKeyInput  (FrameEvent const & evt);
	virtual void processUnbufferedMouseInput(FrameEvent const & evt);

    virtual bool const frameUpdate(FrameEvent const & evt);

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CSample0FrameListener )

    enum
    {
        kMaxCameras = 4
    };

    typedef std::vector<rtc::TViewportHandle> TViewportList;

    rtc::SViewportInfo const getViewportInfo( int const index, int const numCameras ) const;

    void addCamera();
    void removeCamera();
    void updateActiveViewports();

    TViewportList         mViewportList;
    rtc::CRenderManager   mRenderManager;
    rtc::CInputManager    mInputManager;
    int                   mNumCameras;
};

#endif // __CSAMPLE0FRAMELISTENER_H__