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
	~GameLoop();
	void GameInit();
	void GameStart();
	void GameRun();
	void GameEnd();
	bool isRunning() { return _isRunning; }

	
private:
	EmpireMap *gameBoard;
	std::vector<Player*> playerList;
	Hand *gameHand;
	Deck *gameDeck;
	std::vector<Player*>::iterator *currentPlayer;
	bool *_isRunning = false;
	
};