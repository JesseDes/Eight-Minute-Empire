#pragma once
#include <vector>
#include <list>
#include "Country.h"


/*
    Handles the Creation of the map, via use of graphs for continent and subgraphs
*/

class Country
{
public:

    Continent(int continentName);
    Player* getOwner(); // returns current owner of continent
    int getContinentName();
    void updateOwner(); //checks who has the most contries 

private:
    Player* owner;
    std::map<Player*, int*> armies; //maps each player with their corresponding number of armies 
    std::map<Player*, int*> cities;//maps each player with their corresponding number of cities 
    int* countryName;
}; #pragma once
