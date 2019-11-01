#include "pch.h"
#include<iostream>
#include <list>
#include <vector>
#include "Country.h"
#include "GameLoop.h"

using namespace std;

// ------ Country class -------


Country::Country(int cname)
{
    owner = nullptr;
    countryName = new int(cname);
}

int Country::getCountryName()
{
    return *countryName;
}

Player* Country::getOwner()
{
    return owner;
}

int Country::getArmy(Player* player)
{
    if (armies.find(player) == armies.end()) {
        return 0;
    }
    else
        return *armies[player];
}

void Country::addArmy(Player* player)
{
    if (armies.find(player) == armies.end()) {
        armies[player] = new int(1);
    }
    else
        (*armies[player])++;
}

void Country::removeArmy(Player* player)
{
    (*armies[player])--;
}

int Country::getCities(Player* player)
{
    if (cities.find(player) == cities.end()) {
        return 0;
    }
    else
        return *cities[player];
}

void Country::addCity(Player* player)
{
    if (cities.find(player) == cities.end()) {
        cities[player] = new int(1);
    }
    else
        (*cities[player])++;
}

void Country::removeCity(Player* player)
{
    (*cities[player])--;
}

int Country::getTotalUnits(Player * player)
{
    return getArmy(player)+getCities(player);
}

void Country::updateOwner()
{
    std::vector<Player*> playerList = GameLoop::getPlayerList();

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        // if no owner is assigned, assign player
        if (owner == nullptr)
            owner = *it;
        // Replace owner with the player with most units
        else if (this->getTotalUnits(*it) > this->getTotalUnits(owner))
            owner = nullptr;
        // Replace owner null if there is more than 1  player with equal number of units
        else if (this->getTotalUnits(*it) > this->getTotalUnits(owner)) {
            owner = *it;
        }
    }
}

