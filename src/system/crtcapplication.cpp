#include "system/crtcapplication.h"
//------------------------------------------------------------------------------------------
namespace
{
    const char * const skRTCEnvironmentName = "RTC_PATH";
#if ( defined(_DEBUG) && OGRE_PLATFORM != OGRE_PLATFORM_APPLE )
    const char * const skPluginsFilename    = "plugins_d.cfg";
#else
    const char * const skPluginsFilename    = "plugins.cfg";
#endif
    const char * const skOgreConfigFilename = "ogre.cfg";
    const char * const skOgreLogFilename    = "ogre.log";
    const char * const skResourceFilename   = "resources.cfg";
}
//------------------------------------------------------------------------------------------
CRtcApplication::CRtcApplication()
:mpRoot         ( NULL )
,mpSceneMgr     ( NULL )
,mpWindow       ( NULL )
,mRTCPath       ( )
,mResourcePath  ( )
{
	// Provide a nice cross platform solution for locating the configuration files
	// On windows files are searched for in the current working directory, on OS X however
	// you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
    mRTCPath = getenv( skRTCEnvironmentName );
    mResourcePath = mRTCPath + "/resources/";
#endif
}
//------------------------------------------------------------------------------------------
CRtcApplication::~CRtcApplication()
{
    delete mpRoot;
}
//------------------------------------------------------------------------------------------
void CRtcApplication::go()
{
    if (!setup())
    {
        return;
    }

    mpRoot->startRendering();

    // clean up
    destroyScene();
}
//------------------------------------------------------------------------------------------
// These internal methods package up the stages in the startup process
/** Sets up the application - returns false if the user chooses to abandon configuration. */
bool CRtcApplication::setup()
{

	String pluginsPath;
	// only use plugins.cfg if not static
#ifndef OGRE_STATIC_LIB
	pluginsPath = mResourcePath + skPluginsFilename;
#endif
	
    mpRoot = new Root(pluginsPath, mResourcePath + skOgreConfigFilename, mResourcePath + skOgreLogFilename);

    setupResources();

    if ( !configure() )
    {
        // config failed.
        return false;
    }

    // Set default mipmap level (NB some APIs ignore this)
    TextureManager::getSingleton().setDefaultNumMipmaps(5);

	// Create any resource listeners (for loading screens)
	createResourceListener();
	// Load resources
	loadResources();

    chooseSceneManager();

	// Create the scene
    createScene();

    return true;
}
//------------------------------------------------------------------------------------------
/** Configures the application - returns false if the user chooses to abandon configuration. */
bool CRtcApplication::configure()
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mpRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mpWindow = mpRoot->initialise(true);
        return true;
    }
    else
    {
        return false;
    }
}
//------------------------------------------------------------------------------------------
void CRtcApplication::chooseSceneManager()
{
    // Create the SceneManager, in this case a generic one
    mpSceneMgr = mpRoot->createSceneManager(ST_GENERIC, "RTCSMInstance");
}
//------------------------------------------------------------------------------------------
void CRtcApplication::destroyScene()
{
}    // Optional to override this
//------------------------------------------------------------------------------------------
/// Method which will define the source of resources (other than current folder)
void CRtcApplication::setupResources()
{
    // Load resource paths from config file
    ConfigFile cf;
    cf.load(mResourcePath + skResourceFilename);

    // Go through all sections & settings in the file
    ConfigFile::SectionIterator seci = cf.getSectionIterator();

    String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        ConfigFile::SettingsMultiMap *settings = seci.getNext();
        ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            ResourceGroupManager::getSingleton().addResourceLocation( String(mRTCPath + "/" + archName), typeName, secName);
#else
            ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
#endif
        }
    }
}
//------------------------------------------------------------------------------------------
/// Optional override method where you can create resource listeners (e.g. for loading screens)
void CRtcApplication::createResourceListener()
{

}
//------------------------------------------------------------------------------------------
/// Optional override method where you can perform resource group loading
/// Must at least do ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
void CRtcApplication::loadResources()
{
	// Initialise, parse scripts etc
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

}