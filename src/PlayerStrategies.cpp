#include "PlayerStrategies.h"
#include "Country.h"
#include "MapLoader.h"
#include "Testers.h"
#include "GameLoop.h"
#include <stdlib.h>     

//HUMAN

std::string Human::PrintStrategyType() {
    return "Human";
}
void Human::PlaceBid(Player* player)
{
    (*player).GetBidder()->PlaceBid();
}

int Human::GetBid(Player* player) {
    return (*player).GetBidder()->GetCurrentBid();
}

void Human::ChooseCard(Player* player,Hand * gameHand)
{
    int chosenCard;
    do
    {
        chosenCard = Utils::ValidInputRange(0, gameHand->SIZE_OF_HAND,  "Invalid Selection Please choose a card from the list above");

    } while (!(player)->PayCoin(gameHand->GetCardCost(chosenCard)));

    //reads card and performs action
    (player)->ReadCard(gameHand->Exchange(chosenCard));
}

void Human::ReadCard(Player * player, Card * gameCard)
{

    //prompts to select an action from the list

    int selection = 0;

    if (gameCard->isAnd)
    {
        std::cout << "[0]";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
            std::cout << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
                std::cout << " AND ";
        }
        std::cout << "\n[1] Do nothing \n";

        selection = Utils::ValidInputRange(0, 1,  "Invalid selection, please choose a value between 0 and 1");

        if (selection == 0)
        {
            for (int i = 0; i < gameCard->numberOfActions; i++)
                (*player).DoAction(gameCard->actions[i]);
        }
    }
    else
    {
        Action nothing;
        nothing.type = ActionType::null;
        nothing.amount = 0;
        std::vector<Action> optionList;

        //loads all actions into a list

        for (int i = 0; i <= Deck::MAX_ACTIONS_PER_CARD; i++)
            if (gameCard->actions[i].type != ActionType::null)
                optionList.push_back(gameCard->actions[i]);

        optionList.push_back(nothing);


        for (std::vector<Action>::iterator it = optionList.begin(); it != optionList.end(); it++)
            std::cout << "[" << selection++ << "]" << Action::typeToString(it->type) << " " << it->amount << " times \n";

        selection = Utils::ValidInputRange(0, optionList.size() - 1,  "Invalid selection, please choose a value between 0 and " + optionList.size());

        (*player).DoAction(optionList.at(selection));
    }
}

void Human::MoveOverLand(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;
    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
        }
    }
    do {
        std::cout << "\n Select a country to move a troop from: ";
        selectionFrom = Utils::ValidInputRange(0, numberOfCountries - 1, "please select a valid country");

        if (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    } while (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0);


    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLand(selectionFrom);

    std::cout << "These are the adjacent countries (by land only): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
    };

    do {
        std::cout << "\nSelect country to move a troop to: ";
        selectionTo = Utils::ValidInputRange(0,adjacent.size(),"You cannot travel there from the selected country, choose an adjacent country.");
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selectionTo)->UpdateOwner();
    EmpireMap::instance()->country(selectionFrom)->UpdateOwner();
}

void Human::MoveOverSea(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;
    int selectionFrom;
    int selectionTo;
    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
        }
    }
    do {
        std::cout << "\nSelect a country to move a troop from: ";
        selectionFrom = Utils::ValidInputRange(0, numberOfCountries - 1 ,"Please select a valid country");

        if (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    } while (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0);

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLandAndWater(selectionFrom);

    std::cout << "These are the adjacent countries(by land and water): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
    };
    do {
        std::cout << "\nSelect country to move a troop to: ";
        selectionTo = Utils::ValidInputRange(0,adjacent.size(),"You cannot travel there from the selected country, choose an adjacent country");
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selectionTo)->UpdateOwner();
    EmpireMap::instance()->country(selectionFrom)->UpdateOwner();
}

