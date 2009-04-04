/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    CRtcApplication.h
Description: Base class for all the OGRE examples
-----------------------------------------------------------------------------
*/

#ifndef __CRTCAPPLICATION_H__
#define __CRTCAPPLICATION_H__

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "OgreStringConverter.h"
#include "OgreException.h"

//Use this define to signify OIS will be used as a DLL
//(so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

using namespace Ogre;

class CRtcFrameListener;

/** Base class which manages the standard startup of an Ogre application.
    Designed to be subclassed for specific examples if required.
*/
class CRtcApplication
{
public:
    /// Standard constructor
    CRtcApplication();
    /// Standard destructor
    virtual ~CRtcApplication();

    /// Start the example
    virtual void go();

protected:

    // These internal methods package up the stages in the startup process
    /** Sets up the application - returns false if the user chooses to abandon configuration. */
    virtual bool setup();
    /** Configures the application - returns false if the user chooses to abandon configuration. */
    virtual bool configure();
    virtual void chooseSceneManager();
    virtual void createScene() = 0;    // pure virtual - this has to be overridden

    virtual void destroyScene();    // Optional to override this

    /// Method which will define the source of resources (other than current folder)
    virtual void setupResources();

	/// Optional override method where you can create resource listeners (e.g. for loading screens)
	virtual void createResourceListener();

	/// Optional override method where you can perform resource group loading
	/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	virtual void loadResources();

    Ogre::Root            * mpRoot;
    Ogre::SceneManager    * mpSceneMgr;
    Ogre::RenderWindow    * mpWindow;
	 Ogre::String            mRTCPath;
    Ogre::String            mResourcePath;
    Ogre::String            mOGREResourcePath;
};


#endif // __CRTCAPPLICATION_H__