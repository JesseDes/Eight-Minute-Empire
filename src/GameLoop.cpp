#include "GameLoop.h"
#include "Utils.h"

void GameLoop::GameInit()
{
	gameBoard = MapLoader::FindMap();
	std::cout << "How many Players will be playing?\n";
	
	int playerCount;
	std::cin >> playerCount;
	playerCount = Utils::validInputRange(*MIN_PLAYERS, *MAX_PLAYERS, playerCount, "Value must be between" + std::to_string(*MIN_PLAYERS) + " and " + std::to_string(*MAX_PLAYERS));

	for (int i = 0; i < playerCount; i++)
	{
		std::string name;
		int age;
		std::cout << "Player " << playerCount << " What is your name? \n";
		std::cin >> name;
		std::cout << "How old are you?";
		std::cin >> age;
		playerList.push_back(new Player(age, name));

	}
}

void GameLoop::GameStart()
{


}

void GameLoop::GameRun()
{

}

void GameLoop::GameEnd()
{

}