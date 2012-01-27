#include "stdafx.h"
#include "Player.h"


Player::Player()
{

}

Player::~Player(void)
{
}


void Player::init(Critter::RenderSystem* render, Ogre::SceneManager* mSceneMgr){
	pCar = Vehicle::createVehicle("camaro",render,  mSceneMgr);

	pCar->getBody()->setGlobalPosition(Vector3(376.36890, 299.98193, -569.52747));
	pCar->getBody()->getNode()->setOrientation(0.86900270, -1.2700194e-006, -0.48544881, 2.6728865e-006);
	
}


void Player::onKeyPress(OIS::Keyboard* pKeyBoard){

	if (pKeyBoard->isKeyDown(OIS::KC_I)){
		pCar->accelerate();
		Ogre::Vector3 g = pCar->getBody()->getNode()->getPosition();
		Ogre::Quaternion gh = pCar->getBody()->getNode()->getOrientation();

		int j = 0;
	}else if(pKeyBoard->isKeyDown(OIS::KC_K)){
		pCar->deaccelerate();
	}
	
	if(pKeyBoard->isKeyDown(OIS::KC_J))
	{
		pCar->steerRight();

	}else if (pKeyBoard->isKeyDown(OIS::KC_L)){
		

		pCar->steerLeft();

	}


}

Vehicle* Player::getVechicle(){
	return pCar;
}