void Human::BuildCities(Player * player, int* cityPieces)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int selection;
    std::cout << "\nThese are the countries you have troops or cities in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities \n";
        }
    }
    do {
        std::cout << "\nSelect a country to build a city in: ";
        selection = Utils::ValidInputRange(0, numberOfCountries - 1 , "Please Select a valid Country");

        if (EmpireMap::instance()->country(selection)->GetTotalUnits(player) == 0)
            std::cout << "\nYou need at least 1 unit to build here, choose another country: ";
    } while (EmpireMap::instance()->country(selection)->GetTotalUnits(player) == 0);

    if (cityPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddCity(player);
        (*cityPieces)--;
    }
    else
        std::cout << "You are out of city pieces";

    std::cout << "\nUpdated cities & troops info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities \n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selection)->UpdateOwner();
}

void Human::PlaceNewArmies(Player * player, int* armyPieces)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int selection;
    std::cout << "\nThese are the countries you can place troops (cities and starting region): \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetCities(player) > 0 || j == EmpireMap::instance()->GetStartingCountry()->GetCountryName()) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities\n";
        }
    }
    std::cout << "Country [" << EmpireMap::instance()->GetStartingCountry()->GetCountryName() << "] - is the starting region ";

    do {
        std::cout << "\nSelect a country to place a troop in: ";
		selection = Utils::ValidInputRange(0,numberOfCountries - 1 , "Please choose a valid country to place your troops");

        if (EmpireMap::instance()->country(selection)->GetCities(player) == 0 && selection != EmpireMap::instance()->GetStartingCountry()->GetCountryName())
            std::cout << "\nYou can only place a troop at the starting region or countries that you have cities in, choose again: ";

    } while (EmpireMap::instance()->country(selection)->GetCities(player) == 0 && selection != EmpireMap::instance()->GetStartingCountry()->GetCountryName());

    if (armyPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddArmy(player);
        (*armyPieces)--;
    }
    else
        std::cout << "You are out of army pieces";

    std::cout << "\nYour updated troops: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetCities(player) > 0 || j == EmpireMap::instance()->GetStartingCountry()->GetCountryName()) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selection)->UpdateOwner();
}

void Human::DestroyArmy(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int playerSelection;
    int countrySelection;
    std::vector<Player*> playerList = GameLoop::GetPlayerList(); // TODO: in GameLoop we have to replace with this -> GameLoop::getPlayerList();

    std::cout << "\nPlayers List: \n\n";

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
        std::cout << "[" << index << "]: " << (*it)->GetPlayerName() << std::endl;
    }

    std::cout << "\nWhich player would you like to target?: ";
    playerSelection = Utils::ValidInputRange(0, playerList.size() - 1 ,"Please select a valid player option to target");
    std::cout << "\nList of countries that target player has troops in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->GetArmy(playerList[playerSelection]) << " troops\n";
        }
    }

    std::cout << "\nWhich country would you like to target?: ";

	do {
		countrySelection = Utils::ValidInputRange(0, numberOfCountries - 1,"Please select a valid country to target");
		if ( EmpireMap::instance()->country(countrySelection)->GetArmy(playerList[playerSelection]) == 0)
			std::cout << "\n Target doesn't have any troops there, choose another country: ";
	} while (EmpireMap::instance()->country(countrySelection)->GetArmy(playerList[playerSelection]) == 0 );

    EmpireMap::instance()->country(countrySelection)->RemoveArmy(playerList[playerSelection]);


    std::cout << "\n\nUpdated troops of target player: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->GetArmy(playerList[playerSelection]) << " troops\n\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(countrySelection)->UpdateOwner();
}

void Human::PlaceShadowArmy(Player* shadowPlayer)
{
	int numberOfCountries = EmpireMap::instance()->GetCountries();
	Country* country;
	for (int j = 0; j < numberOfCountries; j++)
	{
		country = EmpireMap::instance()->country(j);
		std::cout << "Country [" << j << "] Shadow Player has " << country->GetArmy(shadowPlayer) << " troops \n";

	}

	int selection;
	selection = Utils::ValidInputRange(0, numberOfCountries - 1, "please choose a value between 0 and " + (numberOfCountries - 1));

	EmpireMap::instance()->country(selection)->AddArmy(shadowPlayer);
}



//GREEDY COMPUTER (focused on building cities and destroying opponents)

std::string GreedyComputer::PrintStrategyType() {
    return "GreedyComputer";
}

void GreedyComputer::PlaceBid(Player* player)
{
    _bid = new int(0);
    std::cout <<" bids " << *_bid <<" coins\n\n";
}

