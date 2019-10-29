#include "GameLoop.h"
#include "Utils.h"
#include <iterator>

GameLoop::~GameLoop()
{
	delete _turnCount;
	_turnCount = NULL;

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

	setTurnCount(playerCount);

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

	for (int i = 0; i <= gameHand->SIZE_OF_HAND; i++)
		gameHand->addCard(gameDeck->Draw());


	currentPlayer = playerList.begin();
	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		(*it)->createCoinPurse(playerList.size());
		(*it)->placeBid();

		if (it != playerList.begin() && ((*currentPlayer)->getBid() < (*it)->getBid() || ((*currentPlayer)->getBid() == (*it)->getBid() && (*currentPlayer)->getPlayerAge() > (*it)->getPlayerAge())))
			currentPlayer = it;
	
	}


	std::cout << "HIGHEST BIDDER WAS :"<< (*currentPlayer)->getPlayerName() << "\n";

	*_isRunning = true;

}

void GameLoop::GameRun()
{

	std::cout << "It is " << (*currentPlayer)->getPlayerName() << "'s turn \n";

	*_turnCount += 1;

	gameHand->showHand();

	std::cout << (*currentPlayer)->getPlayerName() << "which card would you like? \n";
	int chosenCard;
	do 
	{
		std::cin >> chosenCard;
		chosenCard = Utils::validInputRange(0, gameHand->SIZE_OF_HAND, chosenCard, "Invalid Selection Please choose a card from the list above");
		
	} while (!(*currentPlayer)->payCoin(gameHand->getCardCost(chosenCard)));
	
	(*currentPlayer)->readCard(gameHand->exchange(chosenCard));

	gameHand->addCard(gameDeck->Draw());

	if (*_turnCount >= *_maxTurnCount)
	{
		*_isRunning = false;
		return;
	}

	if (std::distance(currentPlayer, playerList.end()) == 1)
	{
		currentPlayer = playerList.begin();
	}
	else
	{
		currentPlayer++;
	}
}

void GameLoop::GameEnd()
{
	int highScore = 0;
	currentPlayer = playerList.begin();
	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		int currentScore = (*it)->getScore();
		 std::cout << (*it)->getPlayerName() << " : " << currentScore << " points! \n";
		 if (currentScore > highScore || (currentScore == highScore && (*currentPlayer)->getPlayerAge() < (*it)->getPlayerAge())  )
			 currentPlayer = it;
	}

	std::cout << (*currentPlayer)->getPlayerName() << " Wins!!!!!!!!! \n";
}

void GameLoop::setTurnCount(int playerCount)
{
	switch (playerCount)
	{
		case 2: _maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 3: _maxTurnCount = new int(*THREE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 4: _maxTurnCount = new int(*FOUR_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 5: _maxTurnCount = new int(*FIVE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;

		default: _maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
	}

}