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
	static int validInputRange(int min, int max, int value, std::string msg);
	static int validInputMin(int min, int value, std::string msg);
	static int validInputMax(int max, int value, std::string msg);
};

