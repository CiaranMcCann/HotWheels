#include "stdafx.h"
#include "Ai.h"


Ai::Ai(): mCurrentWayPiont(10), count(0)
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
	

	if(!pTrack->checkIfFinished(mCurrentWayPiont)){

		pTargetPosition = pTrack->getTrackDataPiontAt(mCurrentWayPiont);


		//Vector3 forwardDir =  getVechicle()->getBody()->getNode()->getOrientation() *  Vector3( 1, 0,1 );

	

		//NxOgre::Matrix33  m = ;
		NxOgre::Quat q = getVechicle()->getBody()->getGlobalOrientationQuat();

		//Ogre::Quaterion quat(q.w, q.x. q.y, q.z);

		Vector3 target = Vector3( *pTargetPosition );
		target.y = 0;

		Vector3 forwardDir =  Ogre::Quaternion(q.w, q.x, q.y, q.z) *  Vector3( 1, 0,1 );

		Vector3 destVector =  target -  Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, 0 , this->getVechicle()->getBody()->getGlobalPosition().z );

		Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );




		

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


		
			manual->position(  Vector3( *pTargetPosition ) );

			// tell Ogre, your definition has finished
			manual->end();

			mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

		}

		

	
		destVector.y = 0;
		forwardDir.y = 0;
		float distance = destVector.length();

		forwardDir.normalise();
		destVector.normalise();
	
	
		{


			ManualObject* manual =  mSceneMgr->createManualObject("manual2");


			// specify the material (by name) and rendering type
			manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);

			// define start and end point
			Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );
			pos.y += 2;
			manual->position(pos );

	


			forwardDir *= 10.2;
			manual->position( (pos + forwardDir));


			// tell Ogre, your definition has finished
			manual->end();

			mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

		}


	

		// add ManualObject to the RootSceneNode (so it will be visible)
		//mSceneMgr->getRootSceneNode()->attachObject(manual);


		//forwardDir *= -1;




		float angle =  Ogre::Degree( destVector.angleBetween( Ogre::Vector3( forwardDir.x , 0 , forwardDir.z )) ).valueAngleUnits();
	

		if( angle > 0){
			angle -= 41;
		}else{
			angle += 41;
		}


		// 100 / by large number gives smaller  number

		Ogre::Matrix3 xRotation;
		xRotation.FromAxisAngle(Ogre::Vector3(0,1,0), Ogre::Radian(45));


		Vec3 vTemp = getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,-100));
		Vector3 v = Vector3(vTemp.x, 0, vTemp.z);
		Vector3 wheelNormal = (this->getVechicle()->getWheel(3)->getNode()->getOrientation() * Ogre::Vector3(1,0,0)).normalisedCopy();
		wheelNormal = wheelNormal * xRotation;
		

		Utils::log(Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees());
		Utils::drawLine( pos  , pos + (v*v.length()), mSceneMgr );

			
		if( int(angle) > 1.0f ){

			

			//if(Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() > 80 && Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() < 110 )
				this->getVechicle()->steerLeft();
		}
		else if ( int(angle) < -1.0f) {

			Vec3 vTemp = getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100));
			Vector3 v = Vector3(vTemp.x, 0, vTemp.z);

			//if(Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() > 80 && Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() < 110 )
					this->getVechicle()->steerRight();

		}


		if( distance > 10 ){

			//if(getVechicle()->getBody()->getLinearVelocity().magnitude() < 6)


			//Utils::log( getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,200,-100)).magnitude() );

			if( getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100)).magnitude() < 20
				&& getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,-100)).magnitude() < 20
				
				)
				this->getVechicle()->accelerate();

		}else{

			//a = -99999;
			mCurrentWayPiont += 3;
		
			if(!pTrack->checkIfFinished(mCurrentWayPiont))
			pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);

		}

	}else{

		if(this->getVechicle()->getBody()->getLinearVelocity().magnitude() > 2)
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
	if(!Track::trackingEnabled)
		pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);
}
