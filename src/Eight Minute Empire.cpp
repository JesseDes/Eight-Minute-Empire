// Fixit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Testers.h"
#include "Utils.h"
#include "GameLoop.h"


int main()
{
	/*
	GameLoop gameCycle;
	gameCycle.GameInit();
	gameCycle.GameStart();

	//gameCycle.GameEnd();

	gameCycle.GameEnd();
	*/

    std::cout << "choose a test: \n"
        << "[0] stats test \n"
        << "[1] phase test \n"
        << "[2] strategy test \n"
        << "[3] singleton map test \n";

    int selection;
    std::cin >> selection;
	
    switch (selection) 
    {
        case 0: Testers::StatsTest(); break;
        case 1: Testers::PhaseTest(); break;
        case 2: Testers::StrategyTest(); break;
        case 3: Testers::SingletonMapTest(); break;
    }

	system("pause");
}
