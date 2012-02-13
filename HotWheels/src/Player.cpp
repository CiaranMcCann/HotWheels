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


	NxOgreUtils::rotate(pCar->getBody(), Vector3(0,1,0), -45);
	pCar->getBody()->setGlobalPosition(Vector3(330.36890, 299.98193, -569.52747));	
//	pCar->setSteeringCoef(0.002f);
	
	//pCar->getBody()->setG
//	pCar->getBody()->setGlobalPosition(Vector3(276.36890, 299.98193, -569.52747));	
}


void Player::onKeyPress(OIS::Keyboard* pKeyBoard){

	if (pKeyBoard->isKeyDown(OIS::KC_I)){
		pCar->accelerate();

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
