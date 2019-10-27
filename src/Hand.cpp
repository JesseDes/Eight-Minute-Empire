#include "pch.h"
#include "Hand.h"

Hand::Hand()
{
	cardList = new std::vector<Deck::Card>();
}


Hand::~Hand()
{
	delete cardList;
	cardList = NULL;
}

void Hand::addCard(Deck::Card card)
{		
	if (cardList->size() < SIZE_OF_HAND)
		cardList->push_back(card);
}

Deck::Card Hand::exchange(int cardIndex, int payment)
{
	Deck::Card returnCard;
	if (payment >= getCardCost(cardIndex))
	{
		returnCard = cardList->at(cardIndex);
		cardList->erase(cardList->begin() + cardIndex);
	}
	return returnCard;
}

int Hand::getCardCost(int index)
{
	switch (index)
	{
		case 0: return 0;
		case 1: return 1;
		case 2: return 1;
		case 3: return 2;
		case 4: return 2;
		case 5: return 3;

		default: return -1;
	}
}

void Hand::showHand()
{
	for (std::vector<Deck::Card>::iterator it = cardList->begin(); it != cardList->end(); it++)
	{
		std::cout << "Card #" << std::distance(cardList->begin(), it) << " Good: " << Utils::goodToString(it->good) << " ";

		for (int i = 0; i < it->numberOfActions; i++)
			std::cout << "Action " << Action::typeToString(it->actions[i].type) << " " << it->actions[i].amount << " times ";

		std::cout << "\n";
	}
}
