#include "../pch.h"
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
#include "../utils/Utils.h"
#include <stdio.h>

using namespace std;

void MapLoader::FindMap()
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

	selection = Utils::ValidInputRange(0, (fileCount - 1),  "You must choose a value between 0 and " + std::to_string((fileCount - 1)));

	std::cout << fileList[selection].cFileName << " Selected \n";
	
	ReadMapData(fileList[selection].cFileName);

}

void MapLoader::ReadMapData(std::string file)
{
	ifstream File;

	File.open("Assets/" + file);
	std::list<int> data;
    int start;
	int number;
	File >> start;
	while (File >> number)
		data.push_back(number);

	try
	{
		EmpireMap::instance(data, start);
	}
	catch (CurruptedMapException e)
	{
		cerr << "Map File: " + file + " is corrupted, deleting... \n";
		File.close();
		std::string filePath = "Assets/" + file;
		remove(filePath.c_str());
		throw(e);
	}
	catch (InvalidMapException e)
	{
		std::cout << "\n map is invalid\n\n";
		throw(e);
	}
		
}
