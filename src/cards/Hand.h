#pragma once
#include "Deck.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "../utils/Utils.h"
/*
Hand is a collection on 5 cards that players can exchange coins to recieve
*/

class Hand
{
public:
	Hand();
	~Hand();
	void AddCard(Card* card);  //Adds a card to the hand, will not add if the hand full
    Card* ViewCard(int cardIndex);	// Returns a card at a given index
	Card* Exchange(int cardIndex);	// Serves the player a card at the given index in the hand
	int GetCardCost(int cardInex);     //returns the cost associate with a certain index in the hand
	void ShowHand();	//outputs info of each card in the hand
	static const int SIZE_OF_HAND = 5;			//All numberes are 0 based 

private:
	std::vector<Card*> _cardList;
};

