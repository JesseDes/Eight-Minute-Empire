#include "pch.h"
#include "Testers.h"


void Testers::DeckTest()
{
	Deck testDeck;
	Hand gameHand;

	for (int i = 0; i <= gameHand.SIZE_OF_HAND; i++)
		gameHand.AddCard(testDeck.Draw());

	gameHand.ShowHand();
}

void Testers::BiddingTest()
{
	Player playerOne(5, "Player one");
	Player playerTwo(5, "player Two");

	playerOne.CreateCoinPurse(2);
	playerTwo.CreateCoinPurse(2);

	playerOne.PlaceBid();
	playerTwo.PlaceBid();
	
	if (playerTwo.GetBid() > playerOne.GetBid())
		std::cout << "Player Two wins";
	else if (playerTwo.GetBid() == playerOne.GetBid())
	{
		if(playerTwo.GetPlayerAge() < playerOne.GetPlayerAge())
			std::cout << "Player Two wins";
		else
			std::cout << "Player One wins";
	}
	else
		std::cout << "Player One wins";
}

void Testers::PlayerTest()
{
	Player playerOne(5, "player One");

	playerOne.CreateCoinPurse(2);
	std::cout << "Starting coin amount: " <<  playerOne.GetCoins() << "\n";
	playerOne.PlaceBid();
	playerOne.PayCoin(playerOne.GetBid());
	std::cout << "Post bid coin amount: " << playerOne.GetCoins() << "\n";

    Card* card = CardFactory::Create("wood");

	card->good = GoodType::metal;
    card->numberOfActions = 2;
	Action action1;
	Action action2;
	action1.amount = 2;
	action1.type = ActionType::build;
	action2.amount = 3;
	action2.type = ActionType::recruit;

    card->actions[0] = action1;
    card->actions[1] = action2;

	//playerOne.readCard(card);	
}


void Testers::PhaseTest()
{
	Human human;
	Player playerOne(5, "PlayerOne");
	Player playerTwo(5, "PlayerToo");
	playerOne.GivePieces(10, 10);
	playerTwo.GivePieces(10, 10);
	playerOne.CreateCoinPurse(2);
	playerTwo.CreateCoinPurse(2);
	playerOne.SetPlayerStrategy(&human);
	playerTwo.SetPlayerStrategy(&human);

	PhaseObservable *subject = new PhaseObservable();
	PhaseObserver *watcher = new PhaseObserver(subject);

	Action act;
	act.type = ActionType::build;
	act.amount = 2;
	subject->StartTurn(playerOne.GetPlayerName());
	playerOne.PlaceBid();
	subject->Bid(playerOne.GetBid(), playerOne.GetPlayerName());
	subject->PayPrice(5, 0 , playerOne.GetPlayerName());
	subject->SetAction(&act , playerOne.GetPlayerName());

	act.type = ActionType::kill;
	subject->StartTurn(playerTwo.GetPlayerName());
	playerTwo.PlaceBid();
	subject->Bid(playerTwo.GetBid(), playerTwo.GetPlayerName());
	subject->PayPrice(15,2 , playerTwo.GetPlayerName());
	subject->SetAction(&act, playerTwo.GetPlayerName());
	

}

