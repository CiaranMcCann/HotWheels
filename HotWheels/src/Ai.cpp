/**
 * @class	Ai
 *
 * @brief	Article intelligences.
 *
 * @author	Ciarán McCann
 */

#include "stdafx.h"
#include "Ai.h"

Ai::Ai(): mCurrentWayPiont(2), count(0)
{
  
}

Ai::~Ai(void)
{
}


void Ai::init(Critter::RenderSystem* render, Ogre::SceneManager* mSceneMgr){
	pCar = Vehicle::createVehicle("camaro",render,  mSceneMgr);

	NxOgreUtils::rotate(pCar->getBody(), Vector3(0,1,0), -45);
	pCar->getBody()->setGlobalPosition(Vector3(340.36890, 299.98193, -569.52747));	

	pCar->setMotorToqureMultplier(2.5);
	//pCar->setSteeringCoef(0.008f);
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


		

		if(Settings::debugMode && false){

			mSceneMgr->destroyAllManualObjects();
			{	
				ManualObject* manual =  mSceneMgr->createManualObject("manual");

				manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);
				manual->colour(0.2,0.0,1.0,1);
				Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );
				pos.y += 2;
				manual->position(pos);		
				manual->position(  Vector3( *pTargetPosition ) );
				manual->end();

				mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);
			}
		}

	
		destVector.y = 0;
		forwardDir.y = 0;
		float distance = destVector.length();

		forwardDir.normalise();
		destVector.normalise();
		
		if(Settings::debugMode && false){
	
			{
			ManualObject* manual =  mSceneMgr->createManualObject("manual2");
			manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);
			Vector3 pos = Vector3( this->getVechicle()->getBody()->getGlobalPosition().x, this->getVechicle()->getBody()->getGlobalPosition().y , this->getVechicle()->getBody()->getGlobalPosition().z );
			pos.y += 2;
			manual->position(pos );
			forwardDir *= 10.2;
			manual->position( (pos + forwardDir));
			manual->end();
			mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(manual);
			}
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

		Vec3 vTemp2 = getVechicle()->getBody()->getLocalPointVelocity(Vec3(10000,0,10000));
		Vector3 v2 = Vector3(vTemp2.x, 0, vTemp2.z);

		Vector3 wheelNormal = (this->getVechicle()->getWheel(3)->getNode()->getOrientation() * Ogre::Vector3(1,0,0)).normalisedCopy();
		wheelNormal = wheelNormal * xRotation;
		

		Utils::log(Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees());

		//Utils::drawLine( pos  , pos + (v.normalisedCopy()*v.length()), mSceneMgr );
		//Utils::drawLine( pos  , pos + (v2.normalisedCopy()*v2.length()), mSceneMgr );

			
		if( int(angle) > 8.0f){

				this->getVechicle()->steerLeft();
		}
		else if ( int(angle) < -8.0f) {

			Vec3 vTemp = getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100));
			Vector3 v = Vector3(vTemp.x, 0, vTemp.z);

			//if(Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() > 80 && Ogre::Degree( wheelNormal.angleBetween(v) ).valueDegrees() < 110 )
					this->getVechicle()->steerRight();

		}


		if( distance > 20 ){


			if( distance < 28 ){

				if( getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100)).magnitude() < 80
					&& getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,-100)).magnitude() < 80			
				)
				this->getVechicle()->accelerate();

			}else if ( distance < 23 ){


					if( getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100)).magnitude() < 70
						&& getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,-100)).magnitude() < 70			
						)
						this->getVechicle()->accelerate();

			}else{

					if( getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,100)).magnitude() < 100
					&& getVechicle()->getBody()->getLocalPointVelocity(Vec3(-100,0,-100)).magnitude() < 100	
				)
				this->getVechicle()->accelerate();
			}

		}else{

			mCurrentWayPiont += 5; // Moves AI to next waypoint
		
			//if(!pTrack->checkIfFinished(mCurrentWayPiont))
			//pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);

		}

	}else{
		
		//AI car has reached the finish line.
		if(this->getVechicle()->getBody()->getLinearVelocity().magnitude() > 2)
			this->getVechicle()->deaccelerate();

	}
}


Vehicle* Ai::getVechicle(){
	return pCar;
}

void Ai::setTrack(Track * pTrack){
	this->pTrack = pTrack;

	//if(!Track::trackingEnabled)
		//pTrack->getTrackNodeAt(mCurrentWayPiont)->scale(10,10,10);
}
