#include "GameLoop.h"
#include "Utils.h"


GameLoop::~GameLoop()
{
	delete _isRunning;
	_isRunning = NULL;
}

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
		std::cout << "Player " << (i + 1) << " What is your name? \n";
		std::cin >> name;
		std::cout << "How old are you?";
		std::cin >> age;
		playerList.push_back(new Player(age, name));

	}
}

void GameLoop::GameStart()
{
	gameDeck = new Deck();
	gameDeck->Shuffle();
	gameHand = new Hand();

	for (int i = 0; i < gameHand->SIZE_OF_HAND; i++)
		gameHand->addCard(gameDeck->Draw());

	gameHand->showHand();


	std::vector<Player*>::iterator highestBidder;
	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		(*it)->createCoinPurse(playerList.size());
		(*it)->placeBid();

		if (it != playerList.begin() && ((*highestBidder)->getBid() < (*it)->getBid() || ((*highestBidder)->getBid() == (*it)->getBid() && (*highestBidder)->getPlayerAge() > (*it)->getPlayerAge())))
			highestBidder = it;
		else if (it == playerList.begin())
			highestBidder = it;
	}
	currentPlayer = &highestBidder;
	std::cout << "HIGHEST BIDDER WAS :"<< (**currentPlayer)->getPlayerName() << "\n";


	*_isRunning = true;

}

void GameLoop::GameRun()
{

}

void GameLoop::GameEnd()
{

}