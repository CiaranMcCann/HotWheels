#pragma once
#include "fmod.hpp" //fmod c++ header
#pragma comment( lib, "fmodex_vc.lib" ) // fmod library
#include "stdafx.h"
using namespace std;
using namespace FMOD;


class SoundManager
{
private:	
	FMOD::System     *system; //handle to FMOD engine
	std::map<string,Sound *> sounds;
	static SoundManager * pInstance;

	SoundManager(void);

public:

	void loadSound(const char * url, string referenceName, bool loop = false);
	void play(string referenceName);
	void update();

	static SoundManager * getInstance();
	~SoundManager(void);
};
