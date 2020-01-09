#pragma once
#include "Deck.h"
#include "Player.h"

class Player; //forward declaration 
class Hand; //forward declaration 

class IPlayerStrategy {

public:
    virtual std::string PrintStrategyType() = 0;
    virtual void PlaceBid(Player* player) = 0;
    virtual int GetBid(Player* player) = 0;
    virtual void ChooseCard(Player* player, Hand *gameHand) = 0;
    virtual void ReadCard(Player* player, Card *gameCard) = 0;

    virtual void MoveOverLand(Player* player) = 0;
    virtual void MoveOverSea(Player* player) = 0;
    virtual void BuildCities(Player* player, int* cityPieces) = 0;
    virtual void PlaceNewArmies(Player* player, int* armyPieces) = 0;
    virtual void DestroyArmy(Player* player) = 0;
	virtual void PlaceShadowArmy(Player* player) = 0;
};

// human strategy forced user input for every decision
class Human : public IPlayerStrategy {
public:
    virtual std::string PrintStrategyType();
    virtual void PlaceBid(Player* player);
    virtual int GetBid(Player* player);
    virtual void ChooseCard(Player* player, Hand *gameHand);
    virtual void ReadCard(Player* player,Card *gameCard);

    virtual void MoveOverLand(Player* player);
    virtual void MoveOverSea(Player* player);
    virtual void BuildCities(Player* player, int* cityPieces);
    virtual void PlaceNewArmies(Player* player, int* armyPieces);
    virtual void DestroyArmy(Player* player);
	virtual void PlaceShadowArmy(Player* player);
};

//GreedyComputer strategy focuses on building cities and killing other players 
class GreedyComputer : public IPlayerStrategy {
public:
    virtual std::string PrintStrategyType();
    virtual void PlaceBid(Player* player);
    virtual int GetBid(Player* player);
    virtual void ChooseCard(Player* player, Hand *gameHand);
    virtual void ReadCard(Player* player,Card *gameCard);

    virtual void MoveOverLand(Player* player);
    virtual void MoveOverSea(Player* player);
    virtual void BuildCities(Player* player, int* cityPieces);
    virtual void PlaceNewArmies(Player* player, int* armyPieces);
    virtual void DestroyArmy(Player* player);
	virtual void PlaceShadowArmy(Player* player);
private:
    int* _bid;
};

//ModerateComputer strategy focuses on conquering land 
class ModerateComputer : public IPlayerStrategy {
public:
    virtual std::string PrintStrategyType();
    virtual void PlaceBid(Player* player);
    virtual int GetBid(Player* player);
    virtual void ChooseCard(Player* player, Hand *gameHand);
    virtual void ReadCard(Player* player,Card *gameCard);

    virtual void MoveOverLand(Player* player);
    virtual void MoveOverSea(Player* player);
    virtual void BuildCities(Player* player,int* cityPieces);
    virtual void PlaceNewArmies(Player* player, int* armyPieces);
    virtual void DestroyArmy(Player* player);
	virtual void PlaceShadowArmy(Player* player);
private:
    int* _bid;
};