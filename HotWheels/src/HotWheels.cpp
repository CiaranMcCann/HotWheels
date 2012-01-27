/*
-----------------------------------------------------------------------------
Filename:    HotWheels.cpp
-----------------------------------------------------------------------------
Programming GuideLines 

	Use namespaces derclatation instead of a using derative when using Critter or NxOgre
	classes as it allows for more readable code
-----------------------------------------------------------------------------
*/
#include "stdafx.h"
#include "HotWheels.h"


//-------------------------------------------------------------------------------------
HotWheels::HotWheels(void):mTrack()
{


}

HotWheels::~HotWheels(void)
{
}

void HotWheels::createScene(){

	
	if(!Track::trackingEnabled)
	mTrack.loadWayPoints("aTrack.txt", mSceneMgr);
  
	/************************************************************************/
	/*  Setup some default Ogre scene                                       */ 

	mSceneMgr->setSkyBox(true, "Examples/EarlyMorningSkyBox", 1500, false);

	//set shadows
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

//	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

	// Create the ground with grass on it
	Ogre::Plane plane;
	plane.normal = Ogre::Vector3::UNIT_Y;
	// horizontal plane with normal up in y-direction
	plane.d = 0;//Plane passes through the origin i.e. plane at y = 0

	Ogre::MeshManager::getSingleton().createPlane("floor",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		3000,
		3000,10,10,true,1,10,10,Ogre::Vector3::UNIT_Z);

	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");

	pPlaneEnt->setMaterialName("Examples/WaterStream"); //Examples/Water
	pPlaneEnt->setCastShadows(false);

	Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	floorNode->setPosition(-500,295,300);
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);

	
	//	//-500,-200,300
	//mSceneMgr->getRootSceneNode()->attachObject(floor);

	// use a small amount of ambient lighting
	mSceneMgr->setAmbientLight(ColourValue(0.9, 0.9, 0.9));

	// add a bright light above the scene
	Light* light = mSceneMgr->createLight();
	light->setType(Light::LT_POINT);
	light->setPosition(-10, 400, 20);
	light->setSpecularColour(ColourValue::White);
  
	mCamera->setPosition(5,0,0);
	mCamera->lookAt(0,0,0);
	mCamera->setNearClipDistance(0.02f);
	mCamera->setFarClipDistance(1000.0f);
	mCameraMan->setTopSpeed(7.5);

	// Plane creation
	mScene->createSceneGeometry(NxOgre::PlaneGeometryDescription());

	// Create the rendersystem.
	mRenderSystem = new Critter::RenderSystem(mScene, mSceneMgr);
	NxOgre::MeshManager* mMeshManager = NxOgre::MeshManager::getSingleton();

	/*
	// First off, let's load the Convex Mesh "barrel" through the Ogre resource system, we setup earlier.
	// - The filename is "barrel.nxs" and it's somewhere in the OgreSamples media folder under the "General" ResourceGroup.
	// - We shall call it "barrel".
	 NxOgre::Mesh* mBarrelMesh = mMeshManager->load("ogre://General/cCube.nxs", "barrel");

	// Next create a Body Description for our Bodies with barrels. It's going to be used many times
	// So, let's create it outside the for loop for optimisation reasons.
	Critter::BodyDescription bodyDescription;
	bodyDescription.mMass = 40.0f;  // Set a mass of 40kg.

	// 10 times, create a Body with a ConvexDescription using our barrel we loaded, stack each body on top of
	// each other in the air, and use the "barrel.mesh" for rendering.
	for (unsigned int i=0;i < 10;i++)
		mRenderSystem->createBody(NxOgre::ConvexDescription(mBarrelMesh), NxOgre::Vec3(400,700,-200), "Cylinder.001.mesh", bodyDescription);

	// Next up, let's load a Triangle Mesh "island.nxs" through the Ogre resource system.
	// - It's the general resource group, so we can omit that from the path. (NxOgre is clever enough to know what you mean)
	// - Call it "island".
	*/

	
	NxOgre::Mesh* terrain = mMeshManager->load("ogre://terrain.nxs", "terrain");
	mScene->createSceneGeometry(NxOgre::TriangleGeometryDescription(terrain), NxOgre::Vec3(-500,-200,300));
	

	Ogre::Entity * pTerrain = mSceneMgr->createEntity("island2", "SCG_terrain.mesh");
	SceneNode* islandNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(-500,-200,300));
	islandNode2->attachObject( pTerrain);
	 pTerrain->setCastShadows(false);

	/************************************************************************/
	/* Physics starts now                                                                     */
	/************************************************************************/

	mPlayer.init(mRenderSystem,mSceneMgr);
	mPlayer.getVechicle()->attachCamera(mCamera);

	mAi.init(mRenderSystem,mSceneMgr);
	mAi.setTrack(&mTrack);

	//Ogre::Entity * e = mPlayer.getVechicle()->getBody()->getNode()->getEntityAt(1);
	//e->setCastShadows(true);
	
	

}


bool HotWheels::keyPressed( const OIS::KeyEvent &arg )
{

	BaseApplication::keyPressed(arg);
	
	return true;
}

bool HotWheels::frameRenderingQueued(const Ogre::FrameEvent& evt){

	mKeyboard->capture();
	mMouse->capture();

	mPlayer.onKeyPress(mKeyboard);

	SoundManager::getInstance()->update();
	
	if(!Track::trackingEnabled)
	mAi.update(evt.timeSinceLastFrame);

	mAi.getVechicle()->update(evt.timeSinceLastFrame);
	mPlayer.getVechicle()->update(evt.timeSinceLastFrame);

	if(!Track::trackingEnabled)
		mTrack.checkCurrentWayPoint(mPlayer.getVechicle()->getBody()->getNode()->getPosition());
	
	mWorld->advance(evt.timeSinceLastFrame); 
	BaseApplication::frameRenderingQueued(evt);

	mAi.getVechicle()->postPhysics(evt.timeSinceLastFrame);
	mPlayer.getVechicle()->postPhysics(evt.timeSinceLastFrame);

	

	 return true;

}

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        HotWheels app;

        try {
            app.go();

        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
