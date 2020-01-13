#include "../pch.h"
#include<iostream>
#include <list>
#include <vector>
#include "map.h"
#include "Country.h"

using namespace std;

// Global static pointer used to ensure a single instance of the class
EmpireMap* EmpireMap::mapInstance = NULL;

EmpireMap* EmpireMap::instance(list<int> mapData, int start) {
    if (mapInstance == NULL) {
		try
		{
			mapInstance = new EmpireMap(mapData, start);
			mapInstance->IsValid();
		}
		catch (CurruptedMapException e)
		{
			delete mapInstance;
			mapInstance = NULL;
			throw(e);
		}
		catch (InvalidMapException e)
		{
			delete mapInstance;
			mapInstance = NULL;
			throw(e);
		}
    }
    else 
        Utils::View("map instance was already created, returning  existing instance",false);
    
    return mapInstance;
}


EmpireMap::EmpireMap(list<int> mapData, int start)
{
	try
	{
		//creating weighted adjacency matrix
		CreateAdjacencyMatrix(mapData);

		//Initialising starting country
		_startingCountry = new int(start);

		//initializing continents to 0
		_continents = new int(0);

		//creating continents
		FindContinentCountries(0);
		CreateContinents();

		//creating continent adjacency matrix
		CreateContinentAdjacencyMatrix();

		//creating country objects
		CreateCountries();
	}
	catch (CurruptedMapException e)
	{
		throw(e);
	}
}

EmpireMap::~EmpireMap()
{
	for (int i = 0; i < *_countries; i++)
	{
		delete[] _map[i];
	}
	delete[] _map;

	for (auto i : _countryContents)
	{
		delete i;
	}
	_countryContents.clear();
	
	delete _countries;
	_countries = NULL;

	delete _continents;
	_continents = NULL;
}

void EmpireMap::CreateAdjacencyMatrix(std::list<int> mapData)
{
	// Setting size equal to the number of nodes (countries)
	//int nodes = sqrt(mapData.size());
	if (mapData.size() == 0)
	{
		CurruptedMapException e;
		throw(e);		
	}

	_countries = new int(sqrt(mapData.size()));

	// Creating our dynamic 2d array
	_map = new int* [*_countries];
	for (int i = 0; i < *_countries; ++i)
		_map[i] = new int[*_countries];

	// adding the list items into the 2d array
	list<int>::iterator it = mapData.begin();


	//creates the 2d matrix from the list data
	int i, j;
	for (i = 0; i < *_countries; i++) {
		for (j = 0; j < *_countries; j++) {
			_map[i][j] = *it;
			advance(it, 1);
		}
	}
}

void EmpireMap::CreateContinentAdjacencyMatrix()
{
	// Creating our dynamic 2d array
	_continentMap = new int* [*_continents];
	for (int i = 0; i <= *_continents; ++i)
		_continentMap[i] = new int[*_continents];


	//initialising all elements of array to 0
	int i, j;
	for (i = 0; i <= *_continents; i++) {
		for (j = 0; j <= *_continents; j++) {
			_continentMap[i][j] = 0;
		}
	}

	// getting all countries that are adjacent by water and checking which continents they belong to

	int continent1;
	int continent2;
	for (int i = 0; i < *_countries; i++) {
		for (int j = 0; j < *_countries; j++) {
			if (IsWater(i, j)) {

				for (auto k = 0; k <= *_continents; k++) {
					for (auto v : _continentCountries[k]) {
						if (*v == i)
							continent1 = k;
						if (*v == j)
							continent2 = k;
					}
				}

				_continentMap[continent1][continent2] = 1;
			}
		}
	}
}

void EmpireMap::CreateCountries()
{
	for (int i = 0; i <= *_countries; i++)
	{
		_countryContents.push_back(new Country(i));
	}
}

Country* EmpireMap::country(int country)
{
	return _countryContents[country];
}

Continent* EmpireMap::continent(int continent)
{
    return _continentContents[continent];
}

void EmpireMap::FindContinentCountries(int start) {

	for (int j = 0; j < *_countries; j++) {
		if (_map[start][j] == 1) {
            if (std::find_if(_visited.begin(), _visited.end(), [j](int* e) {return *e == j;}) == _visited.end())
			{
                _continentCountries.resize((*_continents) + 1);
				_visited.push_back(new int(j));
				_continentCountries[*_continents].push_back(new int(j));
				FindContinentCountries(j);
			}
		}
	}
    
    _visited.push_back(new int(start));

    // If this statements is true the we have just discovered a new continent
	if (_visited.size() < *_countries)
	{
		++(*_continents);
		for (int j = 0; j < *_countries; j++) {
            if (std::find_if(_visited.begin(), _visited.end(), [j](int* e) {return *e==j; }) == _visited.end())
			{
				FindContinentCountries(j);
			}
		}
	}
}

