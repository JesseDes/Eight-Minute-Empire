#pragma once
#include <String>
#include "Action.h"
#include "Good.h"
#include <array>
#include "Cardsfactory.h"


/*
Deck is a class that will generate a list of Card objects
Cards are a class that contains a Good and a list of doable actions for the player.
*/

class Deck{
public:
	static const int NUMBER_OF_CARDS = 41;		//All numbers are 0 based
	static const int MAX_ACTIONS_PER_CARD = 1;

	Deck();
	//Deck(std::string deckSource);
	~Deck();
	Card* Draw();		//Draws 1 card from the cards array and increments drawCount;
	void Shuffle();		// Shuffles the cards array 

private :
	void GenerateCards(); //creates random cards to fill the deck
	std::array<Card*, NUMBER_OF_CARDS> _cards;
	int *_drawCount = new int(0);
};