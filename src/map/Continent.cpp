#include "Continent.h"
#include "../core/GameLoop.h"
#include "MapLoader.h"

Continent::Continent(int contName, std::vector<int*> countries)
{
    _owner = nullptr;
    _continentName = new int(contName);
    this->_countries = countries;
}

int Continent::GetContinentName()
{
    return *_continentName;
}

Player * Continent::GetOwner()
{
    return _owner;
}

int Continent::GetTotalCountries(Player * player)
{
    int totalCountries = 0;
    for (auto v : _countries) {
        if (EmpireMap::instance()->country(*v)->GetOwner() == player) {
            totalCountries++;
        }
    }
    return totalCountries;
}

void Continent::UpdateOwner()
{
    std::vector<Player*> playerList = GameLoop::GetPlayerList();

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if (*it != _owner) {
            // if no owner is assigned, assign player
            if (_owner == nullptr)
                _owner = *it;
            // Replace owner with the player with most countries
            else if (GetTotalCountries(*it) > GetTotalCountries(_owner))
                _owner = *it;
            // Replace owner null if there is more than 1  player with equal number of countries
            else if (GetTotalCountries(*it) == GetTotalCountries(_owner)) {
                _owner = nullptr;
            }
        }
        //if nobody has any countries in the continent, owner is null
        else if (GetTotalCountries(*it) == 0) {
            _owner = nullptr;
        }
    }
}
