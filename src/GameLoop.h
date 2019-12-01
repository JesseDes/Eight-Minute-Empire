#pragma once
#include <vector>
#include "Player.h"
#include "map.h"
#include "MapLoader.h"
#include "Testers.h"


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
	const int* TWO_PLAYER_END_GAME_CARD_COUNT = new int(2);  // 13
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
	bool isRunning() { return *_isRunning; } //returns true if the game is currently being played (This means the setup is finished)
    static std::vector<Player*> getPlayerList(); //returns a vector of every player in the current game

private:
	static std::vector<Player*> playerList;
	Hand *gameHand;
	Deck *gameDeck;
	std::vector<Player*>::iterator currentPlayer;
	bool *_isRunning = new bool(false);
	int *turnCount = new int(0);
	int *maxTurnCount;
	void setTurnCount(int playerCount); //sets the maximum number of turns based on the number of players
	bool *_isShadowPhase = new bool(false);
	int *shadowArmyCount = new int(10);
	Player *shadowPlayer;
	GameType _gameType;
	void getGameTypeStrategies(Player *player);
	
};