void Testers::StatsTest()
{
	Human human;

	Player *playerOne = new Player(5, "PlayerOne");
	playerOne->SetPlayerStrategy(&human);
	StatsObservable *subject = new StatsObservable();
	StatsObserver *watcher = new StatsObserver(subject);


	Deck gameDeck;
	gameDeck.Shuffle();
	MapLoader::FindMap();
	EmpireMap* gameBoard = EmpireMap::instance();

	subject->SetPlayer(playerOne);					//Player acquiring a bunch of territores

	(*gameBoard).country(0)->AddArmy(playerOne);
    (*gameBoard).country(0)->UpdateOwner();
    (*gameBoard).country(1)->AddArmy(playerOne);
    (*gameBoard).country(1)->AddArmy(playerOne);
    (*gameBoard).country(1)->AddCity(playerOne);
    (*gameBoard).country(1)->UpdateOwner();
    (*gameBoard).country(2)->AddArmy(playerOne);
    (*gameBoard).country(2)->AddArmy(playerOne);
    (*gameBoard).country(2)->AddArmy(playerOne);
    (*gameBoard).country(2)->AddArmy(playerOne);
    (*gameBoard).country(2)->UpdateOwner();
	subject->UpdateCountries(playerOne->GetCountries());
	
    (*gameBoard).country(0)->RemoveArmy(playerOne); // Player losing some territories
	
    (*gameBoard).country(0)->UpdateOwner();
    (*gameBoard).country(1)->RemoveArmy(playerOne);
    (*gameBoard).country(2)->RemoveArmy(playerOne);
    (*gameBoard).country(1)->UpdateOwner();
    (*gameBoard).country(2)->UpdateOwner();

	subject->UpdateCountries(playerOne->GetCountries());
	
	int currentPoints = 0;
	for (int i = 0; i < 5; i++)
	{
		playerOne->ReadCard(gameDeck.Draw());
		if (currentPoints < playerOne->GetGoodPoints())
		{
			currentPoints = playerOne->GetGoodPoints();
			subject->UpdatePlayerGoods(playerOne->GetGoods());
		}
		else if (i == 4 && currentPoints == 0)
		{
			Card* card = CardFactory::Create("wood");
			Action act;
			act.type = ActionType::null;
			act.amount = 0;
			card->actions[0] = act;
			card->numberOfActions = 1;
			card->good = GoodType::gem;
			
			playerOne->ReadCard(card);
			subject->UpdatePlayerGoods(playerOne->GetGoods());
		}
	}
	
}

std::vector<Player*> Testers::playerList;
void Testers::StrategyTest() 
{
	MapLoader::FindMap();
    EmpireMap* gameBoard = EmpireMap::instance();

    std::cout << "creating Human player-> name: 'Human', age: 9\n";
    std::cout << "creating COMPUTER (greedy) player -> name: 'Greed', age: 8\n";
    std::cout << "creating COMPUTER (moderate) player -> name: 'Moderate', age: 7\n";

    Human human;
    GreedyComputer gBot;
    ModerateComputer mBot;

    Player* playerHuman = new Player(9, "Human");
    playerHuman->SetPlayerStrategy(&human);
    playerHuman->GivePieces(10,10); 

    Player* playerBotGreed = new Player(8, "Greed");
    playerBotGreed->SetPlayerStrategy(&gBot);
    playerBotGreed->GivePieces(10, 10);

    Player* playerBotModerate = new Player(7, "Moderate");
    playerBotModerate->SetPlayerStrategy(&mBot);
    playerBotModerate->GivePieces(10, 10);

    playerList.push_back(playerHuman);
    playerList.push_back(playerBotGreed);
    playerList.push_back(playerBotModerate);

    // adding 3 troops to the starting country
    for (int j = 0; j < 3; j++)
    {
        gameBoard->GetStartingCountry()->AddArmy(playerHuman);
        gameBoard->GetStartingCountry()->AddArmy(playerBotGreed);
        gameBoard->GetStartingCountry()->AddArmy(playerBotModerate);
    }

    //create deck , shuffle, and add cards to hand
    Deck* gameDeck = new Deck();
    gameDeck->Shuffle();

    Hand* gameHand = new Hand();

    for (int i = 0; i <= gameHand->SIZE_OF_HAND; i++)
        gameHand->AddCard(gameDeck->Draw());

    //determine first player
    std::vector<Player*>::iterator currentPlayer = playerList.begin();
    for (std::vector<Player*>::iterator it = playerList.begin(); it != playerList.end(); it++)
    {
        (*it)->CreateCoinPurse(playerList.size());
        (*it)->PlaceBid();

        //currentPlayer is set to the player with the highest Bid and the youngest age (if matching bids) 
        if (it != playerList.begin() && ((*currentPlayer)->GetBid() < (*it)->GetBid() || ((*currentPlayer)->GetBid() == (*it)->GetBid() && (*currentPlayer)->GetPlayerAge() > (*it)->GetPlayerAge())))
            currentPlayer = it;
    }
    (*currentPlayer)->PayCoin((*currentPlayer)->GetBid());
    std::cout << "HIGHEST BIDDER WAS :" << (*currentPlayer)->GetPlayerName() << "\n";

    //Looping gameplay
    while (true)
    {
        std::cout << "It is " << (*currentPlayer)->GetPlayerName() << "'s turn \n";

        int strategySelection;
        std::cout << "Current player's strategy type is :" << (*currentPlayer)->GetPlayerStrategy()->PrintStrategyType() << "\n\n" <<
            "Would you like to set a new player strategy?\n\n" <<
            "[0] No\n" <<
            "[1] Human\n" <<
            "[2] Greedy (computer focused on building and killing)\n" << 
            "[3] Moderate (computer focused on conquering)\n";

        std::cin >> strategySelection;

        switch (strategySelection) 
        {
            case 0: break;// do nothing
            case 1: (*currentPlayer)->SetPlayerStrategy(&human); break;
            case 2: (*currentPlayer)->SetPlayerStrategy(&gBot); break;
            case 3: (*currentPlayer)->SetPlayerStrategy(&mBot); break;
        }

        //DISPLAY CARDS
        gameHand->ShowHand();

        std::cout << (*currentPlayer)->GetPlayerName() << ", which card would you like? \n";

        //CHOOSE CARD
        (*currentPlayer)->ChooseCard(gameHand);

        //ADD CARD
        gameHand->AddCard(gameDeck->Draw());

        //if player is last in the vector, go back to beginning else, increment iterator
        if (std::distance(currentPlayer, playerList.end()) == 1)
        {
            currentPlayer = playerList.begin();
        }
        else
        {
            currentPlayer++;
        }
    }
}
std::vector<Player*> Testers::getPlayerList()
{
    return playerList;
}

