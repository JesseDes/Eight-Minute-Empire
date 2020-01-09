#pragma once
#include <vector>
#include <list>
#include "Player.h"
#include "Country.h"

/*
    Handles the Creation of the map, via use of graphs for continent and subgraphs
*/

class Continent
{
public:

    Continent(int countryName, std::vector<int*> countries);
    int GetContinentName();
    void UpdateOwner(); //checks every country owner and updates continent owner with the user with the highest #countries
    Player* GetOwner(); // returns current owner of Continent
    int GetTotalCountries(Player * player); // returns current owner of Continent

private:
    Player* _owner;
    int* _continentName;
    std::vector<int*> _countries;
};