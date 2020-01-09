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
    int GetCountryName();
    void UpdateOwner(); //checks every player and updates owner with the user with the highest # of units
    Player* GetOwner(); // returns current owner of country
    void AddArmy(Player* player); 
    void RemoveArmy(Player* player);
    int GetArmy(Player* player);
    void AddCity(Player* player);
    void RemoveCity(Player* player);
    int GetCities(Player* player);
    int GetTotalUnits(Player* player); //the sum of all army and cities

private:
    Player* _owner;
    std::map<Player*,int*> _armies; //maps each player with their corresponding number of armies 
    std::map<Player*, int*> _cities;//maps each player with their corresponding number of cities 
    int* _countryName;   
};