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

void Track::loadWayPoints(Ogre::String wayPointFileName, SceneManager* sceneManager){

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

		mTrackDataPionts.push_back( current );

		//atof ( szInput )
		Ogre::Entity *cube = sceneManager->createEntity("cube" + Utils::toString(i), "cube.1m.mesh");
		//cube->setMaterialName("Examples/RustySteel");

		// Create a new sceneNode fro the cube, attach it to the rootSceneNode 
		//as a child of the scene manager
		SceneNode * sceneNode = sceneManager->createSceneNode("cubeNode" + Utils::toString(i));
		sceneManager->getRootSceneNode()->addChild(sceneNode);
		sceneNode->attachObject( cube );
		sceneNode->setPosition(current + upXa*trackWidth + Vector3(0,0.5,0));

		i++;
		Vector3 aXup = UP.crossProduct((current - previous));

		Ogre::Entity *cube2 = sceneManager->createEntity("cube" + Utils::toString(i), "cube.1m.mesh");
		//cube->setMaterialName("Examples/RustySteel");

		 sceneNode = sceneManager->createSceneNode("cubeNode" + Utils::toString(i));
		sceneManager->getRootSceneNode()->addChild(sceneNode);
		sceneNode->attachObject( cube2 );
		sceneNode->setPosition(current + aXup*trackWidth + Vector3(0,0.5,0));

		previous = Ogre::Vector3(current);
		subString.clear();

		i++;

		if(i == 10){

			Ogre::Entity *cube = mSceneManager->createEntity("waypiont", "cube.1m.mesh");
			cube->setMaterialName("Examples/RustySteel");
			SceneNode * sceneNode = mSceneManager->createSceneNode("waypiontNode");
			mSceneManager->getRootSceneNode()->addChild(sceneNode);
			sceneNode->attachObject( cube );
			current.y += 5;
			sceneNode->setPosition(current);
		}
		
	}	

	file.close();
}


void Track::trackVechicleMovement(NxOgre::Vec3 pos, Ogre::String fileNameToWriteTo, int frequnceyOfWrites){

	if( (Track::previous-pos).magnitude() > 9 ){

		OutputDebugStringW(L"My output string.");
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

