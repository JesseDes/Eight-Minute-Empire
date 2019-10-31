#include "pch.h"
#include<iostream>
#include <list>
#include <vector>
#include "Country.h"


using namespace std;

// ------ Country class -------


Country::Country()
{
    owner = new std::string("-");
}

void Country::writeOwner(string owner)
{
    *this->owner = owner;
}
string Country::getOwner()
{
    return *owner;
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