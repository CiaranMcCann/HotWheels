#include "stdafx.h"
#include "GUI.h"


GUI::GUI(Ogre::RenderWindow* window, OIS::Mouse* mouse):
	pTrayMgr(new OgreBites::SdkTrayManager("InterfaceName", window, mouse, this)),
	isMenuVisable(true)
{	
	// pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
	 pLabel = pTrayMgr->createLabel(OgreBites::TL_CENTER, "mainmenu", "Main Meun", 500);
	 pNewGameBtn = pTrayMgr->createButton(OgreBites::TL_CENTER, "newgame", "New Game", 400);
	 pQuitGameBtn =  pTrayMgr->createButton(OgreBites::TL_CENTER, "quit", "Quit", 400);
}

bool GUI::isMenuShowing(){
	return isMenuVisable;
}

void GUI::show(){
	isMenuVisable = true;
	pTrayMgr->showAll();
	pTrayMgr->showCursor();
}


void GUI::hide(){
	isMenuVisable = false;
	pTrayMgr->hideAll();
	pTrayMgr->hideCursor();

}

GUI::~GUI(void)
{
	delete pTrayMgr;
	delete pNewGameBtn;
	delete pQuitGameBtn;
	delete pLabel;
}

OgreBites::SdkTrayManager* GUI::getTrayManager(){
	return pTrayMgr;
}

void GUI::update(){
	 pQuitGameBtn->setCaption("Quit");
	 pNewGameBtn->setCaption("New Game");
	 pLabel->setCaption("Main Menu");

	 OgreBites::Button * t = 0;

}