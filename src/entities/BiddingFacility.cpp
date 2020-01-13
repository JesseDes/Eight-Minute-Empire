#include "../pch.h"
#include "BiddingFacility.h"

using namespace std;

int* BiddingFacility::COIN_SUPPLY = new int(40);

BiddingFacility::BiddingFacility()
{
	_coinCount = new int(14);
}

BiddingFacility::BiddingFacility(int numberOfPlayers)
{

	switch (numberOfPlayers)
	{
		case 2: _coinCount = new int(14); break;
		case 3: _coinCount = new int(11); break;
		case 4: _coinCount = new int(9); break;
		case 5: _coinCount = new int(8); break;
		default: _coinCount = new int(8);break;
	}

	*COIN_SUPPLY -= *_coinCount;
}


BiddingFacility::~BiddingFacility()
{
	delete _coinCount;
	delete _currentBid;

	_coinCount = NULL;
	_currentBid = NULL;
}

void BiddingFacility::PlaceBid()
{
	int bidAmount = -1;
	Utils::View("How much would you like to bid?");

	bidAmount = Utils::ValidInputRange(0, (int)*_coinCount, "please enter a bid between 0 and " + std::to_string((int)*_coinCount));

	_currentBid = new int(bidAmount);
}

void BiddingFacility::Pay(int payment)
{
	*_coinCount -= payment;
	*COIN_SUPPLY += payment;
}

int BiddingFacility::GetCurrentBid()
{
	return *_currentBid;
}

int BiddingFacility::GetCoinPurse()
{
	return *_coinCount;
}
