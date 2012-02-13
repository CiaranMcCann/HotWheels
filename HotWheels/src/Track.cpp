/**
 * @file Track.cpp
 * This class controls contsucting the track from the file. It also handles the 
 * waypoints collections. It allows the vechiles to poll for their next waypoint.
 *
 * @brief Controls the Track visually and the waypoints.
 *
 * @author Ciarán McCann 
 */
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


/**
   This gets a Vector point from the waypoints list

   @param int index for array indexing.
   @return Ogre::Vector3 Position of waypiont.
 */
Ogre::Vector3 * Track::getTrackDataPiontAt(int index){

	//assert( !(index >= mTrackDataPionts.size()) );

	if( index >= mTrackDataPionts.size()){
		return & mTrackDataPionts.at(mTrackDataPionts.size()-1);
	}
	
	return & mTrackDataPionts.at(index);
}

/**
   This gets the ScenceNode point from the waypoints list.

   @param int index for array indexing.
   @return Ogre::SceneNode *.
 */
Ogre::SceneNode * Track::getTrackNodeAt(int index){
	return mSceneManager->getSceneNode("waypiontNode" + Utils::toString(index));
}

/**
   Checks if the indexd waypiont is the end of the track

   @param int index for array indexing.
   @return bool
 */
bool Track::checkIfFinished(int index){
	return index >= mTrackDataPionts.size();
}


void Track::loadWayPoints(Ogre::String wayPointFileName, SceneManager* sceneManager, Critter::RenderSystem* mRenderSystem){

	mSceneManager = sceneManager;
	
	char* str;
	std::string s = "";
	std::ifstream file;	
	file.open(wayPointFileName, std::ios::out);
	std::vector<std::string> subString;

	float trackWidth = 1.35;
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

		if(previous != current){

			Vector3 upXa = (current - previous).crossProduct(UP);

			Vector3 directionToNextBarrier = (previous - current).normalisedCopy();

			mTrackDataPionts.push_back( current );

			/*
			Ogre::Entity *cube = mSceneManager->createEntity("waypiont" + Utils::toString(i) , "concrete.mesh");
			cube->setMaterialName("Examples/RustySteel");
			SceneNode * sceneNode = mSceneManager->createSceneNode("waypiontNode" + Utils::toString(i));
			mSceneManager->getRootSceneNode()->addChild(sceneNode);
			sceneNode->attachObject( cube );
			sceneNode->rotate(Vector3(0,1,0), Ogre::Radian( Ogre::Degree(45) )  , Ogre::Node::TS_LOCAL);
			current.y += 2;
			sceneNode->scale(0.1,0.1,0.1);
			sceneNode->setPosition(current);
			*/
			i++;

			//Road mesh!!

			Critter::BodyDescription bodyDescription;
			bodyDescription.mMass = 9000.f;  // Set a mass of 40kg.
			NxOgre::MeshManager* mMeshManager = NxOgre::MeshManager::getSingleton();
		
		
			Critter::Body* t = mRenderSystem->createBody(NxOgre::BoxDescription(6.5,2,1),  NxOgre::Vec3(current + upXa*trackWidth + Vector3(0, 10.2,0) ), "concrete.mesh", bodyDescription);


			/************************************************************************/
			/* Roatat barriers                                                                     */
			/************************************************************************/
	
			{	
				Vector3 bodyCurrentOrient = t->getGlobalOrientationQuat().as<Ogre::Quaternion>()*Ogre::Vector3(1,0,1);

				directionToNextBarrier.y = 0;
				bodyCurrentOrient.y = 0;

				float degree = Ogre::Degree(bodyCurrentOrient.normalisedCopy().angleBetween(directionToNextBarrier)).valueDegrees();
				NxOgreUtils::rotate(t,Vector3(0,1,0), degree - 42); //Magic number 42 is not the meaning of life, but the degree by which the enviorment for all model orientions seesm to be off
				t->getNode()->setScale(Ogre::Vector3(5,1,1));

			}

			/************************************************************************/
			/* Roatat barriers                                                                     */
			/************************************************************************/
	
			Vector3 aXup = UP.crossProduct((current - previous));
			Critter::BodyDescription bodyDescription2;
			bodyDescription2.mMass = 9000.f;  // Set a mass of 40kg.
			 t =  mRenderSystem->createBody(NxOgre::BoxDescription(6.5,2,1),  NxOgre::Vec3(current + aXup*trackWidth + Vector3(0,5.2,0)), "concrete.mesh", bodyDescription2);

			 
			 float degree = 0;
			 {
				 
				 Vector3 bodyCurrentOrient = t->getGlobalOrientationQuat().as<Ogre::Quaternion>()*Ogre::Vector3(1,0,1);

				directionToNextBarrier.y = 0;
				bodyCurrentOrient.y = 0;

				 degree = Ogre::Degree(bodyCurrentOrient.normalisedCopy().angleBetween(directionToNextBarrier)).valueDegrees();

				NxOgreUtils::rotate(t,Vector3(0,1,0), degree - 42); //Magic number 42 is not the meaning of life, but the degree by which the enviorment for all model orientions seesm to be off
				t->getNode()->setScale(Ogre::Vector3(5,1,1));

			 }


			Ogre::Entity *cube = mSceneManager->createEntity("waypion" + Utils::toString(i) , "road.mesh");
			SceneNode * sceneNode = mSceneManager->createSceneNode("waypionNode" + Utils::toString(i));
			mSceneManager->getRootSceneNode()->addChild(sceneNode);
			sceneNode->rotate(Vector3(0,1,0), Ogre::Degree(degree + 42) );
			sceneNode->attachObject( cube );
			sceneNode->scale(12,1,1.8);
			sceneNode->setPosition(current + Vector3(0,0.1,0));
		}

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

