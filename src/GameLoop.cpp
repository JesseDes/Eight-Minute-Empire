#pragma once

#include "GameLoop.h"
#include "Utils.h"
#include <iterator>

std::vector<Player*> GameLoop::_playerList;

GameLoop::GameLoop()
{
	_phaseSubject = new PhaseObservable();
	_phaseObserver = new PhaseObserver(_phaseSubject);

	_statsSubject = new StatsObservable();
	_statsObserver = new StatsObserver(_statsSubject);

}

GameLoop::~GameLoop()
{
	delete _phaseObserver;
	delete _phaseSubject;

	_phaseSubject = NULL;
	_phaseObserver = NULL;
	
	delete _statsObserver;
	delete _statsSubject;

	_statsSubject = NULL;
	_statsObserver = NULL;

	delete _turnCount;
	_turnCount = NULL;

	delete _isRunning;
	_isRunning = NULL;
	
	delete _isShadowPhase;
	_isShadowPhase = NULL;

	delete _shadowArmyCount;
	_shadowArmyCount = NULL;
	

	for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); it++)
	{
		delete (*it);
		(*it) = NULL;
	}

	delete _gameDeck;
	_gameDeck = NULL;

	delete _gameHand;
	_gameHand = NULL;

	delete *_currentPlayer;
	*_currentPlayer = NULL;
	
	delete _shadowPlayer;
	_shadowPlayer = NULL;

	delete _turnCount;
	_turnCount = NULL;

	delete _maxTurnCount;
	_maxTurnCount = NULL;
}

void GameLoop::GameInit()
{
	Utils::View("Select Game Mode");
	Utils::View("[0] Normal Play");
	Utils::View("[1] Tournament Mode");

	int gameMode;

	gameMode = Utils::ValidInputRange(0, 1,  "Please select a valid game mode");
	
	_gameType = (GameType)gameMode;

	MapLoader::FindMap();

	std::cout << "How many Players will be playing?\n";
	
	int playerCount;
	if(gameMode == GameType::TOURNAMENT)
		playerCount = Utils::ValidInputRange(*MIN_PLAYERS, 4,  "Value must be between " + std::to_string(*MIN_PLAYERS) + " and 4");
	else 
		playerCount = Utils::ValidInputRange(*MIN_PLAYERS, *MAX_PLAYERS, "Value must be between" + std::to_string(*MIN_PLAYERS) + " and " + std::to_string(*MAX_PLAYERS));

	SetTurnCount(playerCount);
	

	//create players
	for (int i = 0; i < playerCount; i++)
	{
		std::string name;
		int age;
		std::cout << "Player " << (i + 1) << " What is your name? \n";
		std::cin >> name;
		std::cout << "How old are you? \n";
		age = Utils::ValidInputMin(0,"Please enter a valid age");
        Player* player = new Player(age, name);
        GetGameTypeStrategies(player); 
		_playerList.push_back(player);

	}
}

void GameLoop::GameStart()
{
	//create deck , shuffle, and add cards to hand
	_gameDeck = new Deck();
	_gameDeck->Shuffle();

	_gameHand = new Hand();

	for (int i = 0; i <= _gameHand->SIZE_OF_HAND; i++)
		_gameHand->AddCard(_gameDeck->Draw());
	
	//determine first player
	_currentPlayer = _playerList.begin();
	for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); it++)
	{
		(*it)->CreateCoinPurse(_playerList.size());
		std::cout << (*it)->GetPlayerName() + " ";
		(*it)->PlaceBid();
		(*it)->GivePieces(*ARMY_PIECES_PER_PLAYER, *CITY_PIECES_PER_PLAYER);

		// adding 3 troops to the starting country
		for (int j = 0; j < 3; j++)
			EmpireMap::instance()->GetStartingCountry()->AddArmy((*it));

		//currentPlayer is set to the player with the highest Bid and the youngest age (if matching bids) 
		if (it != _playerList.begin() && ((*_currentPlayer)->GetBid() < (*it)->GetBid() || ((*_currentPlayer)->GetBid() == (*it)->GetBid() && (*_currentPlayer)->GetPlayerAge() > (*it)->GetPlayerAge())))
			_currentPlayer = it;
	}


	(*_currentPlayer)->PayCoin((*_currentPlayer)->GetBid());
	std::cout << "HIGHEST BIDDER WAS :"<< (*_currentPlayer)->GetPlayerName() << "\n";

	//game has now begun
	 *_isRunning = true;
	 if (_playerList.size() == 2)
	 {
		 *_isShadowPhase = true;
		 _shadowPlayer = new Player(0, "Shadow Player");
	 }
	 
}

