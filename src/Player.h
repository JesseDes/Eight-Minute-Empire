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
	void CreateCoinPurse(int numberOfPlayers);			//Gives players the number of coins based on the number of players
    void ChooseCard(Hand *gameHand);                    //player chooses a card from the deck
	void ReadCard(Card *gameCard);			//Player reads a card and selects an action to do based on the card
	void DoAction(Action action); //performs action: add/remove army, add city, travel by land/water an amount of times as specified by the action.amount attribute
	bool PayCoin(int cost);		//The player coinpurse is reduced by cost amount
	int GetPlayerAge();			// returns the age of the player
    BiddingFacility* GetBidder(); // returns the bidder
	void PlaceBid();			//calls the bidder to prompt the player to place a bid
	int GetBid();				// returns the players bid from the bidder
	int GetCoins();				// returns the coinPurse value from the bidder
	std::string GetPlayerName() { return *_playerName; };		// returns player name
	int GetScore();		//calculates the players score from their goods and territories 
	void GivePieces(int army, int cities);	//serves the player the number of board pieces they get
	void DrawArmyPiece();		//Adds an army piece to the player
	int GetGoodPoints();		//returns the points from goods alone
	std::vector<int>* GetCountries();	//Gets the countries that the player owns
	std::map<GoodType, int*>* GetGoods();		//gets a list of goods currently owned by the player
    void SetPlayerStrategy(IPlayerStrategy *behavior);	//Sets the player strategy of current player
    IPlayerStrategy* GetPlayerStrategy();	//returns the current player strategy
	void PlaceShadowPlayer(Player *shadowPlayer); // Player action to place the shadow players armies
	int GetCardCount() { return *_playerHand; }; // returns the number of cards the player has
	int GetActionCount() { return *_playerActions; }; // returns the number of actions the player has performed 

private:
	void PlaceNewArmies();
	void MoveOverSea();
	void MoveOverLand();
	void BuildCities();
	void DestroyArmy();

	std::vector<int> *_countryList; 
	std::map<GoodType, int*> _goodMap;
	std::string *_playerName;
	BiddingFacility *_bidder;
	int *_playerAge;
	int *_playerHand;
	int *_armyPieces;
	int *_cityPieces;
	int *_playerActions;
    IPlayerStrategy* _behavior;

};

