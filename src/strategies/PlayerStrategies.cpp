#include "PlayerStrategies.h"
#include "../map/Country.h"
#include "../map/MapLoader.h"
#include "../Testers.h"
#include "../core/GameLoop.h"
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
	std::ostringstream output;

    if (gameCard->isAnd)
    {
        output << "[0]";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
			output << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
				output << " AND ";
        }
		output << "\n[1] Do nothing ";

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
			output << "[" << selection++ << "]" << Action::typeToString(it->type) << " " << it->amount << " times ";

        selection = Utils::ValidInputRange(0, optionList.size() - 1,  "Invalid selection, please choose a value between 0 and " + optionList.size());

        (*player).DoAction(optionList.at(selection));
    }

	Utils::View(output.str());
}

void Human::MoveOverLand(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;
    Utils::View("\nYour countries & troop info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
			Utils::View("You have " + std::to_string(army) + " troops in country " + "[#" + std::to_string(j) +"]");
        }
    }
    do {
        Utils::View("\n Select a country to move a troop from: ",false);
        selectionFrom = Utils::ValidInputRange(0, numberOfCountries - 1, "please select a valid country");

        if (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0)
			Utils::View("\nYou don't have any troops there, choose another country: ",false);
    } while (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0);


    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLand(selectionFrom);

	Utils::View("These are the adjacent countries (by land only): ");
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
		Utils::View(" Country #" + std::to_string(*it));
    };

    do {
		Utils::View("\nSelect country to move a troop to: ",false);
        selectionTo = Utils::ValidInputRange(0,adjacent.size(),"You cannot travel there from the selected country, choose an adjacent country.");
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
			Utils::View("\nYou cannot travel there from the selected country, choose an adjacent country: ",false);
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

	Utils::View("\nThis is you updated country & troop info:\n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
		Utils::View("You have " + std::to_string(army) + " troops in country" + "[#" + std::to_string(j) + "]");
    }

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
	Utils::View("\nYour countries & troop info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
			Utils::View("You have " + std::to_string(army) + " troops in country " + "[#" + std::to_string(j) + "]");
		}
    }
    do {
		Utils::View("\nSelect a country to move a troop from: ");
        selectionFrom = Utils::ValidInputRange(0, numberOfCountries - 1 ,"Please select a valid country");

        if (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0)
			Utils::View("\nYou don't have any troops there, choose another country: ");
    } while (EmpireMap::instance()->country(selectionFrom)->GetArmy(player) == 0);

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLandAndWater(selectionFrom);

	Utils::View("These are the adjacent countries(by land and water): ");
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
		Utils::View(" Country #" + std::to_string(*it));
    };
    do {
		Utils::View("\nSelect country to move a troop to: " , false);
        selectionTo = Utils::ValidInputRange(0,adjacent.size(),"You cannot travel there from the selected country, choose an adjacent country");
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
			Utils::View("\nYou cannot travel there from the selected country, choose an adjacent country: " , false);
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

	Utils::View("\nThis is you updated country & troop info:\n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
		Utils::View("You have " + std::to_string(army) + " troops in country" + "[#" + std::to_string(j) + "]\n");
    }

    //UPDATE OWNER
    EmpireMap::instance()->country(selectionTo)->UpdateOwner();
    EmpireMap::instance()->country(selectionFrom)->UpdateOwner();
}

void Human::BuildCities(Player * player, int* cityPieces)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int selection;
	Utils::View("\nThese are the countries you have troops or cities in: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities");
        }
    }
    do {
		Utils::View("\nSelect a country to build a city in: ",false);
        selection = Utils::ValidInputRange(0, numberOfCountries - 1 , "Please Select a valid Country");

        if (EmpireMap::instance()->country(selection)->GetTotalUnits(player) == 0)
			Utils::View("\nYou need at least 1 unit to build here, choose another country: ",false);
    } while (EmpireMap::instance()->country(selection)->GetTotalUnits(player) == 0);

    if (cityPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddCity(player);
        (*cityPieces)--;
    }
    else
		Utils::View("You are out of city pieces");

	Utils::View("\nUpdated cities & troops info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities \n");
        }
    }

    //UPDATE OWNER
    EmpireMap::instance()->country(selection)->UpdateOwner();
}