void GameLoop::GameRun()
{
	std::cout << "It is " << (*_currentPlayer)->GetPlayerName() << "'s turn \n";

	if (*_isShadowPhase)
	{
		std::cout << "Place shadow player army in a country \n";
		
		(*_currentPlayer)->PlaceShadowPlayer(_shadowPlayer);

		(*_shadowArmyCount)--;

		if (*_shadowArmyCount == 0)
			*_isShadowPhase = false;
	}
	else
	{
		_phaseSubject->StartTurn((*_currentPlayer)->GetPlayerName());
		_statsSubject->SetPlayer(*_currentPlayer);
		_statsSubject->UpdateCountries((*_currentPlayer)->GetCountries());
		_statsSubject->UpdatePlayerGoods((*_currentPlayer)->GetGoods());
		
		*_turnCount += 1;
		_gameHand->ShowHand();

		std::cout << (*_currentPlayer)->GetPlayerName() << ", which card would you like? \n";
		
		(*_currentPlayer)->ChooseCard(_gameHand);
		_gameHand->AddCard(_gameDeck->Draw());
	}

	if (*_turnCount >= *_maxTurnCount)
	{
		*_isRunning = false;
		return;
	}

	//if player is last in the vector, go back to beginning else, increment iterator
	if (std::distance(_currentPlayer, _playerList.end()) == 1)
	{
		_currentPlayer = _playerList.begin();
	}
	else
	{
		_currentPlayer++;
	}
}

void GameLoop::GameEnd()
{
	Utils::View("\n\n ***********************FINAL RESULTS****************** \n\n");
	for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); it++)
	{
		_statsSubject->SetPlayer(*it);
		_statsSubject->UpdateCountries((*it)->GetCountries());
		_statsSubject->UpdatePlayerGoods((*it)->GetGoods());
	}


	int highScore = 0;
	int playerNameLength;
	_currentPlayer = _playerList.begin();
	std::string SPACE_BETWEEN_COLUMNS;

	for (int i = 0; i < *SPACE_BETWEEN_HEADER; i++)
		SPACE_BETWEEN_COLUMNS += " ";

	Utils::View("Player Name" + SPACE_BETWEEN_COLUMNS + "Cards" + SPACE_BETWEEN_COLUMNS + "Points" + SPACE_BETWEEN_COLUMNS + "Coins");
	
	for (int i = 0; i < *SPACE_BETWEEN_SCORE_LINE; i++)
		SPACE_BETWEEN_COLUMNS += " ";
	
	for (std::vector<Player*>::iterator it = _playerList.begin(); it != _playerList.end(); it++)
	{
		std::string spaceBetweenName;
		int currentScore = (*it)->GetScore();
		playerNameLength = (*it)->GetPlayerName().length();
		
		for (int i = 0; i < *SCORE_LINE_FIRST_SPACE_LENGTH - playerNameLength; i++)
			spaceBetweenName += " ";

		Utils::View((*it)->GetPlayerName() + spaceBetweenName + std::to_string((*it)->GetActionCount()) + SPACE_BETWEEN_COLUMNS + std::to_string(currentScore) + SPACE_BETWEEN_COLUMNS + std::to_string((*it)->GetCoins()));
		if (currentScore > highScore)
		{
			highScore = currentScore;
			_currentPlayer = it;
		}
	}

	std::cout << (*_currentPlayer)->GetPlayerName() << " Wins!!!!!!!!! \n";
}

void GameLoop::SetTurnCount(int playerCount)
{
	//turns is equal to specific amount * number of players

	if (_gameType == GameType::NORMAL)
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
	else if (_gameType == GameType::TOURNAMENT)
		_maxTurnCount = new int((30 / playerCount) * playerCount);	//it may seem redundant but the first divison is a floor to nearest int then we do it per player ex: 30/4 = 7 * 4 =28
	

}


void GameLoop::GetGameTypeStrategies(Player *player)
{
	Utils::View("What kind of Strategy would you like to use?");
	int selection;

	if (_gameType == GameType::NORMAL)
	{
		Utils::View("[0] Moderate Computer");
		Utils::View("[1] Greedy Computer");
		Utils::View("[2] Human");

		selection = Utils::ValidInputRange(0, 2,  "Please select a valid strategy");

		switch (selection)
		{
			case 0: player->SetPlayerStrategy(new ModerateComputer()); break;
			case 1:  player->SetPlayerStrategy(new GreedyComputer()); break;
			case 2:  player->SetPlayerStrategy(new Human()); break;
		}
	}
	else if (_gameType == GameType::TOURNAMENT)
	{
		Utils::View("[0] Moderate Computer");
		Utils::View("[1] Greedy Computer");

		selection = Utils::ValidInputRange(0, 1,  "Please select a valid strategy");

		switch (selection)
		{
			case 0: player->SetPlayerStrategy(new ModerateComputer()); break;
			case 1:  player->SetPlayerStrategy(new GreedyComputer()); break;
		}
	}
}


std::vector<Player*> GameLoop::GetPlayerList()
{
    return _playerList;
}