void Testers::SingletonMapTest()
{
    std::cout << "select map 1\n";
	MapLoader::FindMap();
    EmpireMap* map1 = EmpireMap::instance();

    std::cout << "\n\nselect map 2\n";
	MapLoader::FindMap();
    EmpireMap* map2 = EmpireMap::instance();

    std::cout << "\n\npointer of first map instance: " << map1 <<"\n";
    std::cout << "pointer of second map instance: " << map2 << "\n";
}

void Testers::FactoryTest()
{
    while (true) {

        std::cout << "Select one the the following card type: \n\n" <<
            "[0] Wood \n" <<
            "[1] Stone\n" <<
            "[2] Food \n" <<
            "[3] Gem \n"
            "[4] Metal\n" <<
            "[5] Wild \n";
		int cardSelection = Utils::ValidInputRange(0,5 ,"Please select valid card type");

        Card *card;
        switch (cardSelection) {
        case 0: card = CardFactory::Create("wood"); break;
        case 1: card = CardFactory::Create("stone"); break;
        case 2: card = CardFactory::Create("food"); break;
        case 3: card = CardFactory::Create("gem"); break;
        case 4: card = CardFactory::Create("metal"); break;
        case 5: card = CardFactory::Create("wild"); break;
        default: card = CardFactory::Create("wood"); break;
        }

        card->Draw();

        std::cout << "Good Type:  " << Good::GoodToString(card->good);
        std::cout << "\n# of action for this type of card:  " << card->numberOfActions;
        std::cout << "\nthis card has an 'AND' (0 = false, 1 = true):  " << card->isAnd;
        for (int i = 0; i < card->numberOfActions; i++) {
            std::cout << "\n\n#" << i << " action for this type of card:  " << Action::typeToString(card->actions[i].type);
            std::cout << "\n#" << i << " number of moves for this action:  " << card->actions[i].amount;
        }
        std::cout << "\n\n";
        system("pause");
    }
}