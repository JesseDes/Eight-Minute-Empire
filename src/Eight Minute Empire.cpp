// Fixit.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Testers.h"
#include "Utils.h"
#include "GameLoop.h"
#include <time.h>
#include <stdlib.h>

int main()
{
	srand(time(NULL));
	
	GameLoop gameCycle;
	while (true)	//init cycle Loop Keep trying trying to load a map until a valid one is found
	{
		try
		{
			gameCycle.GameInit();
			break;
		}
		catch (...)
		{
			Utils::View("Restarting application");
			system("pause");
			system("CLS");
		}
	}
	gameCycle.GameStart();

	while (gameCycle.isRunning())
		gameCycle.GameRun();

	gameCycle.GameEnd();
	
	/*
    std::cout << "choose a test: \n"
        << "[0] stats test \n"
        << "[1] phase test \n"
        << "[2] strategy test \n"
        << "[3] singleton map test \n"
        << "[4] card factory test \n";

    int selection = Utils::validInputRange(0,4,"Please select a valid option");
	
    switch (selection) 
    {
        case 0: Testers::StatsTest(); break;
        case 1: Testers::PhaseTest(); break;
        case 2: Testers::StrategyTest(); break;
        case 3: Testers::SingletonMapTest(); break;
        case 4: Testers::FactoryTest(); break;
    }
	*/
	system("pause");
}
