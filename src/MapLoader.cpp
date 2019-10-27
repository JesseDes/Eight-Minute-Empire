#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include "MapLoader.h"
#include "map.h"
#include <map>

using namespace std;

MapLoader::MapLoader()
{
	fileName = new string("EmpireData.txt"); // default map
}

MapLoader::~MapLoader()
{
	for (auto i : maps)
	{
		delete i;
	}
	maps.clear();
	
	delete fileName;
	fileName = NULL;
}

list<int> MapLoader::readMapData(std::string file)
{
	ifstream File;
	File.open(file);

	int number;
	while (File >> number)
		data.push_back(number);
	
	return data;
}

// In case we need to create several map objects 
void MapLoader::createMaps(std::vector<std::list<int>> data)
{
	for(auto v: data)
	{
		EmpireMap map(v);

		if (map.isValid())
		{
			maps.push_back(new EmpireMap(v));
			cout << "map created successfully" << endl;
		}
		else
			cout << "bad map";
	}
}

 