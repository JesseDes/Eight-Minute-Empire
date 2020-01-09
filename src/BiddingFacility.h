#pragma once
#include <iostream>
/*
A Bidding facility will keep track of the players finances how much they have bid.

*/


class BiddingFacility
{
public:
	BiddingFacility();
	BiddingFacility(int numberOfPlayers);
	~BiddingFacility();
	static int *COIN_SUPPLY;


	void PlaceBid(); //prompts the player to place bid and stores the value in currentBid
	void Pay(int amount); // deducts amount from coinCount
	int GetCurrentBid(); // returns currentBid
	int GetCoinPurse(); //retunrs coinCount

private:
	int *_coinCount;
	int *_currentBid;
};

