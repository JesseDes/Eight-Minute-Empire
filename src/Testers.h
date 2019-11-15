#pragma once

/*
A utility class with all tests available to run
*/

struct TestType{
	int test;
	char type;
};


class Testers
{
public:
	static void DeckTest();
	static void BiddingTest();
	static void PlayerTest();
	static void MapTest();
    static void StrategyTest();
};

