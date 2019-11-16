#include "pch.h""
#include "Player.h"
#include "map.h"
#include "GameLoop.h"


Player::Player(int age , std::string name)
{
	playerAge = new int(age);
	playerName = new std::string(name);
	playerHand = new Hand();
    behavior = 0;
}

void Player::createCoinPurse(int numberofPlayers)
{
	bidder = new BiddingFacility(numberofPlayers);
	std::cout << bidder->GetCoinPurse() << " coins start \n";
}

BiddingFacility* Player::getBidder() {
    return bidder;
}

Player::~Player()
{
	delete playerAge;
	playerAge = NULL;

	delete playerName;
	playerName = NULL;

	delete bidder;
	bidder = NULL;

	delete countryList;
	countryList = NULL;

	for (std::map<GoodType, int*>::iterator it = _goodMap.begin(); it != _goodMap.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	delete armyPieces;
	armyPieces = NULL;

	delete cityPieces;
	cityPieces = NULL;

	delete playerHand;
	playerHand = NULL;
}

void Player::chooseCard(Hand *gameHand) {
    behavior->chooseCard(this, gameHand);
}

void Player::readCard(Deck::Card *gameCard)
{

	playerHand->AddCard(gameCard);
	//incremets the good count in the map of goods
	if (_goodMap.find(gameCard->good) != _goodMap.end())
		(*_goodMap[gameCard->good])++;
	else
		_goodMap[gameCard->good] = new int(1);
	

	//prompts to select an action from the list
	std::cout << "which action would you like to perform " << *playerName << "? \n";

    behavior->readCard(this, gameCard);
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
			case ActionType::null: break;

			default: std::cout << "invalid action"; break;
		}
	}
}

void Player::moveOverLand()
{
    behavior->moveOverLand(this);
}

void Player::moveOverSea()
{
    behavior->moveOverSea(this);
}

void Player::buildCities()
{
    behavior->buildCities(this, cityPieces);
}

void Player::placeNewArmies()
{
    behavior->placeNewArmies(this, armyPieces);
}

void Player::destroyArmy()
{
    behavior->destroyArmy(this);
}

void Player::placeBid()
{
    behavior->placeBid(this);
}

bool Player::payCoin(int cost)
{
	if (cost <= bidder->GetCoinPurse())
	{
		bidder->Pay(cost);
		return true;
	}
	else
	{
		std::cout << "You can't afford it, you only have " << bidder->GetCoinPurse() << " coins left \n";
		return false;
	}
}

int Player::getBid()
{
    return behavior->getBid(this);
}

int Player::getPlayerAge()
{
	return *playerAge;
}

int Player::getCoins()
{
	return bidder->GetCoinPurse();
}

int Player::getScore()
{
	int score = 0;
	
	int pointsFromGoods = GetGoodPoints();


    // adding a point to total score for every country this player is an owner of
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int pointsFromCountries=0;
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getOwner() == this)
            pointsFromCountries++;
    }

    // adding a point to total score for every country this player is an owner of
    int numberOfContinents = MapLoader::GetMap()->getContinents();
    Continent* continent;
    int pointsFromContinents = 0;
    for (int j = 0; j < numberOfContinents; j++) {
        continent = MapLoader::GetMap()->continent(j);
        continent->updateOwner();
        if (continent->getOwner() == this)
            pointsFromContinents++;
    }


    std::cout << "\n\nStats for player: " << this->getPlayerName() << std::endl
        << "Points from goods: " << pointsFromGoods << std::endl
        << "Points from countries: " << pointsFromCountries << std::endl
        << "Points from continents: " << pointsFromContinents << std::endl;

	return (pointsFromGoods + pointsFromCountries);
}

int Player::GetGoodPoints()
{

	int pointsFromGoods = 0;
	for (std::map<GoodType, int*>::iterator it = _goodMap.begin(); it != _goodMap.end(); it++)
		pointsFromGoods += Good::GoodToScore(it->first, *it->second);

	return pointsFromGoods;
}

void Player::GivePieces(int armies, int cities)
{
	armyPieces = new int(armies);
	cityPieces = new int(cities);
}

void Player::DrawArmyPiece()
{
	(armyPieces)++;
}

std::vector<int>* Player::GetCountries()
{
	delete countryList;
	countryList = new std::vector<int>();

	int numberOfCountries = MapLoader::GetMap()->getCountries();

	for (int i = 0; i < numberOfCountries; i++)
	{
		if (MapLoader::GetMap()->country(i)->getOwner() == this)
			countryList->push_back(i);
	}
	return countryList;
}

std::map<GoodType, int*>* Player::GetGoods()
{
	return &_goodMap;
}

void Player::setPlayerStrategy(IPlayerStrategy* behavior) {
    this->behavior = behavior;
}