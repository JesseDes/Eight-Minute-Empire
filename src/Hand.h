#pragma once
#include "Deck.h"
#include <vector>
#include <iostream>
/*
Hand is a collection on 5 cards that players can exchange coins to recieve
*/

class Hand
{
public:
	Hand();
	~Hand();
	void addCard(Deck::Card* card);
	Deck::Card* exchange(int cardIndex);
	int getCardCost(int cardInex);
	void showHand();
	static const int SIZE_OF_HAND = 5;			//All numberes are 0 based 

private:
	std::vector<Deck::Card*> cardList;
};

