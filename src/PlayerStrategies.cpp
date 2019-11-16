#include "PlayerStrategies.h"
#include "Country.h"
#include "MapLoader.h"
#include "Testers.h"


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

void Human::readCard(Player * player, Deck::Card * gameCard)
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

        std::cin >> selection;
        selection = Utils::validInputRange(0, 1, selection, "Invalid selection, please choose a value between 0 and 1");

        if (selection == 0)
        {
            for (int i = 0; i < gameCard->numberOfActions; i++)
                (*player).doAction(gameCard->actions[i]);
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

        std::cin >> selection;
        selection = Utils::validInputRange(0, optionList.size() - 1, selection, "Invalid selection, please choose a value between 0 and " + optionList.size());

        (*player).doAction(optionList.at(selection));
    }
}

void Human::moveOverLand(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
        }
    }
    do {
        std::cout << "\nSelect a country to move a troop from: ";
        std::cin >> selectionFrom;

        if (MapLoader::GetMap()->country(selectionFrom)->getArmy(player) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    } while (MapLoader::GetMap()->country(selectionFrom)->getArmy(player) == 0);


    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLand(selectionFrom);

    std::cout << "These are the adjacent countries (by land only): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
    };

    do {
        std::cout << "\nSelect country to move a troop to: ";
        std::cin >> selectionTo;
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    MapLoader::GetMap()->country(selectionTo)->addArmy(player);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(player);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selectionTo)->updateOwner();
    MapLoader::GetMap()->country(selectionFrom)->updateOwner();
}

void Human::moveOverSea(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;
    int selectionFrom;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
        }
    }
    do {
        std::cout << "\nSelect a country to move a troop from: ";
        std::cin >> selectionFrom;

        if (MapLoader::GetMap()->country(selectionFrom)->getArmy(player) == 0)
            std::cout << "\nYou don't have any troops there, choose another country: ";
    } while (MapLoader::GetMap()->country(selectionFrom)->getArmy(player) == 0);

    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLandAndWater(selectionFrom);

    std::cout << "These are the adjacent countries(by land and water): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
    };
    do {
        std::cout << "\nSelect country to move a troop to: ";
        std::cin >> selectionTo;
        if (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end())
            std::cout << "\nYou cannot travel there from the selected country, choose an adjacent country: ";
    } while (std::find(adjacent.begin(), adjacent.end(), selectionTo) == adjacent.end());

    MapLoader::GetMap()->country(selectionTo)->addArmy(player);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(player);

    std::cout << "\nThis is you updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selectionTo)->updateOwner();
    MapLoader::GetMap()->country(selectionFrom)->updateOwner();
}

void Human::buildCities(Player * player, int* cityPieces)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int selection;

    std::cout << "\nThese are the countries you have troops or cities in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities \n";
        }
    }
    do {
        std::cout << "\nSelect a country to build a city in: ";
        std::cin >> selection;

        if (MapLoader::GetMap()->country(selection)->getTotalUnits(player) == 0)
            std::cout << "\nYou need at least 1 unit to build here, choose another country: ";
    } while (MapLoader::GetMap()->country(selection)->getTotalUnits(player) == 0);

    if (cityPieces > 0)
    {
        MapLoader::GetMap()->country(selection)->addCity(player);
        (*cityPieces)--;
    }
    else
        std::cout << "You are out of city pieces";

    std::cout << "\nUpdated cities & troops info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities \n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selection)->updateOwner();
}

void Human::placeNewArmies(Player * player, int* armyPieces)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int selection;

    std::cout << "\nThese are the countries you can place troops (cities and starting region): \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getCities(player) > 0 || j == MapLoader::GetMap()->getStartingCountry()->getCountryName()) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities\n";
        }
    }
    std::cout << "Country [" << MapLoader::GetMap()->getStartingCountry()->getCountryName() << "] - is the starting region ";

    do {
        std::cout << "\nSelect a country to place a troop in: ";
        std::cin >> selection;

        if (MapLoader::GetMap()->country(selection)->getCities(player) == 0 && selection != MapLoader::GetMap()->getStartingCountry()->getCountryName())
            std::cout << "\nYou can only place a troop at the starting region or countries that you have cities in, choose again: ";

    } while (MapLoader::GetMap()->country(selection)->getCities(player) == 0 && selection != MapLoader::GetMap()->getStartingCountry()->getCountryName());

    if (armyPieces > 0)
    {
        MapLoader::GetMap()->country(selection)->addArmy(player);
        (*armyPieces)--;
    }
    else
        std::cout << "You are out of army pieces";

    std::cout << "\nYour updated troops: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getCities(player) > 0 || j == MapLoader::GetMap()->getStartingCountry()->getCountryName()) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selection)->updateOwner();
}