void Human::PlaceNewArmies(Player * player, int* armyPieces)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int selection;
	Utils::View("\nThese are the countries you can place troops (cities and starting region): \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetCities(player) > 0 || j == EmpireMap::instance()->GetStartingCountry()->GetCountryName()) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities");
        }
    }
	Utils::View("Country [" + std::to_string(EmpireMap::instance()->GetStartingCountry()->GetCountryName()) + "] - is the starting region " , false);

    do {
		Utils::View("\nSelect a country to place a troop in: " , false);
		selection = Utils::ValidInputRange(0,numberOfCountries - 1 , "Please choose a valid country to place your troops");

        if (EmpireMap::instance()->country(selection)->GetCities(player) == 0 && selection != EmpireMap::instance()->GetStartingCountry()->GetCountryName())
			Utils::View("\nYou can only place a troop at the starting region or countries that you have cities in, choose again: " , false);

    } while (EmpireMap::instance()->country(selection)->GetCities(player) == 0 && selection != EmpireMap::instance()->GetStartingCountry()->GetCountryName());

    if (armyPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddArmy(player);
        (*armyPieces)--;
    }
    else
		Utils::View("\n You are out of army pieces");

	Utils::View("\nYour updated troops: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetCities(player) > 0 || j == EmpireMap::instance()->GetStartingCountry()->GetCountryName()) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities\n");
        }
    }

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

	Utils::View("\nPlayers List: \n");

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
		Utils::View("[" + std::to_string(index) + "]: " + (*it)->GetPlayerName());
    }

	Utils::View("\nWhich player would you like to target?: " , false);
    playerSelection = Utils::ValidInputRange(0, playerList.size() - 1 ,"Please select a valid player option to target");
	Utils::View("\nList of countries that target player has troops in: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - This player has " + std::to_string(country->GetArmy(playerList[playerSelection])) + " troops");
        }
    }

	Utils::View("\nWhich country would you like to target?: ", false);

	do {
		countrySelection = Utils::ValidInputRange(0, numberOfCountries - 1,"Please select a valid country to target");
		if ( EmpireMap::instance()->country(countrySelection)->GetArmy(playerList[playerSelection]) == 0)
			Utils::View("\n Target doesn't have any troops there, choose another country: " , false);
	} while (EmpireMap::instance()->country(countrySelection)->GetArmy(playerList[playerSelection]) == 0 );

    EmpireMap::instance()->country(countrySelection)->RemoveArmy(playerList[playerSelection]);


	Utils::View("\n\nUpdated troops of target player: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - This player has " + std::to_string(country->GetArmy(playerList[playerSelection])) + " troops\n");
        }
    }

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
		Utils::View("Country [" + std::to_string(j) + "] Shadow Player has " + std::to_string(country->GetArmy(shadowPlayer)) + " troops");
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
	Utils::View(" bids " + std::to_string(*_bid) +" coins\n");
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
				Utils::View("Found KILL at card [" + std::to_string(i) + "] at index [" + std::to_string(j) + "]");
                chosenCard = i;
            }
            else if (type == ActionType::build) {
				Utils::View("Found BUILD at card [" + std::to_string(i) + "] at index [" + std::to_string(j) + "]");
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
	std::ostringstream output;

    if (gameCard->isAnd)
    {
		output <<(*player).GetPlayerName()<< " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
			output << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
				output << " AND ";
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

		output << (*player).GetPlayerName() << " chose: ";
		output << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).DoAction(gameCard->actions[selection]);
    }
	Utils::View(output.str(), false);

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

    Utils::View("\nThese are the countries you have troops or cities in: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities");
            selection = j; 
        }
    }
	Utils::View("\nPlayer decided to build on country [" + std::to_string(selection) + "]\n");

	if(selection < 0)
		return;

    if (cityPieces > 0)
    {
        EmpireMap::instance()->country(selection)->AddCity(player);
        (*cityPieces)--;
    }
    else
		Utils::View("You are out of city pieces");

	Utils::View("\nUpdated cities & troops info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetTotalUnits(player) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - you have " + std::to_string(country->GetArmy(player)) + " troops, and " + std::to_string(country->GetCities(player)) + " cities");
        }
    }

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

	Utils::View("\nPlayers List: \n");

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
		Utils::View("[" + std::to_string(index) + "]: " + (*it)->GetPlayerName());
        if ((*it)->GetPlayerName() != player->GetPlayerName()) {
            playerSelection = index;
        }
    }

	if (countrySelection < 0)
		return;

	Utils::View("\nPlayer decided to kill [" + std::to_string(playerSelection) + "]\n");



	Utils::View("\nList of countries that target player has troops in: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - This player has " + std::to_string(country->GetArmy(playerList[playerSelection])) + " troops");
            countrySelection = j;
        }
    }
	if (countrySelection < 0)
		return;


	Utils::View("\nPlayer decided to kill on country [" + std::to_string(countrySelection) + "]\n");

    EmpireMap::instance()->country(countrySelection)->RemoveArmy(playerList[playerSelection]);

	Utils::View("\n\nUpdated troops of target player: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        if (country->GetArmy(playerList[playerSelection]) > 0) {
			Utils::View("Country [" + std::to_string(j) + "] - This player has " + std::to_string(country->GetArmy(playerList[playerSelection])) + " troops\n");
        }
    }

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
	Utils::View(" bids " + std::to_string(*_bid) + " coins\n");
}

