#include "pch.h"
#pragma once

#include "Deck.h"
#include "Action.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Deck::Deck()
{	
	cards = new Card[NUMBER_OF_CARDS];
	generateCards();
}


Deck::~Deck()
{
	delete cards;
	delete drawCount;
	cards = NULL;
	drawCount = NULL;
}

Deck::Card Deck::draw()
{
	//std::cout << "\n numba: " << *drawCount << "\n";
	if (*drawCount < NUMBER_OF_CARDS)
	{
		//std::cout << "\n analiez : " << cards[*drawCount].actions[0].type << "\n";
		return cards[(*drawCount)++];
	}

}

void Deck::generateCards()
{
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		Card card;
		//srand(time(0));
		card.good = (Good)(rand() % 4);
		Action action1;
		action1.type =(ActionType) (rand() % 4);
		action1.amount = i;
		card.actions[0] = action1;
		Action action2;
		action2.amount = 1;
		card.numberOfActions = 1;

		if (true)
		{
			action2.type = (ActionType)(rand() % 4);
			card.numberOfActions = 2;
		}
		else
			action2.type = ActionType::null;

			
		card.actions[1] = action2;
		cards[i] = card;
	}
}