void Human::destroyArmy(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int playerSelection;
    int countrySelection;

    std::vector<Player*> playerList = Testers::getPlayerList(); // TODO: in GameLoop we have to replace with this -> GameLoop::getPlayerList();

    std::cout << "\nPlayers List: \n\n";

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
        std::cout << "[" << index << "]: " << (*it)->getPlayerName() << std::endl;
    }

    std::cout << "\nWhich player would you like to target?: ";
    std::cin >> playerSelection;

    std::cout << "\nList of countries that target player has troops in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->getArmy(playerList[playerSelection]) << " troops\n";
        }
    }
    std::cout << "\nWhich country would you like to target?: ";
    std::cin >> countrySelection;

    MapLoader::GetMap()->country(countrySelection)->removeArmy(playerList[playerSelection]);


    std::cout << "\n\nUpdated troops of target player: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->getArmy(playerList[playerSelection]) << " troops\n\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(countrySelection)->updateOwner();
}


//GREEDY COMPUTER (focused on building cities and destroying opponents)

void GreedyComputer::placeBid(Player* player)
{
    bid = new int(0);
    std::cout << player->getPlayerName() <<" bids " << *bid <<" coins\n\n";
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
     
    if (!(player)->payCoin(gameHand->GetCardCost(chosenCard))) {
        chosenCard = 0;
    }

    //reads card and performs action
    (player)->readCard(gameHand->Exchange(chosenCard));
}

void GreedyComputer::readCard(Player * player, Deck::Card * gameCard)
{
    int selection = 0;

    if (gameCard->isAnd)
    {
        std::cout <<(*player).getPlayerName()<< " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
            std::cout << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
                std::cout << " AND ";
        }

        for (int i = 0; i < gameCard->numberOfActions; i++)
            (*player).doAction(gameCard->actions[i]);
        
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

        std::cout << (*player).getPlayerName() << " chose: ";
        std::cout << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).doAction(gameCard->actions[selection]);
    }
}

void GreedyComputer::moveOverLand(Player * player)
{
    // Currently, bot will never opt to move over land
}

void GreedyComputer::moveOverSea(Player * player)
{
    // Currently, bot will never opt to move over land
}

void GreedyComputer::buildCities(Player * player, int* cityPieces)
{
    //Bot's behavior will be add a city on a land it has an army on

    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int selection;

    std::cout << "\nThese are the countries you have troops or cities in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities \n";
            selection = j; 
        }
    }
    std::cout << "\nPlayer decided to build on country ["<< selection << "]\n\n";

    if (cityPieces > 0)
    {
        MapLoader::GetMap()->country(selection)->addCity(player);
        (*cityPieces)--;
    }
    else
        std::cout << "You are out of city pieces";

    std::cout << "\nUpdated cities & troops info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getTotalUnits(player) > 0) {
            std::cout << "Country [" << j << "] - you have " << country->getArmy(player) << " troops, and " << country->getCities(player) << " cities \n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selection)->updateOwner();
}

void GreedyComputer::placeNewArmies(Player * player, int* armyPieces)
{
    //currently, bot will never opt to place new armies
}

void GreedyComputer::destroyArmy(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int playerSelection;
    int countrySelection;

    std::vector<Player*> playerList = Testers::getPlayerList(); // TODO: in GameLoop we have to replace with this -> GameLoop::getPlayerList();

    std::cout << "\nPlayers List: \n\n";

    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        int index = std::distance(playerList.begin(), it);
        std::cout << "[" << index << "]: " << (*it)->getPlayerName() << std::endl;
        if ((*it)->getPlayerName() != player->getPlayerName()) {
            playerSelection = index;
        }
    }

    std::cout << "\nPlayer decided to kill [" << playerSelection << "]\n\n";



    std::cout << "\nList of countries that target player has troops in: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->getArmy(playerList[playerSelection]) << " troops\n";
            countrySelection = j;
        }
    }
    std::cout << "\nPlayer decided to kill on country [" << countrySelection << "]\n\n";

    MapLoader::GetMap()->country(countrySelection)->removeArmy(playerList[playerSelection]);

    std::cout << "\n\nUpdated troops of target player: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        if (country->getArmy(playerList[playerSelection]) > 0) {
            std::cout << "Country [" << j << "] - This player has " << country->getArmy(playerList[playerSelection]) << " troops\n\n";
        }
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(countrySelection)->updateOwner();
}


