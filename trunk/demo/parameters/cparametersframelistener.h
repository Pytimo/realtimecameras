#ifndef __CPARAMETERSFRAMELISTENER_H__
#define __CPARAMETERSFRAMELISTENER_H__

#include "system/crtcframelistener.h"
#include "render/crendermanager.h"
#include "input/cinputmanager.h"
#include "types/rtc_types.h"
#include <vector>

class CParametersFrameListener: public CRtcFrameListener
{
public:
    explicit CParametersFrameListener(Ogre::SceneManager & sceneManager, RenderWindow & renderWindow);

    virtual void processUnbufferedKeyInput  (FrameEvent const & evt);
	virtual void processUnbufferedMouseInput(FrameEvent const & evt);

    virtual bool const frameUpdate(FrameEvent const & evt);

private:
    RTC_DISABLE_COPY_AND_ASSIGNMENT( CParametersFrameListener )

    void createCamera();
    void updateOverlay(  Ogre::Camera & ogreCamera );
    void updateFOV( Ogre::Camera & ogreCamera, Real const deltaTime );
    void updateAspectRatio( Ogre::Camera & ogreCamera, Real const deltaTime );
    void updateParameters( Real const deltaTime );


    rtc::CRenderManager   mRenderManager;
    rtc::CInputManager    mInputManager;
    Overlay             * mParametersOverlay;
    Ogre::Degree          mFOV;
    Real                  mAspectRatio;
    rtc::TCameraId        mCameraId;
};

#endif // __CPARAMETERSFRAMELISTENER_H__