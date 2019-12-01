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
	
	system("pause");
}
