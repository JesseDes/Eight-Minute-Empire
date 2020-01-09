/*
Written by: Siamak Samie
*/
#pragma once
#include <list>
#include <vector>
#include "Country.h"
#include "Continent.h"

class InvalidMapException : public std::exception
{
	const char * error() const throw()
	{
		return "Map is invalid";
	}
};

class CurruptedMapException : public std::exception
{
	const char * error() const throw()
	{
		return "Map is currpt";
	}
};

class EmpireMap
{
public:

    static EmpireMap* instance(std::list<int> mapData, int start);
	static EmpireMap* instance() { return mapInstance; };
	~EmpireMap();

	int GetCountries(); // returns number of countries
	int getContinents(); // returns number of continents
	Country* country(int country);
    Continent* continent(int continent);
	bool IsLand(int a, int b); //verifies if two nodes are connected by land
	bool IsWater(int a, int b);  //verifies if two nodes are connected by water
	void DisplayContinents(); //displays the contents of each continent
	void DisplayIsLand();  // display all countries along with the countries they'ew adjacent to by land
	void DisplayIsWater();  // display all countries along with the countries they'ew adjacent to by water
	void DisplayAdjecent(); // display all countries along with the countries they'ew adjacent to by land and water
	void DisplayAdjecentContinents(); // display all continents and the continents they're adjacent to
	void DisplayMatrix(); //displays the adjacency matrix as is
	bool IsCountriesConnected(); // checks if countries are a connected subgraph
	bool IsContinentsConnected(); //checks if countinents are a connected subgraph
	bool IsNotDuplicated(); //check that no country is present in two continents
    Country* GetStartingCountry(); //returns starting country
    std::vector<int> GetAdjacentByLand(int country); //takes a country name (as an int) and returns adjacent by land country names (as int)
    std::vector<int> GetAdjacentByLandAndWater(int country);//takes a country name (as an int) and returns adjacent by land and water country names (as int)

private:

	EmpireMap(std::list<int> mapData, int start); // takes a weighted adjacency matrix as a list
    static EmpireMap* mapInstance;

	bool ContinentDFS(int start); //performs a depth first seach to check if continents are connected
	void CreateAdjacencyMatrix(std::list<int> mapData); //takes a list of ints to create an adjacency matrix
	void CreateContinentAdjacencyMatrix(); //created adjacency matrix of continents
	void FindContinentCountries(int start); //finds and pushes each new continents into a vector of vectors of ints called continentCountries 
    void CreateContinents(); //creates each continent
	void CreateCountries(); //pushes each new country in a vector of ints called countryContents
	void IsValid(); // calls the mathods that check if a map is valid - Countries connected, Continents connected, no duplicates

	int** _map; //the 2d map array of countries
	int** _continentMap; //the 2d map array of continents
	int* _countries; //number of countries (nodes)
	int* _continents; // number of groups of countries connected by land
    int* _startingCountry; //the country the initial troops get placed on
	std::vector<Country*> _countryContents; //each vector element represents a continent that holds a vector of countries
	std::vector<std::vector<int*>> _continentCountries; //each vector element hold a list of country names associated to a continent
    std::vector<Continent*> _continentContents; //each vector element represents a continent that holds a vector of countries
	std::vector<int*> _visited; //for the DFS (creating continents)
	std::vector<int*> _visitedContinents; //for the DFS (checking is connected subgraph)
	
};
