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
    // if no army is found for the given player, we return 0 
    if (armies.find(player) == armies.end()) {
        return 0;
    }
    else
        return *armies[player];
}

void Country::addArmy(Player* player)
{
    // if no army is found for the given player, we return we initialise it to 1
    if (armies.find(player) == armies.end()) {
        armies[player] = new int(1);
    }
    else
        (*armies[player])++;
}

void Country::removeArmy(Player* player)
{
    (*armies[player])--;
	player->DrawArmyPiece();
}

int Country::getCities(Player* player)
{
    // if no city is found for the given player, we return we return 0
    if (cities.find(player) == cities.end()) {
        return 0;
    }
    else
        return *cities[player];
}

void Country::addCity(Player* player)
{
    // if no city is found for the given player, we return we initialise it to 1
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
    //std::vector<Player*> playerList = GameLoop::getPlayerList(); BAD
	std::vector<Player*> playerList;

	for (std::map<Player*, int*>::iterator it = armies.begin(); it != armies.end(); it++)
		playerList.push_back(it->first);
	for (std::map<Player*, int*>::iterator it = cities.begin(); it != cities.end(); it++)
	{
		if(std::find(playerList.begin(), playerList.end(), it->first) != playerList.end())
			playerList.push_back(it->first);
	}

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if (*it != owner) {
            // if no owner is assigned, assign player
            if (owner == nullptr)
                owner = *it;
            // Replace owner with the player with most units
            else if (getTotalUnits(*it) > getTotalUnits(owner))
                owner = *it;
            // Replace owner null if there is more than 1  player with equal number of units
            else if (getTotalUnits(*it) == getTotalUnits(owner)) {
                owner = nullptr;
            }
        }
		//if no units owner is null
		else if (getTotalUnits(*it) == 0 ) {
			owner = nullptr;
		}
    }

	if (owner != nullptr)
		std::cout << "OWNER OF " << *countryName << " IS " << owner->getPlayerName() << " \n";
	else
		std::cout << "OWNER OF " << *countryName << " IS NOBODY \n";

}

