#pragma once
#include "stdafx.h"

class Settings 
{
	public:
		static bool debugMode;
};

/************************************************************************/
/* ASK ROSS - I defined the static member in the header file and linker didn't like it, unknown as to why                                                                     */
/************************************************************************/

//bool Settings::debugMode = false;