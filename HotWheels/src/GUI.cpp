#include "stdafx.h"
#include "GUI.h"
#include "Settings.h"



GUI::GUI(Ogre::RenderWindow* window, OIS::Mouse* mouse):
	pTrayMgr(new OgreBites::SdkTrayManager("InterfaceName", window, mouse, this)),
	isMenuVisable(false)
{	
	 pLabel = pTrayMgr->createLabel(OgreBites::TL_CENTER, "mainmenu", "Main Meun", 500);
	 pNewGameBtn = pTrayMgr->createButton(OgreBites::TL_CENTER, "newgame", "Resume Game", 400);
	 pDebugBtn = pTrayMgr->createButton(OgreBites::TL_CENTER, "debug", "Debug Mode", 400);	 
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

void GUI::update(bool & mShutDownGame){

	 if(pQuitGameBtn->getState() == OgreBites::BS_DOWN){
		mShutDownGame = true;
	 }

	 if(pNewGameBtn->getState() == OgreBites::BS_DOWN){
		this->hide();
	 }

	 if(pDebugBtn->getState() == OgreBites::BS_DOWN){
		Settings::debugMode = true;
	 }

	 pQuitGameBtn->setCaption("Quit");
	 pNewGameBtn->setCaption("Resume Game");
	 pLabel->setCaption("Main Menu");
	 pDebugBtn->setCaption("Debug Mode");

}