//MODERATE COMPUTER (focused conquering land)

void ModerateComputer::placeBid(Player* player)
{
    bid = new int(1);
    std::cout << player->getPlayerName() << " bids " << *bid << " coins\n\n";
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
                std::cout << "found MOVE BY SEA at [" << i << "] at index [" << j << "] \n";
                chosenCard = i;
            }
            else if (type == ActionType::moveGround) {
                std::cout << "found MOVE BY GROUND at card [" << i << "] at index [" << j << "] \n";
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

void ModerateComputer::readCard(Player * player, Deck::Card * gameCard)
{
    int selection = 0;

    if (gameCard->isAnd)
    {
        std::cout << (*player).getPlayerName() << " chose: ";
        for (int i = 0; i < gameCard->numberOfActions; i++)
        {
            std::cout << Action::typeToString(gameCard->actions[i].type) << " " << gameCard->actions[i].amount << " times";

            if (i < gameCard->numberOfActions - 1)
                std::cout << " AND ";
        }

        for (int i = 0; i < gameCard->numberOfActions; i++)
            (*player).doAction(gameCard->actions[i]);

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

        std::cout << (*player).getPlayerName() << " chose: ";
        std::cout << Action::typeToString(gameCard->actions[selection].type) << " " << gameCard->actions[selection].amount << " times \n";

        (*player).doAction(gameCard->actions[selection]);
    }
}

void ModerateComputer::moveOverLand(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
            selectionFrom = j; 
        }
    }

    std::cout << "\nPlayer is moving from: [" << selectionFrom << "]\n\n";

    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLand(selectionFrom);

    std::cout << "These are the adjacent countries (by land only): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
        selectionTo = *it;
    };

    std::cout << "\nPlayer moved to: [" << selectionFrom << "]\n\n";

    MapLoader::GetMap()->country(selectionTo)->addArmy(player);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(player);

    std::cout << "\nThis is your updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selectionTo)->updateOwner();
    MapLoader::GetMap()->country(selectionFrom)->updateOwner();
}

void ModerateComputer::moveOverSea(Player * player)
{
    int numberOfCountries = MapLoader::GetMap()->getCountries();
    Country* country;
    int army;

    int selectionFrom;
    int selectionTo;

    std::cout << "\nYour countries & troop info: \n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        if (army > 0) {
            std::cout << "You have " << army << " troops in country " << "[#" << j << "]\n";
            selectionFrom = j;
        }
    }

    std::cout << "\nPlayer is moving from: [" << selectionFrom << "]\n\n";

    std::vector<int> adjacent = MapLoader::GetMap()->getAdjacentByLandAndWater(selectionFrom);

    std::cout << "These are the adjacent countries (by land and water): " << std::endl;
    for (std::vector<int>::iterator it = adjacent.begin(); it != adjacent.end(); ++it) {
        std::cout << " Country #" << *it << std::endl;
        selectionTo = *it;
    };

    std::cout << "\nPlayer moved to: [" << selectionFrom << "]\n\n";

    MapLoader::GetMap()->country(selectionTo)->addArmy(player);
    MapLoader::GetMap()->country(selectionFrom)->removeArmy(player);

    std::cout << "\nThis is your updated country & troop info:\n\n";
    for (int j = 0; j < numberOfCountries; j++) {
        country = MapLoader::GetMap()->country(j);
        army = country->getArmy(player);
        std::cout << "You have " << army << " troops in country" << "[#" << j << "]\n";
    }
    std::cout << std::endl;

    //UPDATE OWNER
    MapLoader::GetMap()->country(selectionTo)->updateOwner();
    MapLoader::GetMap()->country(selectionFrom)->updateOwner();
}

void ModerateComputer::buildCities(Player * player, int* cityPieces)
{
    // Currently, bot will never opt to move over land
}

void ModerateComputer::placeNewArmies(Player * player, int* armyPieces)
{
    // Currently, bot will never opt to move over land
}

void ModerateComputer::destroyArmy(Player * player)
{
    // Currently, bot will never opt to move over land
}