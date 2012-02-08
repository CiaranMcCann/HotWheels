#include "stdafx.h"

#include "Track.h"

ofstream Track::file;
int Track::fileTimer = 0;
NxOgre::Vec3 Track::previous;
bool Track::trackingEnabled = false;

Track::Track(void):currentWayPoint(10)
{
 mTrackDataPionts = std::vector<Ogre::Vector3> (0) ;
}


Track::~Track(void)
{

}


Ogre::Vector3 * Track::getTrackDataPiontAt(int index){

	//assert( !(index >= mTrackDataPionts.size()) );

	if( index >= mTrackDataPionts.size()){
		return & mTrackDataPionts.at(mTrackDataPionts.size()-1);
	}
	
	return & mTrackDataPionts.at(index);
}

Ogre::SceneNode * Track::getTrackNodeAt(int index){
	return mSceneManager->getSceneNode("waypiontNode" + Utils::toString(index));
}

void Track::loadWayPoints(Ogre::String wayPointFileName, SceneManager* sceneManager, Critter::RenderSystem* mRenderSystem){

	mSceneManager = sceneManager;
	
	char* str;
	std::string s = "";
	std::ifstream file;	
	file.open(wayPointFileName, std::ios::out);
	std::vector<std::string> subString;

	float trackWidth = 0.7;
	Vector3 UP = Vector3(0,1,0);


	int i = 0;
	Vector3 previous;

	getline(file,s);
	Utils::split(s," ", subString);
	previous = Ogre::Vector3(atof(subString.at(0).c_str()),atof(subString.at(1).c_str()),atof(subString.at(2).c_str()));

	//file.getline(str,
	while( getline(file,s) ){


		Utils::split(s," ", subString);
	
		Vector3 current = Ogre::Vector3(atof(subString.at(0).c_str()),atof(subString.at(1).c_str()),atof(subString.at(2).c_str()));
		Vector3 upXa = (current - previous).crossProduct(UP);

		Vector3 directionOfBarrier = ( current - previous).normalisedCopy();

		mTrackDataPionts.push_back( current );

		Ogre::Entity *cube = mSceneManager->createEntity("waypiont" + Utils::toString(i) , "concrete.mesh");
		cube->setMaterialName("Examples/RustySteel");
		SceneNode * sceneNode = mSceneManager->createSceneNode("waypiontNode" + Utils::toString(i));
		mSceneManager->getRootSceneNode()->addChild(sceneNode);
		sceneNode->attachObject( cube );
		sceneNode->rotate(Vector3(0,1,0), Ogre::Radian( Ogre::Degree(45) )  , Ogre::Node::TS_LOCAL);
		current.y += 2;
		sceneNode->scale(0.1,0.1,0.1);
		sceneNode->setPosition(current);
		i++;

		//Road mesh!!

		//Vector3 currentScenNodeDir = (sceneNode->getOrientation()*directionOfBarrier);
		//Ogre::Real delta =  acos(  directionOfBarrier.dotProduct( currentScenNodeDir.normalisedCopy()  ) );

		Critter::BodyDescription bodyDescription;
		bodyDescription.mMass = 4.0f;  // Set a mass of 40kg.
		NxOgre::MeshManager* mMeshManager = NxOgre::MeshManager::getSingleton();
	//	NxOgre::Mesh* mBarrelMesh = mMeshManager->load("ogre://General/concrete.nxs", "barrel"  + Utils::toString(i));
		Critter::Body* t = mRenderSystem->createBody(NxOgre::BoxDescription(2,2,1),  NxOgre::Vec3(current + upXa*trackWidth + Vector3(0,0.5,0) ), "concrete.mesh", bodyDescription);


		//Roate things
		NxOgre::Quat q = t->getGlobalOrientationQuat();
		Vector3 bodyCurrentOrient =  Ogre::Quaternion(q.w, q.x, q.y, q.z) *  Vector3( 1, 0,1 );

		Ogre::Radian ro = bodyCurrentOrient.angleBetween(directionOfBarrier);
		//TODO - problem with rotation

		Ogre::Matrix3 xRotation;
		xRotation.FromEulerAnglesXYZ( ro, Ogre::Radian(), Ogre::Radian() );
		Ogre::Quaternion xQuaternion;
		xQuaternion.FromRotationMatrix(xRotation);

		

		t->setGlobalOrientation( NxOgre::Quat(NxOgre::Radian(45),NxOgre::Vec3(0,1,0)) );
		
		//t->setGlobalOrientation( NxOgre::Matrix33( Ogre::Quaternion( 45 ) ));
		//t->getNode()->getSceneNode()->getParentSceneNode()-->rotate(Vector3(0,1,0), Ogre::Radian( Ogre::Degree(-45) )  , Ogre::Node::TS_LOCAL)
//		OutputDebugString( Utils::toString(t->getNode()->getSceneNode()->getOrientation()).c_str() );
		OutputDebugString( "\n" );


//		t->getNode()->getSceneNode()->rotate(Vector3(0,1,0), Ogre::Radian( Ogre::Degree(-45) )  , Ogre::Node::TS_LOCAL);
	//	t->getNode()->getSceneNode()->roll(Ogre::Radian( Ogre::Degree(45) ));

		


		//t->setGlobalOrientationQuat( NxOgre::Quat(t->getNode()->getSceneNode()->getOrientation() ) );

	//	t->setCMassGlobalOrientation(NxOgre::Quat(t->getNode()->getOrientationQuat() ));
		

	//	OutputDebugString( Utils::toString(t->getNode()->getSceneNode()->getOrientation()).c_str() );
		OutputDebugString( "\n" );

		//t->getNode()->getSceneNode()->scale(1.6,0.6,0.5);
		//t->getNode()->getSceneNode()->getShowBoundingBox();
	
		Vector3 aXup = UP.crossProduct((current - previous));
		Critter::BodyDescription bodyDescription2;
		bodyDescription2.mMass = 4.0f;  // Set a mass of 40kg.
		mRenderSystem->createBody(NxOgre::BoxDescription(2,2,1),  NxOgre::Vec3(current + aXup*trackWidth + Vector3(0,0.5,0)), "concrete.mesh", bodyDescription2);

		previous = Ogre::Vector3(current);
		subString.clear();


		if(i == 10){

			Ogre::Entity *cube = mSceneManager->createEntity("waypiont", "cube.1m.mesh");
			cube->setMaterialName("Examples/RustySteel");
			SceneNode * sceneNode = mSceneManager->createSceneNode("waypiontNode");
			mSceneManager->getRootSceneNode()->addChild(sceneNode);
			sceneNode->attachObject( cube );
			sceneNode->rotate(Vector3(0,1,0), Ogre::Radian( Ogre::Degree(45) )  , Ogre::Node::TS_LOCAL);
			current.y += 5;
			sceneNode->setPosition(current);
		}
		
	}	

	file.close();
}


void Track::trackVechicleMovement(NxOgre::Vec3 pos, Ogre::String fileNameToWriteTo, int frequnceyOfWrites){

	if( (Track::previous-pos).magnitude() > 9 ){

	
		if(!file.is_open()){
			file.open (fileNameToWriteTo, ios::app);
		}

			Track::previous = pos;
			file << Utils::toString(pos) + "\n";
			fileTimer =  frequnceyOfWrites;
			file.close();

	}

	fileTimer--;
}

void Track::checkCurrentWayPoint(Ogre::Vector3 playerPosition){
	 
	Ogre::Vector3 pPos = Ogre::Vector3( *(getTrackDataPiontAt(currentWayPoint)) );

	float dist = (pPos - playerPosition).length();

	if( dist < 100 ){

		pPos.y += 5;
		mSceneManager->getSceneNode("waypiontNode")->setPosition( pPos  );

		currentWayPoint += 5;
	}

}

