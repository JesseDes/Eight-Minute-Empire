#pragma once
#include "Deck.h"
#include "Player.h"

class Player; //forward declaration 

class IPlayerStrategy {

public:
    virtual void placeBid(Player* player) = 0;
    virtual int getBid(Player* player) = 0;
};

class Human : public IPlayerStrategy {
public:
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
private:
    BiddingFacility *bidder;
};

class GreedyComputer : public IPlayerStrategy {
public:
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
private:
    int* bid;
};

class ModerateComputer : public IPlayerStrategy {
public:
    virtual void placeBid(Player* player);
    virtual int getBid(Player* player);
private:
    int* bid;
};