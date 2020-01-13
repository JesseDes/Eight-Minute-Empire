#pragma once
#include <vector>
#include "Player.h"
#include "map.h"
#include "MapLoader.h"
#include "Testers.h"
#include "PhaseObservable.h"
#include "PhaseObserver.h"
#include "StatsObservable.h"
#include "StatsObserver.h"

class GameLoop
{
public:
	enum GameType
	{
		NORMAL,
		TOURNAMENT
	};

	const int* MAX_PLAYERS = new int(5);
	const int* MIN_PLAYERS = new int(2);
	const int* TWO_PLAYER_END_GAME_CARD_COUNT = new int(3);  // 13
	const int* THREE_PLAYER_END_GAME_CARD_COUNT = new int(10); // 10
	const int* FOUR_PLAYER_END_GAME_CARD_COUNT = new int(8); // 8
	const int* FIVE_PLAYER_END_GAME_CARD_COUNT = new int(7); // 7
	const int* ARMY_PIECES_PER_PLAYER = new int(14);
	const int* CITY_PIECES_PER_PLAYER = new int(3);
	GameLoop();
	~GameLoop();
	void GameInit();		//initial board set up and player counting
	void GameStart();		// Getting player info, serving players their coins and determining starting player
	void GameRun();			//Players draw cards and choose their actions
	void GameEnd();			// Tally points of each player and determines a winner
	bool IsRunning() { return *_isRunning; } //returns true if the game is currently being played (This means the setup is finished)
    static std::vector<Player*> GetPlayerList(); //returns a vector of every player in the current game

private:
	const int* SPACE_BETWEEN_HEADER = new int(10);		//These are lengths used to format end game message, if you update the text the values must be changed
	const int* SPACE_BETWEEN_SCORE_LINE = new int (6);
	const int* SCORE_LINE_FIRST_SPACE_LENGTH = new int(21);

	void SetTurnCount(int playerCount); //sets the maximum number of turns based on the number of players
	void GetGameTypeStrategies(Player *player);

	static std::vector<Player*> _playerList;

	std::vector<Player*>::iterator _currentPlayer;
	Hand *_gameHand;
	Deck *_gameDeck;
	bool *_isRunning = new bool(false);
	bool *_isShadowPhase = new bool(false);
	int *_turnCount = new int(0);
	int *_maxTurnCount;
	int *_shadowArmyCount = new int(10);
	Player *_shadowPlayer;
	GameType _gameType;
	PhaseObservable *_phaseSubject;
	PhaseObserver *_phaseObserver;
	StatsObservable *_statsSubject;
	StatsObserver *_statsObserver;
	
};