#include "pch.h"
#include "Player.h"


Player::Player(int age , std::string name)
{
	playerAge = new int(age);
	playerName = new std::string(name);
}

void Player::createCoinPurse(int numberofPlayers)
{
	bidder = new BiddingFacility(numberofPlayers);
}


Player::~Player()
{
	delete playerAge;
	playerAge = NULL;

	delete playerName;
	playerName = NULL;

	delete bidder;
	bidder = NULL;


}


void Player::readCard(Deck::Card gameCard)
{
	std::vector<Action> optionList;

	for (int i = 0; i <= Deck::MAX_ACTIONS_PER_CARD; i++)
		if (gameCard.actions[i].type != ActionType::null)
			optionList.push_back(gameCard.actions[i]);
		

	if (optionList.size() > 1)
	{
		int selection = 0;
		std::cout << "which action would you like to perform?" << *playerName <<  " \n";
		for (std::vector<Action>::iterator it = optionList.begin(); it != optionList.end(); it++)
		{
			std::cout << "[" << selection++ << "]" << Action::typeToString(it->type) << " " << it->amount << " times \n";
		}
		std::cin >> selection;
		selection =  Utils::validInputRange(0, optionList.size(), selection , "Invalid selection, please choose a value between 0 and " + optionList.size());
		doAction(optionList.at(selection));
	}
	else
		doAction(optionList.at(0));

}

void Player::doAction(Action action)
{

	for (int i = 1; i <= action.amount; i++)
	{
		switch (action.type)
		{
			case ActionType::moveGround: Player::moveOverLand(); break;
			case ActionType::moveSea: Player::moveOverSea(); break;
			case ActionType::build: Player::buildCities(); break;
			case ActionType::recruit: Player::placeNewArmies(); break;
			case ActionType::kill: Player::destroyArmy(); break;

			default: std::cout << "invalid action"; break;
		}
	}
}

void Player::moveOverLand()
{
	std::cout << "MOVING OVER LAND \n";
	
}

void Player::moveOverSea()
{
	std::cout << "MOVING OVER SEA \n";
}

void Player::buildCities()
{
	std::cout << "Build cities \n";
}

void Player::placeNewArmies()
{
	std::cout << "RECRUIT TROOPS \n";
}

void Player::destroyArmy()
{
	std::cout << " KILL ARMY \n";
}

void Player::placeBid()
{
	std::cout << *playerName << " ";
	bidder->placeBid();
}

void Player::payCoin(int cost)
{
	bidder->pay(cost);
}

int Player::getBid()
{
	return bidder->getCurrentBid();
}

int Player::getPlayerAge()
{
	return *playerAge;
}

int Player::getCoins()
{
	return bidder->getCoinPurse();
}