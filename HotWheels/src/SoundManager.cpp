#include "stdafx.h"

#include "SoundManager.h"

SoundManager * SoundManager::pInstance = 0;

SoundManager::SoundManager(void){
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

void SoundManager::loadSound(const char * url, string referenceName, bool loop){
/*	
   FMOD::Sound * temp2;
   FMOD::Sound * temp;	
   system->createSound(url, FMOD_HARDWARE, 0, &temp); 
   system->createSound("", FMOD_HARDWARE, 0, &temp2); //hack

  if(temp != temp2){
  
	  if(!loop)
		temp->setMode(FMOD_LOOP_OFF);

	   sounds.insert(pair<string,FMOD::Sound *>(referenceName, temp));
  }

  */
}

void SoundManager::play(string referenceName){
/*
	if(false){

		FMOD::Sound * temp = sounds.find(referenceName)->second;

		int * hhss = 0 ;
		temp->getLoopCount(hhss);


		system->playSound(FMOD_CHANNEL_FREE, temp , false, 0);
	}
	*/
}

void SoundManager::update(){
	system->update();
}


SoundManager * SoundManager::getInstance(){
	if(pInstance == 0)
		pInstance = new SoundManager();

	return pInstance;
}

SoundManager::~SoundManager(void){
	delete pInstance;
}

