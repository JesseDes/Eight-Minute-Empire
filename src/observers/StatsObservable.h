#pragma once
#include "Subject.h"
#include "../map/map.h"
#include "../cards/Good.h"
#include <map>

enum class StatsState
{
	Country,
	Good,
};

class StatsObservable : public Subject
{
public:
	StatsObservable();
	~StatsObservable();
	void SetPlayer(Player *player);
	void UpdateCountries(std::vector<int> *list);
	void UpdatePlayerGoods(std::map<GoodType, int*> *good);
	StatsState GetState();
	std::vector<int>* GetCountryList();
	std::map<GoodType, int*>* GetGoodsMap();
	Player* GetPlayer();

private:
	std::map<GoodType, int*> *_goodMap;
	std::vector<int> *_countryList;
	StatsState _currentState;
	Player *_currentPlayer;
};