#pragma once
#include <vector>
#include <iostream>
#include "cards/Deck.h"
#include "cards/Hand.h"
#include "entities/BiddingFacility.h"
#include "entities/Player.h"
#include <list>
#include "map/map.h"
#include "map/MapLoader.h"
#include "observers/PhaseObservable.h"
#include "observers/PhaseObserver.h"
#include "observers/StatsObservable.h"
#include "observers/StatsObserver.h"
#include "core/GameLoop.h"
/*
A utility class with all tests available to run
*/


class Testers
{
public:
	static void DeckTest();
	static void BiddingTest();
	static void PlayerTest();
	static void MapTest();
	static void PhaseTest();
	static void StatsTest();
    static void StrategyTest();
    static std::vector<Player*> getPlayerList(); //returns a vector of every player in the current game (needed for strategy test)
    static void SingletonMapTest();
    static void FactoryTest();
private:
    static std::vector<Player*> playerList; //vector of every player in current game (needed for strategy test)
};

