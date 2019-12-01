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

	int getCountries(); // returns number of countries
	int getContinents(); // returns number of continents
	Country* country(int country);
    Continent* continent(int continent);
	bool isLand(int a, int b); //verifies if two nodes are connected by land
	bool isWater(int a, int b);  //verifies if two nodes are connected by water
	void displayContinents(); //displays the contents of each continent
	void displayIsLand();  // display all countries along with the countries they'ew adjacent to by land
	void displayIsWater();  // display all countries along with the countries they'ew adjacent to by water
	void displayAdjecent(); // display all countries along with the countries they'ew adjacent to by land and water
	void displayAdjecentContinents(); // display all continents and the continents they're adjacent to
	void displayMatrix(); //displays the adjacency matrix as is
	bool IsCountriesConnected(); // checks if countries are a connected subgraph
	bool IsContinentsConnected(); //checks if countinents are a connected subgraph
	bool isNotDuplicated(); //check that no country is present in two continents
    Country* getStartingCountry(); //returns starting country
    std::vector<int> getAdjacentByLand(int country); //takes a country name (as an int) and returns adjacent by land country names (as int)
    std::vector<int> getAdjacentByLandAndWater(int country);//takes a country name (as an int) and returns adjacent by land and water country names (as int)

private:

	EmpireMap(std::list<int> mapData, int start); // takes a weighted adjacency matrix as a list
    static EmpireMap* mapInstance;

	bool ContinentDFS(int start); //performs a depth first seach to check if continents are connected
	void createAdjacencyMatrix(std::list<int> mapData); //takes a list of ints to create an adjacency matrix
	void createContinentAdjacencyMatrix(); //created adjacency matrix of continents
	void findContinentCountries(int start); //finds and pushes each new continents into a vector of vectors of ints called continentCountries 
    void createContinents(); //creates each continent
	void createCountries(); //pushes each new country in a vector of ints called countryContents
	void isValid(); // calls the mathods that check if a map is valid - Countries connected, Continents connected, no duplicates

	int** map; //the 2d map array of countries
	int** continentMap; //the 2d map array of continents
	int* countries; //number of countries (nodes)
	int* continents; // number of groups of countries connected by land
    int* startingCountry; //the country the initial troops get placed on
	std::vector<Country*> countryContents; //each vector element represents a continent that holds a vector of countries
	std::vector<std::vector<int*>> continentCountries; //each vector element hold a list of country names associated to a continent
    std::vector<Continent*> continentContents; //each vector element represents a continent that holds a vector of countries
	std::vector<int*> visited; //for the DFS (creating continents)
	std::vector<int*> visitedContinents; //for the DFS (checking is connected subgraph)
	
};