int GreedyComputer::GetBid(Player* player) {
    return *_bid;
}

void GreedyComputer::ChooseCard(Player* player, Hand * gameHand)
{
    /* Implementing the following check:
        1) bot will look for a card that has either "build city" or "kill enemy" returning the least expensive card
        2) If bot cannot afford the card, it will opt for the free card
    */

    int chosenCard=0;
    int index = 0;

    for (int i=4; i >= 0; i--) {
        for (int j=0; j < 2; j++) {
            ActionType type = gameHand->ViewCard(i)->actions[j].type;
            if (type == ActionType::kill) {
                std::cout << "Found KILL at card [" << i << "] at index ["<<j<<"] \n";
                chosenCard = i;
            }
            else if (type == ActionType::build) {
                std::cout << "Found BUILD at card [" << i << "] at index [" << j << "] \n";
                chosenCard = i;
            }
        }
    }
     
    if (!(player)->PayCoin(gameHand->GetCardCost(chosenCard))) {
        chosenCard = 0;
    }

    //reads card and performs action
    (player)->ReadCard(gameHand->Exchange(chosenCard));
}

void GreedyComputer::ReadCard(Player * player, Card * gameCard)
{
    int selection = 0;

    if (gameCard->isAnd)
    {
        std::cout <<(*player).GetPlayerName()<< " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
            std::cout << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
                std::cout << " AND ";
        }

        for (int i = 0; i < gameCard->numberOfActions; i++)
            (*player).DoAction(gameCard->actions[i]);
        
        return;
    }
    else
    {

        for (int i = 0; i <= Deck::MAX_ACTIONS_PER_CARD; i++) {

            if (gameCard->actions[i].type == ActionType::kill)
                selection = i;
            else if (gameCard->actions[i].type == ActionType::build)
                selection = i;
        }

        std::cout << (*player).GetPlayerName() << " chose: ";
        std::cout << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).DoAction(gameCard->actions[selection]);
    }
}

void GreedyComputer::MoveOverLand(Player * player)
{
    // Currently, bot will never opt to move over land
}

void GreedyComputer::MoveOverSea(Player * player)
{
    // Currently, bot will never opt to move over land
}

void GreedyComputer::BuildCities(Player * player, int* cityPieces)
{
    //Bot's behavior will be add a city on a land it has an army on

    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int selection = -1;

    std::cout << "\nThese are the countries you have troops or cities in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities \n";
            selection = j; 
        }
    }
    std::cout << "\nPlayer decided to build on country ["<< selection << "]\n\n";

	if(selection < 0)
		return;

    if (cityPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddCity(player);
        (*cityPieces)--;
    }
    else
        std::cout << "You are out of city pieces";

    std::cout << "\nUpdated cities & troops info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->GetArmy(player) << " troops, and " << country->GetCities(player) << " cities \n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selection)->UpdateOwner();
}

void GreedyComputer::PlaceNewArmies(Player * player, int* armyPieces)
{
    //currently, bot will never opt to place new armies
}

void GreedyComputer::DestroyArmy(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int playerSelection;
    int countrySelection = -1;

    std::vector<Player*> playerList = GameLoop::GetPlayerList(); // TODO: in GameLoop we have to replace with this -> GameLoop::getPlayerList();

    std::cout << "\nPlayers List: \n\n";

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
        std::cout << "[" << index << "]: " << (*it)->GetPlayerName() << std::endl;
        if ((*it)->GetPlayerName() != player->GetPlayerName()) {
            playerSelection = index;
        }
    }

	if (countrySelection < 0)
		return;

    std::cout << "\nPlayer decided to kill [" << playerSelection << "]\n\n";



    std::cout << "\nList of countries that target player has troops in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->GetArmy(playerList[playerSelection]) << " troops\n";
            countrySelection = j;
        }
    }
	if (countrySelection < 0)
		return;


    std::cout << "\nPlayer decided to kill on country [" << countrySelection << "]\n\n";

    EmpireMap::instance()->country(countrySelection)->RemoveArmy(playerList[playerSelection]);

    std::cout << "\n\nUpdated troops of target player: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->GetArmy(playerList[playerSelection]) << " troops\n\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(countrySelection)->UpdateOwner();
}

