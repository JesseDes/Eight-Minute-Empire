#include "../pch.h"
#include "Hand.h"
Hand::Hand()
{
}


Hand::~Hand()
{
	
	for (std::vector<Card*>::iterator it = _cardList.begin(); it != _cardList.end(); it++)
		(*it) = NULL; //Don't delete the content that is up to Deck to do
	
}

void Hand::AddCard(Card* card)
{		
	if (_cardList.size() <= SIZE_OF_HAND )
		_cardList.push_back(card);
}

Card* Hand::ViewCard(int cardIndex)
{
    Card *returnCard = _cardList.at(cardIndex);
    return returnCard;
}

Card* Hand::Exchange(int cardIndex)
{
	Card *returnCard;
	
	returnCard = _cardList.at(cardIndex);
	_cardList.erase(_cardList.begin() + cardIndex);

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
	std::ostringstream output;
	for (std::vector<Card*>::iterator it = _cardList.begin(); it != _cardList.end(); it++)
	{
		int index = std::distance(_cardList.begin(), it);
		output << "Card #" << index << " Cost : "<< GetCardCost(index) << " Good: " << Good::GoodToString((*it)->good) << " ";
		for (int i = 0; i < (*it)->numberOfActions; i++)
		{
			output << "Action " << Action::typeToString((*it)->actions[i].type) << " " << (*it)->actions[i].amount << " times ";
			
			if (i != (*it)->numberOfActions - 1)
			{
				if ((*it)->isAnd)
					output << " AND ";
				else
					output << " OR ";
			}
		}
		output << "\n";
	}

	Utils::View(output.str(),false);
}
