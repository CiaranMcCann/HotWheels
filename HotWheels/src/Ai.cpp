#include "stdafx.h"
#include "Ai.h"


Ai::Ai(): mCurrentWayPiont(10), a(0)
{
 
}

Ai::~Ai(void)
{
}


void Ai::init(Critter::RenderSystem* render, Ogre::SceneManager* mSceneMgr){
	pCar = Vehicle::createVehicle("camaro",render,  mSceneMgr);
	pCar->getBody()->setGlobalPosition(Vector3(350.36890, 299.98193, -569.52747));	
	this->mSceneMgr = mSceneMgr;

}

void Ai::update(float timeDelta){

	pTargetPosition = pTrack->getTrackDataPiontAt(mCurrentWayPiont);


	//Vector3 forwardDir =  getVechicle()->getBody()->getNode()->getOrientation() *  Vector3( 1, 0,1 );

	

	//NxOgre::Matrix33  m = ;
	NxOgre::Quat q = getVechicle()->getBody()->getGlobalOrientationQuat();

	//Ogre::Quaterion quat(q.w, q.x. q.y, q.z);

	Vector3 target = Vector3( *pTargetPosition );
	 target.y =0;

	Vector3 forwardDir =  Ogre::Quaternion(q.w, q.x, q.y, q.z) *  Vector3( 1, 0,1 );

	Vector3 destVector =  target -  Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, 0 , this->getVechicle()->getBody()->getGlobalPosition().z );

	float distance = destVector.length();

	OutputDebugString( " Ogre Quat " );
	OutputDebugString( Utils::toString(getVechicle()->getBody()->getNode()->getOrientation()).c_str() );
	OutputDebugString( "\n" );


	OutputDebugString( " NxOgre Quat " );
	OutputDebugString( Utils::toString(getVechicle()->getBody()->getGlobalOrientation()).c_str() );
	OutputDebugString( "\n" );


	// create ManualObject

	mSceneMgr->destroyAllManualObjects();

	{

	
		ManualObject* manual =  mSceneMgr->createManualObject("manual");


		// specify the material (by name) and rendering type
		
		manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);
		manual->colour(0.2,0.0,1.0,1);
		// define start and end point
		Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );
		pos.y += 2;
		manual->position(pos);
		destVector.y += 2;
		manual->position(destVector);

		// tell Ogre, your definition has finished
		manual->end();

		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

	}

	forwardDir.normalise();
	destVector.normalise();
	destVector.y = 0;
	forwardDir.y = 0;
	

	{


		ManualObject* manual =  mSceneMgr->createManualObject("manual2");


		// specify the material (by name) and rendering type
		manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);

		// define start and end point
		Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );
		pos.y += 2;
		manual->position(pos );

		forwardDir *= 10.2;
		manual->position(pos + forwardDir);


		// tell Ogre, your definition has finished
		manual->end();

		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

	}





	// add ManualObject to the RootSceneNode (so it will be visible)
	//mSceneMgr->getRootSceneNode()->attachObject(manual);


	//forwardDir *= -1;




	float angle =  Ogre::Degree( destVector.angleBetween( Ogre::Vector3( forwardDir.x , forwardDir.y , forwardDir.z )) ).valueAngleUnits();
	

	if( angle > 0){
		angle -= 40;
	}else{
		angle += 40;
	}

	OutputDebugString( "Actually Angle " );
	OutputDebugString( Utils::toString(angle).c_str() );
	OutputDebugString( "\n" );
	OutputDebugString( " Distance " );
	OutputDebugString( Utils::toString(distance).c_str() );
	OutputDebugString( "\n" );




	if( int(angle) > 10.0f ){
		
	//	if(getVechicle()->getWheel(3)->getWheel()->getAxleSpeed() < 25)
		
			this->getVechicle()->steerLeft();

	}
	else if ( int(angle) < -10.0f) {

	//	if(getVechicle()->getWheel(3)->getWheel()->getAxleSpeed() < 25)
			this->getVechicle()->steerRight();
	
	}


	if( distance > 10 ){

		if(getVechicle()->getBody()->getLinearVelocity().magnitude() < 12)
			this->getVechicle()->accelerate();

	}else{

		//a = -99999;
		mCurrentWayPiont += 12;
		pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);
		
		this->getVechicle()->deaccelerate();
	}

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
		pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);
}
