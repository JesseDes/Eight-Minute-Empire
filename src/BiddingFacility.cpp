#include "pch.h"
#include "BiddingFacility.h"
#include "Utils.h"

using namespace std;

int* BiddingFacility::COIN_SUPPLY = new int(40);

BiddingFacility::BiddingFacility()
{
	coinCount = new int(14);
}

BiddingFacility::BiddingFacility(int numberOfPlayers)
{

	switch (numberOfPlayers)
	{
		case 2: coinCount = new int(14); break;
		case 3: coinCount = new int(11); break;
		case 4: coinCount = new int(9); break;
		case 5: coinCount = new int(8); break;
		default: coinCount = new int(8);break;
	}

	*COIN_SUPPLY -= *coinCount;
}


BiddingFacility::~BiddingFacility()
{
	delete coinCount;
	delete currentBid;

	coinCount = NULL;
	currentBid = NULL;
}

void BiddingFacility::PlaceBid()
{
	int bidAmount = -1;
	std::cout << "How much would you like to bid? \n";

	bidAmount = Utils::validInputRange(0, (int)*coinCount, "please enter a bid between 0 and " + std::to_string((int)*coinCount));

	currentBid = new int(bidAmount);
}

void BiddingFacility::Pay(int payment)
{
	*coinCount -= payment;
	*COIN_SUPPLY += payment;
}

int BiddingFacility::GetCurrentBid()
{
	return *currentBid;
}

int BiddingFacility::GetCoinPurse()
{
	return *coinCount;
}
