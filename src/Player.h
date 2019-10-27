#pragma once
#include "Deck.h"
#include "BiddingFacility.h"
#include "Hand.h"
#include <vector>
#include <iostream>
#include "Utils.h"
#include <string>

/*
The Player of the game. Contains a player's name and age and a Bidding Facility. 
Player is able to read Cards and choose one action among them
Player is able to place bids and pay for cards.

*/

class Player
{
public:

	Player(int age, std::string name);
	~Player();
	void createCoinPurse(int numberOfPlayers);
	void readCard(Deck::Card gameCard);
	void payCoin(int cost);
	int getPlayerAge();
	void placeBid();
	int getBid();
	int getCoins();

private:
	std::vector<int> *countryList; 
	BiddingFacility *bidder;
	int *playerAge;
	std::string *playerName;
	void placeNewArmies();
	void moveOverSea();
	void moveOverLand();
	void buildCities();
	void destroyArmy();
	void doAction(Action action);

};

