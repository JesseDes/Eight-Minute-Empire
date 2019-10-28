// Fixit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Testers.h"
#include "Utils.h"
#include "GameLoop.h"

int main()
{

	GameLoop gameCycle;
	gameCycle.GameInit();
	gameCycle.GameStart();

	while (gameCycle.isRunning())
	{
		gameCycle.GameRun();
	}

	gameCycle.GameEnd();

	system("pause");
	/*
	int selection;
	std::cout << "Select what you'd like to test \n";
	std::cout << "[1] Test Map generation \n";
	std::cout << "[2] Test Map Load \n";
	std::cout << "[3] Test Player Classes \n";
	std::cout << "[4] Test Deck \n";
	std::cout << "[5] Test Bidding\n";
	std::cin >> selection;

	selection = Utils::validInputRange(1, 5, selection, "Option must be between 1 and 5 \r");

	switch (selection)
	{
		case 1: Testers::MapTest(); break;
		case 2: Testers::MapLoadTest(); break;
		case 3: Testers::PlayerTest(); break;
		case 4: Testers::DeckTest(); break;
		case 5: Testers::BiddingTest(); break;
		default: Testers::MapLoadTest(); break;
	}
	*/
}
