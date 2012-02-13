#include "stdafx.h"
#pragma once

using namespace std;


namespace NxOgreUtils{

	template<typename T> //hack as I get a linker error if I don't have this???
	void rotate(Critter::Body* body, Vector3 axiesOfRoatation, T degree ){

		Ogre::Matrix3 xRotation;
		xRotation.FromAxisAngle(axiesOfRoatation, Ogre::Degree(degree));

		Ogre::Quaternion quat;
		quat.FromRotationMatrix(xRotation);

		Vec4 v;
		v.set(quat.w, quat.x, quat.y, quat.z);
		body->setGlobalOrientationQuat(v);

	}
}

namespace Utils {

	static int lineCount = 0;

		
	template<typename T> //hack as I get a linker error if I don't have this???
	int drawLine(T & pos1, T & pos2, SceneManager *  mSceneManager){

		lineCount++;

		ManualObject* manual =  mSceneManager->createManualObject("drawLine" + Utils::toString(lineCount));
		manual->begin("BeachStones", RenderOperation::OT_LINE_STRIP);	
		manual->position(pos1);
		manual->position(pos2);
		manual->end();
		mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(manual);

		return lineCount;
	}


	template<typename T>
	float toDegree(T radians){
		return radians * (180/3.14);
	}


	template<typename T>
	std::string toString(T numberToConvert){

		std::stringstream ss;
		ss << numberToConvert;

		return ss.str();
	}

	template<typename T>
	void logMessage(T objectToPrint){
		_cprintf( (toString(objectToPrint)+"\n").c_str() );
	}

	template<typename T>
	void log(T objectToPrint){
		OutputDebugString( (toString(objectToPrint)+"\n").c_str() );
	}


	template<typename T> //hack as I get a linker error if I don't have this???
	void split(const T& str, const string& delimiters , std::vector<string>& tokens)
	{
		// Skip delimiters at beginning.
		string::size_type lastPos = str.find_first_not_of(delimiters, 0);
		// Find first "non-delimiter".
		string::size_type pos     = str.find_first_of(delimiters, lastPos);

		while (string::npos != pos || string::npos != lastPos)
		{
			// Found a token, add it to the vector.
			tokens.push_back(str.substr(lastPos, pos - lastPos));
			// Skip delimiters.  Note the "not_of"
			lastPos = str.find_first_not_of(delimiters, pos);
			// Find next "non-delimiter"
			pos = str.find_first_of(delimiters, lastPos);
		}
	}

	

	

}