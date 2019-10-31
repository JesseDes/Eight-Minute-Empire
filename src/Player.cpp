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

void Player::readCard(Deck::Card *gameCard)
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
}

void Player::doAction(Action action)
{
	for (int i = 0; i < action.amount; i++)
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

    int selectionFrom;
    int selectionTo;
    
    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(this);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n" ;
    } 
    do {
        std::cout << "\nSelect a country to move a troop from: ";
        std::cin >> selectionFrom;

        if(MapLoader::GetMap()->country(selectionFrom)->getArmy(this) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    }while(MapLoader::GetMap()->country(selectionFrom)->getArmy(this) == 0);


    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLand(selectionFrom);
    
    std::cout << "These are the adjacent countries (by land only):" << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it){
        std::cout << " Country #" << *it << std::endl;
    };

    do {
        std::cout << "\nSelect country to move a troop to: ";
        std::cin >> selectionTo;
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end()) 
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    MapLoader::GetMap()->country(selectionTo)->addArmy(this);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(this);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(this);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;
}

void Player::moveOverSea()
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(this);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    do {
        std::cout << "\nSelect a country to move a troop from: ";
        std::cin >> selectionFrom;

        if (MapLoader::GetMap()->country(selectionFrom)->getArmy(this) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    } while (MapLoader::GetMap()->country(selectionFrom)->getArmy(this) == 0);

    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLandAndWater(selectionFrom);

    std::cout << "These are the adjacent countries(by land and water):" << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
    };
    do {
        std::cout << "\nSelect country to move a troop to: ";
        std::cin >> selectionTo;
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end()) 
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    MapLoader::GetMap()->country(selectionTo)->addArmy(this);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(this);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(this);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;
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