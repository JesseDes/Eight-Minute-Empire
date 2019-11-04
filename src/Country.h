#pragma once
#include <vector>
#include <list>
#include "Player.h"


/*
    Handles the Creation of the map, via use of graphs for continent and subgraphs
*/

class Country
{
public:

    Country(int countryName);
    int getCountryName();
    void updateOwner(); //checks every player and updates owner with the user with the highest # of units
    Player* getOwner(); // returns current owner of country
    void addArmy(Player* player); 
    void removeArmy(Player* player);
    int getArmy(Player* player);
    void addCity(Player* player);
    void removeCity(Player* player);
    int getCities(Player* player);
    int getTotalUnits(Player* player); //the sum of all army and cities

private:
    Player* owner;
    std::map<Player*,int*> armies; //maps each player with their corresponding number of armies 
    std::map<Player*, int*> cities;//maps each player with their corresponding number of cities 
    int* countryName;   
};