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
    int getContinentName();
    void updateOwner(); //checks every country owner and updates continent owner with the user with the highest #countries
    Player* getOwner(); // returns current owner of Continent
    int getTotalCountries(Player * player); // returns current owner of Continent

private:
    Player* owner;
    int* continentName;
    std::vector<int*> countries;
};