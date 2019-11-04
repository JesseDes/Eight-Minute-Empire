#pragma once
#include <iostream>
#include <string>
#include "Good.h"
class Utils
{
	/*
		A utility class for Misc functions
	*/


public:
	//keeps prompting the user to enter a value between the range of min and max, otherwise it displays msg and and asks again until condition is met
	static int validInputRange(int min, int max, int value, std::string msg); //value must be between min and max
	static int validInputMin(int min, int value, std::string msg);	//value must be greater than or equal min
	static int validInputMax(int max, int value, std::string msg); // value must be less than or equal to max
};

