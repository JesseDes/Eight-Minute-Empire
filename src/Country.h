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
    static void addArmy(Player* player);
    static void removeArmy(Player* player);
    static int getArmy(Player* player);

private:
    static std::string* owner;
    static std::map<Player*,int*> armies;
};