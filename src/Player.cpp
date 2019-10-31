#include "pch.h""
#include "Player.h"
#include "map.h"
#include "GameLoop.h"


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

Action Player::readCard(Deck::Card *gameCard)
{
	if (_goodMap.find(gameCard->good) != _goodMap.end())
		(*_goodMap[gameCard->good])++;
	else
		_goodMap[gameCard->good] = new int(1);
	
	std::vector<Action> optionList;

	for (int i = 0; i <= Deck::MAX_ACTIONS_PER_CARD; i++)
		if (gameCard->actions[i].type != ActionType::null)
			optionList.push_back(gameCard->actions[i]);	

	int selection = 0;

    // TODO: check if there is more than 1 action 

	std::cout << "which action would you like to perform?" << *playerName <<  " \n";
	for (std::vector<Action>::iterator it = optionList.begin(); it != optionList.end(); it++)
		std::cout << "[" << selection++ << "]" << Action::typeToString(it->type) << " " << it->amount << " times \n";
		
	std::cout << "[" << selection << "]" << "Do Nothing \n";
	std::cin >> selection;
	selection =  Utils::validInputRange(0, optionList.size(), selection , "Invalid selection, please choose a value between 0 and " + optionList.size());
	if(selection != optionList.size())
		doAction(optionList.at(selection));

    return gameCard->actions[selection];
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
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;

    int selection;
    std::cout << "Select which country you want a troop to move from:" << std::endl;

    for (int i = 0; i < numberOfCountries; i++) {

        country = MapLoader::GetMap()->country(i);
        army = country->getArmy(this);

        std::cout << " - You have " << army << " troops in country" << "[#" << i << "]" << std::endl;
    } 
    std::cin >> selection;

    std::cout << "Select one of the adjacent countries to move this troop:" << std::endl;
    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLand(selection);
    
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it){
        std::cout << " Country #" << *it << std::endl;
    };
    std::cin >> selection;

    // TODO: remove troop from existing and add troop to new 
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

bool Player::payCoin(int cost)
{
	if (cost <= bidder->getCoinPurse())
	{
		bidder->pay(cost);
		return true;
	}
	else
		return false;
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

int Player::getScore()
{
	int score = 0;
	
	for (std::map<GoodType, int*>::iterator it = _goodMap.begin(); it != _goodMap.end(); it++)
		score += Good::GoodToScore(it->first, *it->second);

	//TODO: add score players get from map
	return score;
}