void GreedyComputer::PlaceShadowArmy(Player *shadowPlayer)
{
	int countrySelection = rand() % (EmpireMap::instance()->GetCountries() - 1);
	Utils::View("Placing army at country" + std::to_string(countrySelection) );
	EmpireMap::instance()->country(countrySelection)->AddArmy(shadowPlayer);

}

//MODERATE COMPUTER (focused conquering land)

std::string ModerateComputer::PrintStrategyType() {
    return "ModerateComputer";
}

void ModerateComputer::PlaceBid(Player* player)
{
    _bid = new int(1);
    std::cout  << " bids " << *_bid << " coins\n\n";
}

int ModerateComputer::GetBid(Player* player) {
    return *_bid;
}

void ModerateComputer::ChooseCard(Player* player, Hand * gameHand)
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
                std::cout << "found MOVE BY SEA at [" << i << "] at index [" << j << "] \n";
                chosenCard = i;
            }
            else if (type == ActionType::moveGround) {
                std::cout << "found MOVE BY GROUND at card [" << i << "] at index [" << j << "] \n";
                chosenCard = i;
            }
        }
    }

    if (!(player)->PayCoin(gameHand->GetCardCost(chosenCard))) {
        chosenCard = 0;
    }

    //reads card and performs action
    (player)->ReadCard(gameHand->Exchange(chosenCard));
}

void ModerateComputer::ReadCard(Player * player, Card * gameCard)
{
    int selection = 0;

    if (gameCard->isAnd)
    {
        std::cout << (*player).GetPlayerName() << " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
            std::cout << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
                std::cout << " AND ";
        }

        for (int i = 0; i < gameCard->numberOfActions; i++)
            (*player).DoAction(gameCard->actions[i]);

        return;
    }
    else
    {

        for (int i = 0; i <= Deck::MAX_ACTIONS_PER_CARD; i++) {

            if (gameCard->actions[i].type == ActionType::moveSea)
                selection = i;
            else if (gameCard->actions[i].type == ActionType::moveGround)
                selection = i;
        }

        std::cout << (*player).GetPlayerName() << " chose: ";
        std::cout << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).DoAction(gameCard->actions[selection]);
    }
}

void ModerateComputer::MoveOverLand(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;

    int selectionFrom = -1;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
            selectionFrom = j; 
        }
    }
	if (selectionFrom < 0)
		return;

    std::cout << "\nPlayer is moving from: [" << selectionFrom << "]\n\n";

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLand(selectionFrom);

    std::cout << "These are the adjacent countries (by land only): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
        selectionTo = *it;
    };

    std::cout << "\nPlayer moved to: [" << selectionFrom << "]\n\n";

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

    std::cout << "\nThis is your updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selectionTo)->UpdateOwner();
    EmpireMap::instance()->country(selectionFrom)->UpdateOwner();
}

void ModerateComputer::MoveOverSea(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;

    int selectionFrom = - 1;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
            selectionFrom = j;
        }
    }
	
	if (selectionFrom < 0)
		return;


    std::cout << "\nPlayer is moving from: [" << selectionFrom << "]\n\n";

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLandAndWater(selectionFrom);

    std::cout << "These are the adjacent countries (by land and water): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
        selectionTo = *it;
    };

    std::cout << "\nPlayer moved to: [" << selectionFrom << "]\n\n";

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

    std::cout << "\nThis is your updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    EmpireMap::instance()->country(selectionTo)->UpdateOwner();
    EmpireMap::instance()->country(selectionFrom)->UpdateOwner();
}

void ModerateComputer::BuildCities(Player * player, int* cityPieces)
{
    // Currently, bot will never opt to move over land
}

void ModerateComputer::PlaceNewArmies(Player * player, int* armyPieces)
{
    // Currently, bot will never opt to move over land
}

void ModerateComputer::DestroyArmy(Player * player)
{
    // Currently, bot will never opt to move over land
}

void ModerateComputer::PlaceShadowArmy(Player *shadowPlayer)
{
	int countrySelection = rand() % (EmpireMap::instance()->GetCountries() - 1);
	Utils::View("Placing army at country " + std::to_string(countrySelection));
	EmpireMap::instance()->country(countrySelection)->AddArmy(shadowPlayer);

}