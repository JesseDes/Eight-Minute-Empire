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

private:
    std::string* owner;
    std::map<Player*,int*> armies;
};