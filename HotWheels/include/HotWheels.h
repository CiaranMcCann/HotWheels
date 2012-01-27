/*
-----------------------------------------------------------------------------
Filename:    HotWheels.h
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC10 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/
#ifndef __HotWheels_h_
#define __HotWheels_h_

#include "stdafx.h"
#include "Vehicle.h"
#include "Player.h"
#include "Track.h"
#include "Ai.h"


#include "BaseApplication.h"
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif

using namespace Ogre;
using namespace NxOgre;

class HotWheels : public BaseApplication
{
public:
	Player mPlayer;
	Ai mAi;
	Track mTrack;

    HotWheels(void);
    virtual ~HotWheels(void);
	//bool frameRenderingQueued(const Ogre::FrameEvent& evt);

protected:	

	 bool keyPressed( const OIS::KeyEvent &arg );
	 bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	//PhysX
	void createScene();


};

#endif // #ifndef __HotWheels_h_