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
	Utils::View("Select Game Mode");
	Utils::View("[0] Normal Play");
	Utils::View("[1] Tournament Mode");

	int gameMode;

	gameMode = Utils::validInputRange(0, 1,  "Please select a valid game mode");
	
	_gameType = (GameType)gameMode;

	MapLoader::FindMap();

	std::cout << "How many Players will be playing?\n";
	
	int playerCount;
	if(gameMode == GameType::TOURNAMENT)
		playerCount = Utils::validInputRange(*MIN_PLAYERS, 4,  "Value must be between" + std::to_string(*MIN_PLAYERS) + " and 4");
	else 
		playerCount = Utils::validInputRange(*MIN_PLAYERS, *MAX_PLAYERS, "Value must be between" + std::to_string(*MIN_PLAYERS) + " and " + std::to_string(*MAX_PLAYERS));

	setTurnCount(playerCount);
	

	//create players
	for (int i = 0; i < playerCount; i++)
	{
		std::string name;
		int age;
		std::cout << "Player " << (i + 1) << " What is your name? \n";
		std::cin >> name;
		std::cout << "How old are you? \n";
		age = Utils::validInputMin(0,"Please enter a valid age");
        Player* player = new Player(age, name);
        getGameTypeStrategies(player); 
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
			EmpireMap::instance()->getStartingCountry()->addArmy((*it));

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
		
		(*currentPlayer)->PlaceShadowPlayer(shadowPlayer);

		(*shadowArmyCount)--;

		if (*shadowArmyCount == 0)
			*_isShadowPhase = false;
	}
	else
	{

		*turnCount += 1;

		gameHand->ShowHand();

		std::cout << (*currentPlayer)->getPlayerName() << ", which card would you like? \n";
		
		/*int chosenCard;
		do
		{
			chosenCard = Utils::validInputRange(0, gameHand->SIZE_OF_HAND, "Invalid Selection Please choose a card from the list above");

		} while (!(*currentPlayer)->payCoin(gameHand->GetCardCost(chosenCard)));
		*/
		//reads card and performs actio
		//(*currentPlayer)->readCard(gameHand->Exchange(chosenCard));
		(*currentPlayer)->chooseCard(gameHand);

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
	std::string SPACE_BETWEEN_COLUMNS = "        ";
	Utils::View("Player Name" + SPACE_BETWEEN_COLUMNS + "Cards" + SPACE_BETWEEN_COLUMNS + "Points" + SPACE_BETWEEN_COLUMNS + "Coins");
	SPACE_BETWEEN_COLUMNS = "           ";	//Enlarge the space since to try and keep things well placed
	for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
	{
		int currentScore = (*it)->getScore();
		 //std::cout << (*it)->getPlayerName() << " : " << currentScore << " points! \n";

		Utils::View((*it)->getPlayerName() + SPACE_BETWEEN_COLUMNS + std::to_string((*it)->getCardCount()) + SPACE_BETWEEN_COLUMNS + std::to_string(currentScore) + SPACE_BETWEEN_COLUMNS + std::to_string((*it)->getCoins()));
		 if (currentScore > highScore || (currentScore == highScore && (*currentPlayer)->getPlayerAge() < (*it)->getPlayerAge())  )
			 currentPlayer = it;
	}

	std::cout << (*currentPlayer)->getPlayerName() << " Wins!!!!!!!!! \n";
}

void GameLoop::setTurnCount(int playerCount)
{
	//turns is equal to specific amount * number of players

	if (_gameType == GameType::NORMAL)
	{
		switch (playerCount)
		{
		case 2: maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 3: maxTurnCount = new int(*THREE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 4: maxTurnCount = new int(*FOUR_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		case 5: maxTurnCount = new int(*FIVE_PLAYER_END_GAME_CARD_COUNT * playerCount); break;

		default: maxTurnCount = new int(*TWO_PLAYER_END_GAME_CARD_COUNT * playerCount); break;
		}
	}
	else if (_gameType == GameType::TOURNAMENT)
		maxTurnCount = new int((30 / playerCount) * playerCount);	//it may seem redundant but the first divison is a floor to nearest int then we do it per player ex: 30/4 = 7 * 4 =28
	

}


void GameLoop::getGameTypeStrategies(Player *player)
{
	Utils::View("What kind of Strategy would you like to use?");
	int selection;

	if (_gameType == GameType::NORMAL)
	{
		Utils::View("[0] Moderate Computer");
		Utils::View("[1] Greedy Computer");
		Utils::View("[2] Human");

		selection = Utils::validInputRange(0, 2,  "Please select a valid strategy");

		switch (selection)
		{
			case 0: player->setPlayerStrategy(new ModerateComputer()); break;
			case 1:  player->setPlayerStrategy(new GreedyComputer()); break;
			case 2:  player->setPlayerStrategy(new Human()); break;
		}
	}
	else if (_gameType == GameType::TOURNAMENT)
	{
		Utils::View("[0] Moderate Computer");
		Utils::View("[1] Greedy Computer");

		selection = Utils::validInputRange(0, 1,  "Please select a valid strategy");

		switch (selection)
		{
			case 0: player->setPlayerStrategy(new ModerateComputer()); break;
			case 1:  player->setPlayerStrategy(new GreedyComputer()); break;
		}
	}
}


std::vector<Player*> GameLoop::getPlayerList()
{
    return playerList;
}