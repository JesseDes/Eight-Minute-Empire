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
	//fileName = new string("EmpireData.txt"); // default map
	HANDLE fileHandle;
	WIN32_FIND_DATAA fileData;
	int fileCount = 0;
	std::vector<WIN32_FIND_DATAA> fileList;
	fileHandle = FindFirstFileA("Assets/*.txt", &fileData);

	/*if (INVALID_HANDLE_VALUE == fileHandle)
	{
		std::cout << "Storage ERROR exiting game";
		return NULL;
	}*/
	
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
	
	newMap = new EmpireMap(data, start);
	//std::cout << newMap.isValid();
	return newMap;
}

EmpireMap* MapLoader::GetMap()
{
    return newMap;
}