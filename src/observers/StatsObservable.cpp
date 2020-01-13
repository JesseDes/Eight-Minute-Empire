#include "StatsObservable.h"

StatsObservable::StatsObservable() : Subject()
{
	
}

StatsObservable::~StatsObservable()
{
	_goodMap = NULL;	//No deleting. Is shallow copy
	_countryList = NULL; 
	_currentPlayer = NULL;
}

void StatsObservable::SetPlayer(Player *player)
{
	_currentPlayer = player;
}

void StatsObservable::UpdateCountries(std::vector<int> *list)
{
	_currentState = StatsState::Country;
	_countryList = list;
	Notify();

}

void StatsObservable::UpdatePlayerGoods(std::map<GoodType, int*> *good)
{
	_currentState = StatsState::Good;
	_goodMap = good;
	Notify();
}

std::vector<int>* StatsObservable::GetCountryList()
{
	return _countryList;
}

std::map<GoodType, int*>* StatsObservable::GetGoodsMap()
{
	return _goodMap;
}

StatsState StatsObservable::GetState()
{
	return _currentState;
}

Player* StatsObservable::GetPlayer()
{
	return _currentPlayer;
}

