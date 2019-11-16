#pragma once

#include "GameLoop.h"
#include "Utils.h"
#include <iterator>

std::vector<Player*> GameLoop::playerList;

GameLoop::GameLoop()
{

}

GameLoop::~GameLoop()
{
	delete turnCount;
	turnCount = NULL;

	delete _isRunning;
	_isRunning = NULL;
	
	delete _isShadowPhase;
	_isShadowPhase = NULL;

	delete shadowArmyCount;
	shadowArmyCount = NULL;
	

	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		delete (*it);
		(*it) = NULL;
	}

	delete gameBoard;
	gameBoard = NULL;

	delete gameDeck;
	gameDeck = NULL;

	delete gameHand;
	gameHand = NULL;

	delete *currentPlayer;
	*currentPlayer = NULL;
	
	delete shadowPlayer;
	shadowPlayer = NULL;

	delete turnCount;
	turnCount = NULL;

	delete maxTurnCount;
	maxTurnCount = NULL;
}

void GameLoop::GameInit()
{
	do
	{
		gameBoard = MapLoader::FindMap();
	} while (!gameBoard->isValid());

	std::cout << "How many Players will be playing?\n";
	
	int playerCount;
	std::cin >> playerCount;
	playerCount = Utils::validInputRange(*MIN_PLAYERS, *MAX_PLAYERS, playerCount, "Value must be between" + std::to_string(*MIN_PLAYERS) + " and " + std::to_string(*MAX_PLAYERS));

	setTurnCount(playerCount);
	

	//create players
	for (int i = 0; i < playerCount; i++)
	{
		std::string name;
		int age;
		std::cout << "Player " << (i + 1) << " What is your name? \n";
		std::cin >> name;
		std::cout << "How old are you? \n";
		std::cin >> age;
        Player* player = new Player(age, name);
        //player->setPlayerStrategy(new Human); //UNCOMMENT TO MAKE ORIGINAL PROGRAM WORK
		playerList.push_back(player);

	}
}

void GameLoop::GameStart()
{
	//create deck , shuffle, and add cards to hand
	gameDeck = new Deck();
	gameDeck->Shuffle();

	gameHand = new Hand();

	for (int i = 0; i <= gameHand->SIZE_OF_HAND; i++)
		gameHand->AddCard(gameDeck->Draw());
	
	//determine first player
	currentPlayer = playerList.begin();
	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		(*it)->createCoinPurse(playerList.size());
		(*it)->placeBid();
		(*it)->GivePieces(*ARMY_PIECES_PER_PLAYER, *CITY_PIECES_PER_PLAYER);

		// adding 3 troops to the starting country
		for (int j = 0; j < 3; j++)
			gameBoard->getStartingCountry()->addArmy((*it));

		//currentPlayer is set to the player with the highest Bid and the youngest age (if matching bids) 
		if (it != playerList.begin() && ((*currentPlayer)->getBid() < (*it)->getBid() || ((*currentPlayer)->getBid() == (*it)->getBid() && (*currentPlayer)->getPlayerAge() > (*it)->getPlayerAge())))
			currentPlayer = it;
	}


	(*currentPlayer)->payCoin((*currentPlayer)->getBid());
	std::cout << "HIGHEST BIDDER WAS :"<< (*currentPlayer)->getPlayerName() << "\n";

	//game has now begun
	 *_isRunning = true;
	 if (playerList.size() == 2)
	 {
		 *_isShadowPhase = true;
		 shadowPlayer = new Player(0, "Shadow Player");
	 }
	 
}

void GameLoop::GameRun()
{
	std::cout << "It is " << (*currentPlayer)->getPlayerName() << "'s turn \n";

	if (*_isShadowPhase)
	{
		std::cout << "Place shadow player army in a country \n";
		
		int numberOfCountries=  MapLoader::GetMap()->getCountries();
		Country* country;
		for (int j = 0; j < numberOfCountries; j++) 
		{
			country = MapLoader::GetMap()->country(j);
			std::cout << "Country [" << j << "] Shadow Player has " << country->getArmy(shadowPlayer) << " troops \n";
			
		}


		int selection;
		std::cin >> selection;
		selection = Utils::validInputRange(0, numberOfCountries - 1, selection, "please choose a value between 0 and " + ( numberOfCountries - 1));
		
		MapLoader::GetMap()->country(selection)->addArmy(shadowPlayer);

		(*shadowArmyCount)--;

		if (*shadowArmyCount == 0)
			*_isShadowPhase = false;
	}
	else
	{

		*turnCount += 1;

		gameHand->ShowHand();

		std::cout << (*currentPlayer)->getPlayerName() << ", which card would you like? \n";
		int chosenCard;
		do
		{
			std::cin >> chosenCard;
			chosenCard = Utils::validInputRange(0, gameHand->SIZE_OF_HAND, chosenCard, "Invalid Selection Please choose a card from the list above");

		} while (!(*currentPlayer)->payCoin(gameHand->GetCardCost(chosenCard)));

		//reads card and performs action
		(*currentPlayer)->readCard(gameHand->Exchange(chosenCard));

		gameHand->AddCard(gameDeck->Draw());
	}

	if (*turnCount >= *maxTurnCount)
	{
		*_isRunning = false;
		return;
	}

	//if player is last in the vector, go back to beginning else, increment iterator
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
	int highScore = 0;	//highscore is stored as int to avoid redoing calculations
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
	//turns is equal to specific amount * number of players
	switch (playerCount)
	{
		case 2: maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 3: maxTurnCount = new int(*THREE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 4: maxTurnCount = new int(*FOUR_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 5: maxTurnCount = new int(*FIVE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;

		default: maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
	}

}
std::vector<Player*> GameLoop::getPlayerList()
{
    return playerList;
}