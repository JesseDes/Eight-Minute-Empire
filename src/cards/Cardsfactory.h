
#include <String>
#include "Action.h"
#include "Good.h"
#include <array>


class Card {
public:
    virtual void Draw() = 0;
    Action actions[2];
    GoodType good;
    int numberOfActions;
    bool isAnd;
};

class Wood : public Card {
public:
    virtual void Draw();
};

class Stone : public Card {
public:
    virtual void Draw();
};

class Food : public Card {
public:
    virtual void Draw();
};

class Gem : public Card {
public:
    virtual void Draw();
};

class Metal : public Card {
public:
    virtual void Draw();
};

class Wild : public Card {
public:
    virtual void Draw();
};



class CardFactory {
public:
    static Card* Create(std::string type) {
        if (type == "wood") return new Wood();
        if (type == "stone") return new Food();
        if (type == "food") return new Gem();
        if (type == "gem") return new Metal();
        if (type == "metal") return new Metal();
        if (type == "wild") return new Wild();
        return NULL;
    }
private:
    CardFactory() {};
};