#pragma once
#include "stdafx.h"


class GUI : OgreBites::SdkTrayListener
{
public:
	GUI(Ogre::RenderWindow*, OIS::Mouse*);
	~GUI(void);

	void update(bool & mShutDownGame);
	OgreBites::SdkTrayManager* getTrayManager();
	bool isMenuShowing();
	void show();
	void hide();



private:

	bool isMenuVisable;

	OgreBites::SdkTrayManager* pTrayMgr;
	OgreBites::Button* pNewGameBtn;
	OgreBites::Button* pQuitGameBtn;
	OgreBites::Button* pDebugBtn;
	OgreBites::Label* pLabel;


};

