#pragma once
#include "Deck.h"
#include "Player.h"

class Player; //forward declaration 
class Hand; //forward declaration 

class IPlayerStrategy {

public:
    virtual std::string printStrategyType() = 0;
    virtual void placeBid(Player* player) = 0;
    virtual int getBid(Player* player) = 0;
    virtual void chooseCard(Player* player, Hand *gameHand) = 0;
    virtual void readCard(Player* player, Deck::Card *gameCard) = 0;

    virtual void moveOverLand(Player* player) = 0;
    virtual void moveOverSea(Player* player) = 0;
    virtual void buildCities(Player* player, int* cityPieces) = 0;
    virtual void placeNewArmies(Player* player, int* armyPieces) = 0;
    virtual void destroyArmy(Player* player) = 0;
};

// human strategy forced user input for every decision
class Human : public IPlayerStrategy {
public:
    virtual std::string printStrategyType();
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
    virtual void chooseCard(Player* player, Hand *gameHand);
    virtual void readCard(Player* player, Deck::Card *gameCard);

    virtual void moveOverLand(Player* player);
    virtual void moveOverSea(Player* player);
    virtual void buildCities(Player* player, int* cityPieces);
    virtual void placeNewArmies(Player* player, int* armyPieces);
    virtual void destroyArmy(Player* player);
};

//GreedyComputer strategy focuses on building cities and killing other players 
class GreedyComputer : public IPlayerStrategy {
public:
    virtual std::string printStrategyType();
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
    virtual void chooseCard(Player* player, Hand *gameHand);
    virtual void readCard(Player* player, Deck::Card *gameCard);

    virtual void moveOverLand(Player* player);
    virtual void moveOverSea(Player* player);
    virtual void buildCities(Player* player, int* cityPieces);
    virtual void placeNewArmies(Player* player, int* armyPieces);
    virtual void destroyArmy(Player* player);
private:
    int* bid;
};

//ModerateComputer strategy focuses on conquering land 
class ModerateComputer : public IPlayerStrategy {
public:
    virtual std::string printStrategyType();
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
    virtual void chooseCard(Player* player, Hand *gameHand);
    virtual void readCard(Player* player, Deck::Card *gameCard);

    virtual void moveOverLand(Player* player);
    virtual void moveOverSea(Player* player);
    virtual void buildCities(Player* player,int* cityPieces);
    virtual void placeNewArmies(Player* player, int* armyPieces);
    virtual void destroyArmy(Player* player);
private:
    int* bid;
};