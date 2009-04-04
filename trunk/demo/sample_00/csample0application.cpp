#include "csample0application.h"
#include "csample0framelistener.h"
//------------------------------------------------------------------------------------------
using namespace rtc;
using namespace Ogre;
//------------------------------------------------------------------------------------------
CSample0Application::CSample0Application()
: CRtcApplication()
, mpFrameListener( NULL )
{
}

//------------------------------------------------------------------------------------------

CSample0Application::~CSample0Application()
{
    delete mpFrameListener;
}

//------------------------------------------------------------------------------------------

void CSample0Application::createFrameListener()
{
    mpFrameListener= new CSample0FrameListener(*mpSceneMgr, *mpWindow);
    mpRoot->addFrameListener(mpFrameListener);
}

//------------------------------------------------------------------------------------------

void CSample0Application::createScene()
{
    createFrameListener();

    mpSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
    mpSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

    Entity *ent = mpSceneMgr->createEntity("Ninja", "ninja.mesh");
    ent->setCastShadows(true);
    mpSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

    Plane plane(Vector3::UNIT_Y, 0);

    MeshManager::getSingleton().createPlane("ground",
        ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
        1500,1500,20,20,true,1,5,5,Vector3::UNIT_Z);

   ent = mpSceneMgr->createEntity("GroundEntity", "ground");
   mpSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ent);

   ent->setMaterialName("Examples/Rockwall");
   ent->setCastShadows(false);

   Light *light = mpSceneMgr->createLight("Light1");
   light->setType(Light::LT_POINT);
   light->setPosition(Vector3(0, 150, 250));

   light->setDiffuseColour(1.0, 0.0, 0.0);
   light->setSpecularColour(1.0, 0.0, 0.0);

   light = mpSceneMgr->createLight("Light3");
   light->setType(Light::LT_DIRECTIONAL);
   light->setDiffuseColour(ColourValue(.25, .25, 0));
   light->setSpecularColour(ColourValue(.25, .25, 0));

   light->setDirection(Vector3( 0, -1, 1 ));

   light = mpSceneMgr->createLight("Light2");
   light->setType(Light::LT_SPOTLIGHT);
   light->setDiffuseColour(0, 0, 1.0);
   light->setSpecularColour(0, 0, 1.0);

   light->setDirection(-1, -1, 0);
   light->setPosition(Vector3(300, 300, 0));

   light->setSpotlightRange(Degree(35), Degree(50));
}

//------------------------------------------------------------------------------------------