int ModerateComputer::GetBid(Player* player) {
    return *_bid;
}

void ModerateComputer::ChooseCard(Player* player, Hand * gameHand)
{
    /* Implementing the following check:
        1) bot will look for a card that has either "move by land" or "move by sea" returning the least expensive card
        2) If bot cannot afford the card, it will opt for the free card
    */

    int chosenCard = 0;


    for (int i = 4; i >= 0; i--) {
        for (int j = 0; j < 2; j++) {
            ActionType type = gameHand->ViewCard(i)->actions[j].type;
            if (type == ActionType::moveSea) {
				Utils::View("found MOVE BY SEA at [" + std::to_string(i) + "] at index [" + std::to_string(j) + "]");
                chosenCard = i;
            }
            else if (type == ActionType::moveGround) {
				Utils::View("found MOVE BY GROUND at card [" + std::to_string(i) + "] at index [" + std::to_string(j) + "]");
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
	std::ostringstream output;

    if (gameCard->isAnd)
    {
        output << (*player).GetPlayerName() << " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
			output << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
				output << " AND ";
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

		output << (*player).GetPlayerName() << " chose: ";
		output << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).DoAction(gameCard->actions[selection]);
    }

	Utils::View(output.str());
}

void ModerateComputer::MoveOverLand(Player * player)
{
    int numberOfCountries = EmpireMap::instance()->GetCountries();
    Country* country;
    int army;

    int selectionFrom = -1;
    int selectionTo;

    Utils::View("\nYour countries & troop info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
			Utils::View("You have " + std::to_string(army) + " troops in country " + "[#" + std::to_string(j) + "]");
            selectionFrom = j; 
        }
    }
	if (selectionFrom < 0)
		return;

	Utils::View("\nPlayer is moving from: [" + std::to_string(selectionFrom) + "]\n");

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLand(selectionFrom);

	Utils::View("These are the adjacent countries (by land only): ");
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
		Utils::View(" Country #" + std::to_string(*it));
        selectionTo = *it;
    };

	Utils::View("\nPlayer moved to: [" + std::to_string(selectionFrom) + "]\n");

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

	Utils::View("\nThis is your updated country & troop info:\n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
		Utils::View("You have " + std::to_string(army) + " troops in country" + "[#" + std::to_string(j) + "]");
    }


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

	Utils::View("\nYour countries & troop info: \n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
        if (army > 0) {
			Utils::View("You have " + std::to_string(army) + " troops in country " + "[#" + std::to_string(j) + "]");
            selectionFrom = j;
        }
    }
	
	if (selectionFrom < 0)
		return;


	Utils::View("\nPlayer is moving from: [" + std::to_string(selectionFrom) + "]\n");

    std::vector<int> adjacent = EmpireMap::instance()->GetAdjacentByLandAndWater(selectionFrom);

	Utils::View("These are the adjacent countries (by land and water): ");
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
		Utils::View(" Country #" + std::to_string(*it));
        selectionTo = *it;
    };

	Utils::View("\nPlayer moved to: [" + std::to_string(selectionFrom) + "]\n");

    EmpireMap::instance()->country(selectionTo)->AddArmy(player);
    EmpireMap::instance()->country(selectionFrom)->RemoveArmy(player);

	Utils::View("\nThis is your updated country & troop info:\n");
    for (int j = 0; j < numberOfCountries; j++) {
        country = EmpireMap::instance()->country(j);
        army = country->GetArmy(player);
		Utils::View("You have " + std::to_string(army) + " troops in country" + "[#" + std::to_string(j) + "]");
    }

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