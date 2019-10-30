#include "pch.h"
#include<iostream>
#include <list>
#include <vector>
#include "map.h"
#include "Country.h"

using namespace std;

// ------ EmpireMap Class -------

EmpireMap::EmpireMap(list<int> mapData)
{
	//creating weighted adjacency matrix
	createAdjacencyMatrix(mapData);

	//initializing continents to 0
	continents = new int(0);

	//creating continents
	createContinents(0);

	//creating continent adjacency matrix
	createContinentAdjacencyMatrix();
	
	//creating country objects
	createCountries();
}

EmpireMap::~EmpireMap()
{
	for (int i = 0; i < *countries; i++)
	{
		delete[] map[i];
	}
	delete[] map;

	for (auto i : countryContents)
	{
		delete i;
	}
	countryContents.clear();
	
	delete countries;
	countries = NULL;

	delete continents;
	continents = NULL;
}

void EmpireMap::createAdjacencyMatrix(std::list<int> mapData)
{
	// Setting size equal to the number of nodes (countries)
	//int nodes = sqrt(mapData.size());
	countries = new int(sqrt(mapData.size()));

	// Creating our dynamic 2d array
	map = new int* [*countries];
	for (int i = 0; i < *countries; ++i)
		map[i] = new int[*countries];

	// adding the list items into the 2d array
	list<int>::iterator it = mapData.begin();


	//creates the 2d matrix from the list data
	int i, j;
	for (i = 0; i < *countries; i++) {
		for (j = 0; j < *countries; j++) {
			map[i][j] = *it;
			advance(it, 1);
		}
	}
}

void EmpireMap::createContinentAdjacencyMatrix()
{
	// Creating our dynamic 2d array
	continentMap = new int* [*continents];
	for (int i = 0; i <= *continents; ++i)
		continentMap[i] = new int[*continents];


	//initialising all elements of array to 0
	int i, j;
	for (i = 0; i <= *continents; i++) {
		for (j = 0; j <= *continents; j++) {
			continentMap[i][j] = 0;
		}
	}

	// getting all countries that are adjacent by water and checking which continents they belong to

	int continent1;
	int continent2;
	for (int i = 0; i < *countries; i++) {
		for (int j = 0; j < *countries; j++) {
			if (isWater(i, j)) {

				for (auto k = 0; k <= *continents; k++) {
					for (auto v : continentContents[k]) {
						if (v == i)
							continent1 = k;
						if (v == j)
							continent2 = k;
					}
				}

				continentMap[continent1][continent2] = 1;
			}
		}
	}
}

void EmpireMap::createCountries()
{
	for (int i = 0; i <= *countries; i++)
	{
		countryContents.push_back(new Country());
	}
}

Country* EmpireMap::country(int country)
{
	return countryContents[country];
}

void EmpireMap::createContinents(int start) {

	continentContents.resize((*continents) + 1);

	for (int j = 0; j < *countries; j++) {
		if (map[start][j] == 1) {
			if (std::find(visited.begin(), visited.end(), j) == visited.end())
			{
				visited.push_back(j);
				continentContents[*continents].push_back(j);
				createContinents(j);
			}
		}
	}

	if (visited.size() < *countries)
	{
		++(*continents);
		for (int j = 0; j < *countries; j++) {
			if (std::find(visited.begin(), visited.end(), j) == visited.end())
			{
				createContinents(j);
			}
		}
	}
}

int EmpireMap::getCountries()
{
	return *countries;
}

int EmpireMap::getContinents()
{
	return (*continents)+1; //because we start at 0
}

bool EmpireMap::isLand(int a, int b)
{
	if (map[a][b] == 1)
		return true;
	
	return false;
}

bool EmpireMap::isWater(int a, int b)
{
	if (map[a][b] == 2)
		return true;

	return false;
}

void EmpireMap::displayMatrix() {

	cout << "The Matrix";
	cout << endl;
	for (int i = 0; i < *countries; i++) {
		for (int j = 0; j < *countries; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

void EmpireMap::displayAdjecent() {

	cout << "all adjancent (including by water)";
	cout << endl;
	for (int i = 0; i < *countries; i++) {
		cout << i << " --> ";
		for (int j = 0; j < *countries; j++) {
			if (map[i][j] != 0) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

void EmpireMap::displayAdjecentContinents()
{
	cout << "all adjancent continents";
	cout << endl;
	for (int i = 0; i <= *continents; i++) {
		cout << i << " --> ";
		for (int j = 0; j <= *continents; j++) {
			if (continentMap[i][j] != 0) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

void EmpireMap::displayContinents() {

	for (auto i = 0; i <= *continents; i++)
	{
		// print current vertex number
		cout << "continent " << i << " --> countries: ";

		for (auto v : continentContents[i])
			cout << v << " ";
		cout << endl;
	}
}

void EmpireMap::displayIsWater() {

	cout << "adjacent by water";
	cout << endl;
	for (int i = 0; i < *countries; i++) {
		for (int j = 0; j < *countries; j++) {
			if (map[i][j] == 2) {
				cout << i << " --> " << j;
				cout << endl;
			}
		}
	}
}

void EmpireMap::displayIsLand() {

	cout << "adjacent by land";
	cout << endl;
	for (int i = 0; i < *countries; i++) {
		for (int j = 0; j < *countries; j++) {
			if (map[i][j] == 1) {
				cout << i << " --> " << j;
				cout << endl;
			}
		}
	}
}

bool EmpireMap::IsCountriesConnected() {

	//  checking if the map is a connected graph:
	//	If every number is connected to at least one other land by land or sea, it's a connected graph

	vector<vector<int>> adjacency(*countries);
	
	for (int i = 0; i < *countries; i++) {
		for (int j = 0; j < *countries; j++) {
			if (map[i][j] != 0) {
				adjacency[i].push_back(j);
			}
		}
		if (adjacency[i].empty())
			return false;
	}

	return true;
}

bool EmpireMap::IsContinentsConnected() {

	//if every continent can be visited from continent 0, then it's connected
	return ContinentDFS(0);
}

bool EmpireMap::ContinentDFS(int start) {


	for (int j = 0; j <= *continents; j++) {
		if (continentMap[start][j] == 1) {
            if (std::find(visitedContinents.begin(), visitedContinents.end(), j) == visitedContinents.end())
            {
                visitedContinents.push_back(j);
                ContinentDFS(j);
            }
		}
	}

	// if the size of visited continents is less than the number of continents, it's not connected
	if (visitedContinents.size() < *continents)
		return false;

	return true;
}

bool EmpireMap::isNotDuplicated() {

	// checking that there are no duplicate countries
	int visit;
	for (int i = 0; i < *countries; i++) {
		visit = 0;
		for (int j = 0; j <= *continents; j++) {
			for (auto v : continentContents[j]) {
				if (v == i)
					visit++;
			}
		}
		if (visit != 1)
			return false;
	}
	return true;
}

bool EmpireMap::isValid() {

	if (isNotDuplicated()&&IsCountriesConnected()&&IsContinentsConnected())
		return true;
	return false;
}