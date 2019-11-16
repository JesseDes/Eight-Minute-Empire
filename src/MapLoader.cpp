#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <list>
#include "MapLoader.h"
#include "map.h"
#include <map>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include "Utils.h"

using namespace std;

EmpireMap* MapLoader::newMap;

EmpireMap* MapLoader::FindMap()
{
	HANDLE fileHandle;
	WIN32_FIND_DATAA fileData;
	int fileCount = 0;
	std::vector<WIN32_FIND_DATAA> fileList;
	fileHandle = FindFirstFileA("Assets/*.EMEMAP", &fileData);
	
	do
	{
		std::cout << "[" << fileCount++ << "] : " << fileData.cFileName << "\n";
		fileList.push_back(fileData);

	} while (FindNextFileA(fileHandle, &fileData));
	
	int selection;
	std::cout << "Which map would you like to use? \n";
	std::cin >> selection;
	selection = Utils::validInputRange(0, (fileCount - 1), selection, "You must choose a value between 0 and " + (fileCount - 1));

	std::cout << fileList[selection].cFileName << " Selected \n";
	
	return readMapData(fileList[selection].cFileName);

}

EmpireMap* MapLoader::readMapData(std::string file)
{
	ifstream File;

	File.open("Assets/" + file);
	std::list<int> data;
    int start;
	int number;

    File >> start;

	while (File >> number)
		data.push_back(number);
	
    newMap = EmpireMap::instance(data, start);

    //checking that map is valid: Is connected subgraph of countries and continents and no duplicates
    if (newMap->isValid()) {
        std::cout << "\nmap is valid\n\n";
        return newMap;
    }
    else {
        std::cout << "\nmap is invalid\n\n";
        system("pause");
        exit(0);
    }
}

EmpireMap* MapLoader::GetMap()
{
    return newMap;
}