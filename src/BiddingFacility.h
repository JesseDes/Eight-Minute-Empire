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

	void placeBid();
	void pay(int amount);
	int getCurrentBid();
	int getCoinPurse();

private:
	int *coinCount;
	int *currentBid;
};

