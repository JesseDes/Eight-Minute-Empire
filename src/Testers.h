#pragma once
#include <vector>
#include "Player.h"

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
    static std::vector<Player*> getPlayerList(); //returns a vector of every player in the current game 
private:
    static std::vector<Player*> playerList;
};

