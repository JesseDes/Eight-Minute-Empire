#include "pch.h""
#include "Player.h"
#include "map.h"
#include "GameLoop.h"


Player::Player(int age , std::string name)
{
	_playerAge = new int(age);
	_playerName = new std::string(name);
	_playerHand = new int(0);
	_playerActions = new int(0);
    _behavior = 0;
}

void Player::CreateCoinPurse(int numberofPlayers)
{
	_bidder = new BiddingFacility(numberofPlayers);
	std::cout << _bidder->GetCoinPurse() << " coins start \n";
}

BiddingFacility* Player::GetBidder() {
    return _bidder;
}

Player::~Player()
{
	delete _playerAge;
	_playerAge = NULL;

	delete _playerName;
	_playerName = NULL;

	delete _bidder;
	_bidder = NULL;

	delete _countryList;
	_countryList = NULL;

	for (std::map<GoodType, int*>::iterator it = _goodMap.begin(); it != _goodMap.end(); it++)
	{
		delete it->second;
		it->second = NULL;
	}

	delete _armyPieces;
	_armyPieces = NULL;

	delete _cityPieces;
	_cityPieces = NULL;

	delete _playerHand;
	_playerHand = NULL;

	delete _playerActions;
	_playerActions = NULL;
}

void Player::ChooseCard(Hand *gameHand) {
    _behavior->ChooseCard(this, gameHand);
}

void Player::ReadCard(Card *gameCard)
{

	(*_playerHand)++;
	//incremets the good count in the map of goods
	if (_goodMap.find(gameCard->good) != _goodMap.end())
		(*_goodMap[gameCard->good])++;
	else
		_goodMap[gameCard->good] = new int(1);
	

	//prompts to select an action from the list
	std::cout << "which action would you like to perform " << *_playerName << "? \n";

    _behavior->ReadCard(this, gameCard);
}

void Player::DoAction(Action action)
{
	if(action.type != ActionType::null)
		(*_playerActions)++;

	for (int i = 0; i < action.amount; i++)
	{
		switch (action.type)
		{
			case ActionType::moveGround: Player::MoveOverLand(); break;
			case ActionType::moveSea: Player::MoveOverSea(); break;
			case ActionType::build: Player::BuildCities(); break;
			case ActionType::recruit: Player::PlaceNewArmies(); break;
			case ActionType::kill: Player::DestroyArmy(); break;
			case ActionType::null: break;

			default: std::cout << "invalid action"; break;
		}
	}
}

void Player::MoveOverLand()
{
    _behavior->MoveOverLand(this);
}

void Player::MoveOverSea()
{
    _behavior->MoveOverSea(this);
}

void Player::BuildCities()
{
    _behavior->BuildCities(this, _cityPieces);
}

void Player::PlaceNewArmies()
{
    _behavior->PlaceNewArmies(this, _armyPieces);
}

void Player::DestroyArmy()
{
    _behavior->DestroyArmy(this);
}

void Player::PlaceBid()
{
    _behavior->PlaceBid(this);
}

bool Player::PayCoin(int cost)
{
	if (cost <= _bidder->GetCoinPurse())
	{
		_bidder->Pay(cost);
		return true;
	}
	else
	{
		std::cout << "You can't afford it, you only have " << _bidder->GetCoinPurse() << " coins left \n";
		return false;
	}
}

int Player::GetBid()
{
    return _behavior->GetBid(this);
}

int Player::GetPlayerAge()
{
	return *_playerAge;
}

int Player::GetCoins()
{
	return _bidder->GetCoinPurse();
}

int Player::GetScore()
{
	int score = 0;
	
	int pointsFromGoods = GetGoodPoints();


    // adding a point to total score for every country this player is an owner of
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int pointsFromCountries=0;
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetOwner() == this)
            pointsFromCountries++;
    }

    // adding a point to total score for every country this player is an owner of
    int numberOfContinents = EmpireMap::instance()->getContinents();
    Continent* continent;
    int pointsFromContinents = 0;
    for (int j = 0; j < numberOfContinents; j++) {
        continent = EmpireMap::instance()->continent(j);
        continent->UpdateOwner();
        if (continent->GetOwner() == this)
            pointsFromContinents++;
    }

/*
    std::cout << "\n\nStats for player: " << this->getPlayerName() << std::endl
        << "Points from goods: " << pointsFromGoods << std::endl
        << "Points from countries: " << pointsFromCountries << std::endl
        << "Points from continents: " << pointsFromContinents << std::endl;
		*/
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
	_armyPieces = new int(armies);
	_cityPieces = new int(cities);
}

void Player::DrawArmyPiece()
{
	(*_armyPieces)++;
}

std::vector<int>* Player::GetCountries()
{
	delete _countryList;
	_countryList = new std::vector<int>();

	int numberOfCountries = EmpireMap::instance()->GetCountries();

	for (int i = 0; i < numberOfCountries; i++)
	{
		if (EmpireMap::instance()->country(i)->GetOwner() == this)
			_countryList->push_back(i);
	}
	return _countryList;
}

std::map<GoodType, int*>* Player::GetGoods()
{
	return &_goodMap;
}

void Player::SetPlayerStrategy(IPlayerStrategy* behavior) {
    this->_behavior = behavior;
}

IPlayerStrategy* Player::GetPlayerStrategy() {
    return _behavior;
}

void Player::PlaceShadowPlayer(Player *shadowPlayer)
{
	_behavior->PlaceShadowArmy(shadowPlayer);
}