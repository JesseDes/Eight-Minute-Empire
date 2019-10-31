#include "pch.h"
#pragma once

#include "Deck.h"
#include "Action.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>


Deck::Deck()
{	
	GenerateCards();
}


Deck::~Deck()
{
	for (auto& i : cards)
	{
		delete i;
		i = NULL;
	}

	delete drawCount;
	
	drawCount = NULL;
}

Deck::Card* Deck::Draw()
{
	if (*drawCount < NUMBER_OF_CARDS)
	{
		return cards[(*drawCount)++];
	}

}

void Deck::Shuffle()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::shuffle(cards.begin(), cards.end() , std::default_random_engine(seed));
}


void Deck::GenerateCards()
{
	for (int i = 0; i < NUMBER_OF_CARDS; i++)
	{
		Card *card = new Card();
		card->good = (GoodType)(rand() % 6);
		Action action1;
		action1.type =(ActionType) (rand() % 5);
		action1.amount = i % 3;
		card->actions[0] = action1;
		Action action2;
		action2.amount = 1;
		card->numberOfActions = 1;

		if (true)
		{
			action2.type = (ActionType)(rand() % 5);
			card->numberOfActions = 2;
		}
		else
			action2.type = ActionType::null;

			
		card->actions[1] = action2;
		cards[i] = card;
	}
}