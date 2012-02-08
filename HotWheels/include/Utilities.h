#include "stdafx.h"
#pragma once

using namespace std;

namespace Utils {


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