#include "PlayerStrategies.h"

//HUMAN

void Human::placeBid(Player* player)
{
    (*player).getBidder()->PlaceBid();
}
int Human::getBid(Player* player) {
    return (*player).getBidder()->GetCurrentBid();
}

void Human::chooseCard(Player* player,Hand * gameHand)
{
    int chosenCard;
    do
    {
        std::cin >> chosenCard;
        chosenCard = Utils::validInputRange(0, gameHand->SIZE_OF_HAND, chosenCard, "Invalid Selection Please choose a card from the list above");

    } while (!(player)->payCoin(gameHand->GetCardCost(chosenCard)));

    //reads card and performs action
    (player)->readCard(gameHand->Exchange(chosenCard));
}

//GREEDY COMPUTER (focused on building cities and destroying opponents)

void GreedyComputer::placeBid(Player* player)
{
    bid = new int(0);
    std::cout << "Greedy computer bids " << *bid <<" coins\n\n";
}
int GreedyComputer::getBid(Player* player) {
    return *bid;
}

void GreedyComputer::chooseCard(Player* player, Hand * gameHand)
{
    /* Implementing the following check:
        1) bot will look for a card that has either "build city" or "kill enemy" returning the least expensive card
        2) If bot cannot afford the card, it will opt for the free card
    */

    int chosenCard=0;

    for (int i=4; i >= 0; i--) {
        for (int j=0; j < 2; j++) {
            ActionType type = gameHand->ViewCard(i)->actions[j].type;
            if (type == ActionType::kill) {
                std::cout << "Found A KILL at card " << i << " \n";
                chosenCard = i;
            }
            else if (type == ActionType::build) {
                std::cout << "Found A BUILD at card " << i << " \n";
                chosenCard = i;
            }
        }
    }
     
    if (!(player)->payCoin(gameHand->GetCardCost(chosenCard))) {
        chosenCard = 0;
    }

    //reads card and performs action
    (player)->readCard(gameHand->Exchange(chosenCard));
}

//MODERATE COMPUTER (focused conquering land)

void ModerateComputer::placeBid(Player* player)
{
    bid = new int(1);
    std::cout << "Moderate computer bids " << *bid << " coins\n\n";
}
int ModerateComputer::getBid(Player* player) {
    return *bid;
}

void ModerateComputer::chooseCard(Player* player, Hand * gameHand)
{
    /* Implementing the following check:
        1) bot will look for a card that has either "move by land" or "move by sea" returning the least expensive card
        2) If bot cannot afford the card, it will opt for the free card

        TODO: implement better logic:
        1) If the number of countries player owns is equal to the number of troops, bot will look for a card to recruit troop starting from cheapest
        2) If player cannot find a card it will opt for the cheapest
        3) If bot has more troops than land, it will look for a card that has either "move by land" or "move by sea" starting from the least expensive
        4) If bot cannot afford the card, it will opt for the free card
    */

    int chosenCard = 0;


    for (int i = 4; i >= 0; i--) {
        for (int j = 0; j < 2; j++) {
            ActionType type = gameHand->ViewCard(i)->actions[j].type;
            if (type == ActionType::moveSea) {
                std::cout << "found MOVE BY SEA at card [" << i << "]\n";
                chosenCard = i;
            }
            else if (type == ActionType::moveGround) {
                std::cout << "found MOVE BY GROUND at card [" << i << "]\n";
                chosenCard = i;
            }
        }
    }

    if (!(player)->payCoin(gameHand->GetCardCost(chosenCard))) {
        chosenCard = 0;
    }

    //reads card and performs action
    (player)->readCard(gameHand->Exchange(chosenCard));
}
