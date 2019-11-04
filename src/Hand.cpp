#include "pch.h"
#include "Hand.h"

Hand::Hand()
{
}


Hand::~Hand()
{
	
	for (std::vector<Deck::Card*>::iterator it = cardList.begin(); it != cardList.end(); it++)
		(*it) = NULL; //Don't delete the content that is up to Deck to do
	
}

void Hand::AddCard(Deck::Card* card)
{		
	if (cardList.size() <= SIZE_OF_HAND )
		cardList.push_back(card);
}

Deck::Card* Hand::Exchange(int cardIndex)
{
	Deck::Card *returnCard;
	
	returnCard = cardList.at(cardIndex);
	cardList.erase(cardList.begin() + cardIndex);

	return returnCard;
}

int Hand::GetCardCost(int index)
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

void Hand::ShowHand()
{
	for (std::vector<Deck::Card*>::iterator it = cardList.begin(); it != cardList.end(); it++)
	{
		int index = std::distance(cardList.begin(), it);
		std::cout << "Card #" << index << " Cost : "<< GetCardCost(index) << " Good: " << Good::GoodToString((*it)->good) << " ";

		for (int i = 0; i < (*it)->numberOfActions; i++)
			std::cout << "Action " << Action::typeToString((*it)->actions[i].type) << " " << (*it)->actions[i].amount << " times ";

		std::cout << "\n";
	}
}
