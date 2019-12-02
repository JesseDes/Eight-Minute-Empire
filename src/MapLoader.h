#pragma once
#include "map.h"

/*
Parse Map files to create Map objects. Map objects will be able to determine if they are valid or not
*/

class MapLoader
{
public:
	static void FindMap();	//prompts user to select a map file in the Assets folder
	static void readMapData(std::string file); //reads a map file and returns a map object

};
