#include "stdafx.h"
#include "Ai.h"


Ai::Ai(): mCurrentWayPiont(25), a(0)
{
 
}

Ai::~Ai(void)
{
}


void Ai::init(Critter::RenderSystem* render, Ogre::SceneManager* mSceneMgr){
	pCar = Vehicle::createVehicle("camaro",render,  mSceneMgr);

	pCar->getBody()->setGlobalPosition(Vector3(290,300,-550));
}

void Ai::update(float timeDelta){

	pTargetPosition = pTrack->getTrackDataPiontAt(mCurrentWayPiont);

	Vector3 destVector = *pTargetPosition - this->getVechicle()->getBody()->getNode()->getPosition();
	destVector.y = 0;
	destVector.normalise();

	//Vector3 cp = destVector.crossProduct(this->getVechicle()->getBody()->getNode()->getOrientation() * Ogre::Vector3(1,0,1));
	//float steer = cp.length();

	float angleDelta =  acos(  (this->getVechicle()->getBody()->getNode()->getOrientation() * Ogre::Vector3(1,0,1)).normalisedCopy().dotProduct( destVector ) );

	if( int(angleDelta) != 0 ){

		if(angleDelta > 0){
			this->getVechicle()->steerLeft();
		}else{
			this->getVechicle()->steerRight();
		}
	}

	float distance = ( this->getVechicle()->getBody()->getNode()->getPosition() - ( *pTargetPosition) ).length();

	if( distance > 10 ){

		if( a > 5){

			this->getVechicle()->accelerate();
			a = 0;
		}

		a++;

	}else{

		//a = -99999;
		mCurrentWayPiont += 2;
		//this->getVechicle()->deaccelerate();
	}



/*	
	Ogre::Vector3 t = pTargetPosition->normalisedCopy();
	t.y = 0;

	Ogre::Vector3 modelDirection =  (this->getVechicle()->getBody()->getNode()->getOrientation() * Ogre::Vector3(1,0,1) );
	modelDirection.y = 0;

	float angleDelta =  acos(  modelDirection.normalisedCopy().dotProduct( t ) );

	Vector3 posa = (*pTargetPosition - modelDirection);


	if( (int(angleDelta) != 0) ){

		if( angleDelta < 0 )
			this->getVechicle()->steerLeft();

		if(angleDelta > 0 )
			this->getVechicle()->steerRight();
	}else{
		int g = 0;
	}
	

	float distance = ( this->getVechicle()->getBody()->getNode()->getPosition() - ( *pTargetPosition) ).length();

	if( distance > 25 ){
		this->getVechicle()->accelerate();
	}else{
		mDataPointCount++;
		//this->getVechicle()->deaccelerate();
	}

	*/


}

void Ai::onKeyPress(OIS::Keyboard* pKeyBoard){

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

Vehicle* Ai::getVechicle(){
	return pCar;
}

void Ai::setTrack(Track * pTrack){
	this->pTrack = pTrack;
}
