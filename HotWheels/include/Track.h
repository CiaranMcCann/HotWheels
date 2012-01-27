#pragma once
#include "stdafx.h"
#include "Utilities.h"
#include <assert.h>


class Track
{

private:
	// Members all used for file recodring
	static ofstream file;
	static int fileTimer;
	static NxOgre::Vec3 previous;

	SceneManager* mSceneManager;

	//Waypionts
	int currentWayPoint;


	//Tack data pionts
	std::vector< Ogre::Vector3 > mTrackDataPionts;


public:

		static bool trackingEnabled;
	Track(void);
	~Track(void);

	void loadWayPoints(Ogre::String wayPointFileName, SceneManager* sceneMgr);
	static void trackVechicleMovement(NxOgre::Vec3 pos, Ogre::String fileNameToWriteTo, int frequnceyOfWrites);

	// Returns a pionter to the track data which then can be used by the car to move around it
	Ogre::Vector3 * getTrackDataPiontAt(int index);

	void checkCurrentWayPoint(Ogre::Vector3 playerPosition);

};

