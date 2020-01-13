#pragma once
#include <iostream>
#include <string>
#include "../cards/Good.h"
class Utils
{
	/*
		A utility class for Misc functions
	*/


public:
	//keeps prompting the user to enter a value between the range of min and max, otherwise it displays msg and and asks again until condition is met
	static int ValidInputRange(int min, int max, std::string msg); //value must be between min and max
	static int ValidInputMin(int min, std::string msg);	//value must be greater than or equal min
	static int ValidInputMax(int max, std::string msg); // value must be less than or equal to max
	static void View(std::string output);
};

