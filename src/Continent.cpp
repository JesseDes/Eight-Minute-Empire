#include "Continent.h"
#include "GameLoop.h"
#include "MapLoader.h"

Continent::Continent(int contName, std::vector<int*> countries)
{
    owner = nullptr;
    continentName = new int(contName);
    this->countries = countries;
}

int Continent::getContinentName()
{
    return *continentName;
}

Player * Continent::getOwner()
{
    return owner;
}

int Continent::getTotalCountries(Player * player)
{
    int totalCountries = 0;
    for (auto v : countries) {
        if (MapLoader::GetMap()->country(*v)->getOwner() == player) {
            totalCountries++;
        }
    }
    return totalCountries;
}

void Continent::updateOwner()
{
    std::vector<Player*> playerList = GameLoop::getPlayerList();

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        if (*it != owner) {
            // if no owner is assigned, assign player
            if (owner == nullptr)
                owner = *it;
            // Replace owner with the player with most countries
            else if (getTotalCountries(*it) > getTotalCountries(owner))
                owner = *it;
            // Replace owner null if there is more than 1  player with equal number of countries
            else if (getTotalCountries(*it) == getTotalCountries(owner)) {
                owner = nullptr;
            }
        }
        //if nobody has any countries in the continent, owner is null
        else if (getTotalCountries(*it) == 0) {
            owner = nullptr;
        }
    }
}
