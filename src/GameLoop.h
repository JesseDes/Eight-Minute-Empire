#pragma once
#include <vector>
#include "Player.h"
#include "map.h"
#include "MapLoader.h"
//GameLoop manages the 
class GameLoop
{
public:
	const int* MAX_PLAYERS = new int(5);
	const int* MIN_PLAYERS = new int(2);
	const int* TWO_PLAYER_END_GAME_CARD_COUNT = new int(3); //13
	const int* THREE_PLAYER_END_GAME_CARD_COUNT = new int(10);
	const int* FOUR_PLAYER_END_GAME_CARD_COUNT = new int(8);
	const int* FIVE_PLAYER_END_GAME_CARD_COUNT = new int(7);
	~GameLoop();
	void GameInit();
	void GameStart();
	void GameRun();
	void GameEnd();
	bool isRunning() { return *_isRunning; }
    static std::vector<Player*> getPlayerList();

private:
	EmpireMap *gameBoard;
	static std::vector<Player*> playerList;
	Hand *gameHand;
	Deck *gameDeck;
	std::vector<Player*>::iterator currentPlayer;
	bool *_isRunning = new bool(false);
	int *_turnCount = new int(0);
	int *_maxTurnCount;
	void setTurnCount(int playerCount);
	
};