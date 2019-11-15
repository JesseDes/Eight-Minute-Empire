#include "pch.h"
#include "Testers.h"
#include <iostream>
#include "Deck.h"
#include "Hand.h"
#include "BiddingFacility.h"
#include "Player.h"
#include <list>
#include "map.h"
#include "MapLoader.h"


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

	playerOne.createCoinPurse(2);
	playerTwo.createCoinPurse(2);

	playerOne.placeBid();
	playerTwo.placeBid();
	
	if (playerTwo.getBid() > playerOne.getBid())
		std::cout << "Player Two wins";
	else if (playerTwo.getBid() == playerOne.getBid())
	{
		if(playerTwo.getPlayerAge() < playerOne.getPlayerAge())
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

	playerOne.createCoinPurse(2);
	std::cout << "Starting coin amount: " <<  playerOne.getCoins() << "\n";
	playerOne.placeBid();
	playerOne.payCoin(playerOne.getBid());
	std::cout << "Post bid coin amount: " << playerOne.getCoins() << "\n";

	Deck::Card card;

	card.good = GoodType::metal;
	card.numberOfActions = 2;
	Action action1;
	Action action2;
	action1.amount = 2;
	action1.type = ActionType::build;
	action2.amount = 3;
	action2.type = ActionType::recruit;

	card.actions[0] = action1;
	card.actions[1] = action2;

	//playerOne.readCard(card);	
}

void Testers::MapTest()
{

	EmpireMap test = *MapLoader::FindMap();

	std::cout << std::endl;
	test.displayMatrix();
	std::cout << std::endl;
	test.displayAdjecent();
	std::cout << std::endl;
	test.displayAdjecentContinents();
	std::cout << std::endl << "number of continents: "<< test.getContinents();
	std::cout << std::endl << "number of countries: "<< test.getCountries();

	std::cout << std::endl << std::endl<<"displaying continent contents:"<< std::endl;
	test.displayContinents();

	std::cout << std::endl << std::endl << "changing owner of country 3 and returning it:" << std::endl;
	//test.country(3)->writeOwner("Siamak"); //Deprecated function

	std::cout << "owner name is now: " << test.country(3)->getOwner() << std::endl;

	std::cout << std::endl << std::endl << "ARE COUNTRIES CONNECTED?: " << test.IsCountriesConnected()<< std::endl;
	std::cout << std::endl << std::endl << "ARE CONTINENTS CONNECTED?: " << test.IsContinentsConnected() << std::endl;
	std::cout << std::endl << std::endl << "ARE COUNTRIES UNIQUE?: " << test.isNotDuplicated() << std::endl;

    std::cout << std::endl << std::endl << "Starting Country is: " << test.getStartingCountry() << std::endl;
}


void Testers::StrategyTest() 
{
    EmpireMap* gameBoard = MapLoader::FindMap();

    std::vector<Player*> playerList;


    std::cout << "creating Human player-> name: 'Human', age: 9\n";
    std::cout << "creating COMPUTER (greedy) player -> name: 'Greed', age: 8\n";
    std::cout << "creating COMPUTER (moderate) player -> name: 'Moderate', age: 7\n";

    Human human;
    GreedyComputer gBot;
    ModerateComputer mBot;

    Player* playerHuman = new Player(9, "Human");
    playerHuman->setPlayerStrategy(&human);

    Player* playerBotGreed = new Player(8, "Greed");
    playerBotGreed->setPlayerStrategy(&gBot);

    Player* playerBotModerate = new Player(7, "Moderate");
    playerBotModerate->setPlayerStrategy(&mBot);

    playerList.push_back(playerHuman);
    playerList.push_back(playerBotGreed);
    playerList.push_back(playerBotModerate);

    // adding 3 troops to the starting country
    for (int j = 0; j < 3; j++)
    {
        gameBoard->getStartingCountry()->addArmy(playerHuman);
        gameBoard->getStartingCountry()->addArmy(playerBotGreed);
        gameBoard->getStartingCountry()->addArmy(playerBotModerate);
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
        (*it)->createCoinPurse(playerList.size());
        std::cout << (*it)->getPlayerName() << " ";
        (*it)->placeBid();

        //currentPlayer is set to the player with the highest Bid and the youngest age (if matching bids) 
        if (it != playerList.begin() && ((*currentPlayer)->getBid() < (*it)->getBid() || ((*currentPlayer)->getBid() == (*it)->getBid() && (*currentPlayer)->getPlayerAge() > (*it)->getPlayerAge())))
            currentPlayer = it;
    }
    (*currentPlayer)->payCoin((*currentPlayer)->getBid());
    std::cout << "HIGHEST BIDDER WAS :" << (*currentPlayer)->getPlayerName() << "\n";
}