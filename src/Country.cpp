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

int Country::getArmy()
{
    return armies[0];
}

int Country::addArmy()
{
    return armies[0];
}

int Country::removeArmy()
{
    return armies[0]; //not sure how we'll implement this
}