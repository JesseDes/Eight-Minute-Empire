#pragma once
#include "map.h"

/*
Parse Map files to create Map objects. Map objects will be able to determine if they are valid or not
*/

class MapLoader
{
public:
	MapLoader();
	~MapLoader();
	void createMaps(std::vector<std::list<int>> data);
	std::list<int> readMapData(std::string file);
	int getNumberOfElements();
private:
	std::string* fileName;
	int* numberOfElements;
	std::list<int> data;
	std::vector<EmpireMap*> maps;
};
