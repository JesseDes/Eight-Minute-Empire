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
	
	//Testers::StatsTest();
	//Testers::PhaseTest();
    Testers test;
    test.StrategyTest();

	system("pause");
}
