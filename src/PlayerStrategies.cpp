#include "PlayerStrategies.h"

//HUMAN

void Human::placeBid(Player* player)
{
    (*player).getBidder()->PlaceBid();
}
int Human::getBid(Player* player) {
    return (*player).getBidder()->GetCurrentBid();
}

//GREEDY COMPUTER

void GreedyComputer::placeBid(Player* player)
{
    bid = new int(0);
    std::cout << "Greedy computer bids " << *bid <<" coins\n\n";
}
int GreedyComputer::getBid(Player* player) {
    return *bid;
}

//MODERATE COMPUTER

void ModerateComputer::placeBid(Player* player)
{
    bid = new int(1);
    std::cout << "Moderate computer bids " << *bid << " coins\n\n";
}
int ModerateComputer::getBid(Player* player) {
    return *bid;
}