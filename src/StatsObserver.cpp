#include "StatsObserver.h"
#include "MapLoader.h"

StatsObserver::StatsObserver(StatsObservable *observable)
{
	_subject = observable;
	_subject->Attach(this);
}

StatsObserver::~StatsObserver()
{
	_subject->Detach(this);
	_subject = NULL; 
}

void StatsObserver::Update()
{
	if (_subject->GetState() == StatsState::Country)
		DisplayCountriesChart();
	else
		DisplayGoodsChart();
}

void StatsObserver::DisplayCountriesChart()
{
	if (_subject->GetCountryList()->size() == 0)
	{
		std::cout << _subject->GetPlayer()->getPlayerName() << " has No countries\n";
		return;
	}

	
	std::string output = _subject->GetPlayer()->getPlayerName() + "'s Countries are currently:\n";
	for (int i = 0; i < _subject->GetCountryList()->size(); i++)
	{
		int country = _subject->GetCountryList()->at(i);
		output += "Country " + std::to_string(country) + " |";
		for (int j = 0; j < MapLoader::GetMap()->country(country)->getArmy(_subject->GetPlayer()); j++)
			output += "*";
		for (int j = 0; j < MapLoader::GetMap()->country(country)->getCities(_subject->GetPlayer()); j++)
			output += "[]";
		output += "\n";
	}

	Utils::View(output);
}

void StatsObserver::DisplayGoodsChart()
{
	std::string output = _subject->GetPlayer()->getPlayerName() + "'s Goods are currently:\n"; ;
	for (std::map<GoodType, int*>::iterator it = _subject->GetGoodsMap()->begin(); it != _subject->GetGoodsMap()->end(); it++)
	{
		output += Good::GoodToString(it->first);
		int spaceCount = Good::GoodToString(it->first).length() - 5; // This keeps the rows even
		for (int i = 0; i < spaceCount; i++)
			output += " ";
		output += "|";

		for (int i = 0; i < *(it->second); i++)
			output += "*";

		output += " for " + std::to_string(Good::GoodToScore(it->first, *it->second)) + " points\n";
	}

	Utils::View(output);
}

