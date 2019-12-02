#pragma once
#include "Deck.h"
#include "BiddingFacility.h"
#include "Hand.h"
#include <vector>
#include <iostream>
#include "Utils.h"
#include <string>
#include <map>
#include "PlayerStrategies.h"


/*
The Player of the game. Contains a player's name and age and a Bidding Facility. 
Player is able to read Cards and choose one action among them
Player is able to place bids and pay for cards.

*/

class IPlayerStrategy; //forward declaration 

class Player
{
public:
	
	Player(int age, std::string name);
	~Player();
	void createCoinPurse(int numberOfPlayers);			//Gives players the number of coins based on the number of players
    void chooseCard(Hand *gameHand);                    //player chooses a card from the deck
	void readCard(Card *gameCard);			//Player reads a card and selects an action to do based on the card
	void doAction(Action action); //performs action: add/remove army, add city, travel by land/water an amount of times as specified by the action.amount attribute
	bool payCoin(int cost);		//The player coinpurse is reduced by cost amount
	int getPlayerAge();			// returns the age of the player
    BiddingFacility* getBidder(); // returns the bidder
	void placeBid();			//calls the bidder to prompt the player to place a bid
	int getBid();				// returns the players bid from the bidder
	int getCoins();				// returns the coinPurse value from the bidder
	std::string getPlayerName() { return *playerName; };		// returns player name
	int getScore();		//calculates the players score from their goods and territories 
	void GivePieces(int army, int cities);	//serves the player the number of board pieces they get
	void DrawArmyPiece();
	int GetGoodPoints();
	std::vector<int>* GetCountries();
	std::map<GoodType, int*>* GetGoods();
    void setPlayerStrategy(IPlayerStrategy *behavior);
    IPlayerStrategy* getPlayerStrategy();

private:
	std::vector<int> *countryList; 
	BiddingFacility *bidder;
	int *playerAge;
	std::map<GoodType,int*> _goodMap;
	std::string *playerName;
	Hand *playerHand;
	int *armyPieces;
	int *cityPieces;
	void placeNewArmies();
	void moveOverSea();
	void moveOverLand();
	void buildCities();
	void destroyArmy();
	//add hand to store past cards
	//add token counter for cities and armies decrement each placement, if killed you get it back
    IPlayerStrategy* behavior;

};

