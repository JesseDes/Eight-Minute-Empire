#pragma once
#include "map.h"

/*
Parse Map files to create Map objects. Map objects will be able to determine if they are valid or not
*/

class MapLoader
{
public:
	static EmpireMap* FindMap();
    static EmpireMap* GetMap();
	static EmpireMap* readMapData(std::string file);

private:
    static EmpireMap *newMap;
};
