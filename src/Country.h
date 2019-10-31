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

    Country();
    void writeOwner(std::string owner);
    std::string getOwner();
    void addArmy(Player* player);
    void removeArmy(Player* player);
    int getArmy(Player* player);
    void addCity(Player* player);
    void removeCity(Player* player);
    int getCities(Player* player);
    int getTotalUnits(Player* player); //the sum of all army and cities

private:
    std::string* owner;
    std::map<Player*,int*> armies;
    std::map<Player*, int*> cities;
};