int EmpireMap::GetCountries()
{
	return *_countries;
}

int EmpireMap::getContinents()
{
	return (*_continents)+1; //because we start at 0
}

bool EmpireMap::IsLand(int a, int b)
{
	if (_map[a][b] == 1)
		return true;
	
	return false;
}

bool EmpireMap::IsWater(int a, int b)
{
	if (_map[a][b] == 2)
		return true;

	return false;
}

void EmpireMap::DisplayMatrix() {

	cout << "The Matrix";
	cout << endl;
	for (int i = 0; i < *_countries; i++) {
		for (int j = 0; j < *_countries; j++) {
			cout << _map[i][j] << " ";
		}
		cout << endl;
	}
}

void EmpireMap::DisplayAdjecent() {

	cout << "all adjancent (including by water)";
	cout << endl;
	for (int i = 0; i < *_countries; i++) {
		cout << i << " --> ";
		for (int j = 0; j < *_countries; j++) {
			if (_map[i][j] != 0) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

void EmpireMap::DisplayAdjecentContinents()
{
	cout << "all adjancent continents";
	cout << endl;
	for (int i = 0; i <= *_continents; i++) {
		cout << i << " --> ";
		for (int j = 0; j <= *_continents; j++) {
			if (_continentMap[i][j] != 0) {
				cout << j << " ";
			}
		}
		cout << endl;
	}
}

void EmpireMap::DisplayContinents() {

	for (auto i = 0; i <= *_continents; i++)
	{
		// print current vertex number
		cout << "continent " << i << " --> countries: ";

		for (auto v : _continentCountries[i])
			cout << *v << " ";
		cout << endl;
	}
}


void EmpireMap::CreateContinents() {

    for (auto i = 0; i <= *_continents; i++)
    {
        _continentContents.push_back(new Continent(i, _continentCountries[i]));
    }
}


void EmpireMap::DisplayIsWater() {

	cout << "adjacent by water";
	cout << endl;
	for (int i = 0; i < *_countries; i++) {
		for (int j = 0; j < *_countries; j++) {
			if (_map[i][j] == 2) {
				cout << i << " --> " << j;
				cout << endl;
			}
		}
	}
}

void EmpireMap::DisplayIsLand() {

	cout << "adjacent by land";
	cout << endl;
	for (int i = 0; i < *_countries; i++) {
		for (int j = 0; j < *_countries; j++) {
			if (_map[i][j] == 1) {
				cout << i << " --> " << j;
				cout << endl;
			}
		}
	}
}

bool EmpireMap::IsCountriesConnected() {

	//  checking if the map is a connected graph:
	//	If every number is connected to at least one other land by land or sea, it's a connected graph

	vector<vector<int>> adjacency(*_countries);
	
	for (int i = 0; i < *_countries; i++) {
		for (int j = 0; j < *_countries; j++) {
			if (_map[i][j] != 0) {
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


	for (int j = 0; j <= *_continents; j++) {
		if (_continentMap[start][j] == 1) {
            if (std::find_if(_visitedContinents.begin(), _visitedContinents.end(), [j](int* e) {return *e == j; }) == _visitedContinents.end())
            {
                _visitedContinents.push_back(new int(j));
                ContinentDFS(j);
            }
		}
	}

	// if the size of visited continents is less than the number of continents, it's not connected
	if (_visitedContinents.size() < *_continents)
		return false;

	return true;
}

bool EmpireMap::IsNotDuplicated() {

	// checking that there are no duplicate countries
	int visit;
	for (int i = 0; i < *_countries; i++) {
		visit = 0;
		for (int j = 0; j <= *_continents; j++) {
			for (auto v : _continentCountries[j]) {
				if (*v == i)
					visit++;
			}
		}
		if (visit != 1)
			return false;
	}
	return true;
}

void EmpireMap::IsValid() {

	if (!(IsNotDuplicated() && IsCountriesConnected() && IsContinentsConnected()))
	{
		InvalidMapException e;
		throw(e);
	}

}

Country* EmpireMap::GetStartingCountry()
{
    return _countryContents[*_startingCountry];
}

vector<int> EmpireMap::GetAdjacentByLand(int country)
{
    vector<int> adjacentCountries;
    cout << endl;
        for (int j = 0; j < *_countries; j++) {
            if (_map[country][j] == 1) {
                adjacentCountries.push_back(j);
            }
    }
    return adjacentCountries;
}

vector<int> EmpireMap::GetAdjacentByLandAndWater(int country)
{
    vector<int> adjacentCountries;
    cout << endl;
    for (int j = 0; j < *_countries; j++) {
        if (_map[country][j] > 0 ) {
            adjacentCountries.push_back(j);
        }
    }
    return adjacentCountries;
}