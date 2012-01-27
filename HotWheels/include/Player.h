#pragma once
#include "stdafx.h"
#include "Vehicle.h"

using namespace Ogre;

class Player
{

private:
	Vehicle* pCar;
	Player(Player &);  // disable copy construction

public:
	Player(void);

	Vehicle* getVechicle();
	void init(Critter::RenderSystem* render, Ogre::SceneManager* mSceneMgr);

	void onKeyPress(OIS::Keyboard* pKeyBoard);
	//void attachCamera(Ogre::Camera* pCamera);
	~Player(void);
};

