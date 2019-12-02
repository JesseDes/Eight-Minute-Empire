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
	//deletes each card pointer and sets the pointer null. All cards MUST be deleted here and here alone
	for (auto& i : cards)
	{
		delete i;
		i = NULL;
	}

	delete drawCount;
	
	drawCount = NULL;
}

Card* Deck::Draw()
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
        int RandIndex = rand() % 4;
        Card *card;
        switch (RandIndex) {
            case 0: card = CardFactory::Create("wood"); break;
            case 1: card = CardFactory::Create("stone"); break;
            case 2: card = CardFactory::Create("food"); break;
            case 3: card = CardFactory::Create("gem"); break;
            case 4: card = CardFactory::Create("metal"); break;
            case 5: card = CardFactory::Create("wild"); break;
            default: card = CardFactory::Create("wood"); break;
        }

        card->draw();
		cards[i] = card;
	}
}