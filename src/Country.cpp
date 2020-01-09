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
    _owner = nullptr;
    _countryName = new int(cname);
}

int Country::GetCountryName()
{
    return *_countryName;
}

Player* Country::GetOwner()
{
    return _owner;
}

int Country::GetArmy(Player* player)
{
    // if no army is found for the given player, we return 0 
    if (_armies.find(player) == _armies.end()) {
        return 0;
    }
    else
        return *_armies[player];
}

void Country::AddArmy(Player* player)
{
    // if no army is found for the given player, we return we initialise it to 1
    if (_armies.find(player) == _armies.end()) {
        _armies[player] = new int(1);
    }
    else
        (*_armies[player])++;
}

void Country::RemoveArmy(Player* player)
{
    (*_armies[player])--;
	player->DrawArmyPiece();
}

int Country::GetCities(Player* player)
{
    // if no city is found for the given player, we return we return 0
    if (_cities.find(player) == _cities.end()) {
        return 0;
    }
    else
        return *_cities[player];
}

void Country::AddCity(Player* player)
{
    // if no city is found for the given player, we return we initialise it to 1
    if (_cities.find(player) == _cities.end()) {
        _cities[player] = new int(1);
    }
    else
        (*_cities[player])++;
}

void Country::RemoveCity(Player* player)
{
    (*_cities[player])--;
}

int Country::GetTotalUnits(Player * player)
{
    return GetArmy(player)+GetCities(player);
}

void Country::UpdateOwner()
{
    //std::vector<Player*> playerList = GameLoop::getPlayerList(); BAD
	std::vector<Player*> playerList;

	for (std::map<Player*, int*>::iterator it = _armies.begin(); it != _armies.end(); it++)
		playerList.push_back(it->first);
	for (std::map<Player*, int*>::iterator it = _cities.begin(); it != _cities.end(); it++)
	{
		if(std::find(playerList.begin(), playerList.end(), it->first) != playerList.end())
			playerList.push_back(it->first);
	}

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if (*it != _owner) {
            // if no owner is assigned, assign player
            if (_owner == nullptr)
                _owner = *it;
            // Replace owner with the player with most units
            else if (GetTotalUnits(*it) > GetTotalUnits(_owner))
                _owner = *it;
            // Replace owner null if there is more than 1  player with equal number of units
            else if (GetTotalUnits(*it) == GetTotalUnits(_owner)) {
                _owner = nullptr;
            }
        }
		//if no units owner is null
		else if (GetTotalUnits(*it) == 0 ) {
			_owner = nullptr;
		}
    }

	if (_owner != nullptr)
		std::cout << "OWNER OF " << *_countryName << " IS " << _owner->GetPlayerName() << " \n";
	else
		std::cout << "OWNER OF " << *_countryName << " IS NOBODY \n";

}

