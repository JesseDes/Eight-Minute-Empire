#pragma once
#include <String>
#include "Action.h"
#include "Good.h"
#include <array>

/*
Deck is a class that will generate a list of Card objects
Cards are a class that contains a Good and a list of doable actions for the player.
*/

class Deck{
	public:
	static const int NUMBER_OF_CARDS = 41;		//All numbers are 0 based
	static const int MAX_ACTIONS_PER_CARD = 1;

		struct Card{
			int numberOfActions;
			GoodType good;
			Action actions[MAX_ACTIONS_PER_CARD + 1];
			Card() {}
		};

		Deck();
		//Deck(std::string deckSource);
		~Deck();
		Card* Draw();
		void Shuffle();

	private :
		void GenerateCards();
		std::array<Deck::Card*, NUMBER_OF_CARDS> cards;
		int *drawCount = new int(0);
};