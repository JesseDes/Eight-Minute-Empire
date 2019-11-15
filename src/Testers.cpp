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
#include "PhaseObservable.h"
#include "PhaseObserver.h"
#include "StatsObservable.h"
#include "StatsObserver.h"

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

void Testers::PhaseTest()
{
	Player playerOne(5, "PlayerOne");
	Player playerTwo(5, "PlayerToo");
	PhaseObservable *subject = new PhaseObservable();
	PhaseObserver *watcher = new PhaseObserver(subject);

	Action act;
	act.type = ActionType::build;
	act.amount = 2;
	subject->StartTurn(playerOne.getPlayerName());
	subject->Bid(12, playerOne.getPlayerName());
	subject->PayPrice(5, 0 , playerOne.getPlayerName());
	subject->SetAction(&act , playerOne.getPlayerName());

	act.type = ActionType::kill;
	subject->StartTurn(playerTwo.getPlayerName());
	subject->Bid(12, playerTwo.getPlayerName());
	subject->PayPrice(15,2 , playerTwo.getPlayerName());
	subject->SetAction(&act, playerTwo.getPlayerName());
	

}

void Testers::StatsTest()
{
	Player *playerOne = new Player(5, "PlayerOne");

	StatsObservable *subject = new StatsObservable();
	StatsObserver *watcher = new StatsObserver(subject);


	Deck gameDeck;
	gameDeck.Shuffle();
	EmpireMap gameBoard = *MapLoader::FindMap();

	subject->SetPlayer(playerOne);					//Player acquiring a bunch of territores

	gameBoard.country(0)->addArmy(playerOne);
	gameBoard.country(0)->updateOwner();
	gameBoard.country(1)->addArmy(playerOne);
	gameBoard.country(1)->addArmy(playerOne);
	gameBoard.country(1)->addCity(playerOne);
	gameBoard.country(1)->updateOwner();
	gameBoard.country(2)->addArmy(playerOne);
	gameBoard.country(2)->addArmy(playerOne);
	gameBoard.country(2)->addArmy(playerOne);
	gameBoard.country(2)->addArmy(playerOne);
	gameBoard.country(2)->updateOwner();
	subject->UpdateCountries(playerOne->GetCountries());
	
	gameBoard.country(0)->removeArmy(playerOne); // Player losing some territories
	
	gameBoard.country(0)->updateOwner();
	gameBoard.country(1)->removeArmy(playerOne);
	gameBoard.country(2)->removeArmy(playerOne);
	gameBoard.country(1)->updateOwner();
	gameBoard.country(2)->updateOwner();

	subject->UpdateCountries(playerOne->GetCountries());
	
	int currentPoints = 0;
	for (int i = 0; i < 5; i++)
	{
		playerOne->readCard(gameDeck.Draw());
		if (currentPoints < playerOne->GetGoodPoints())
		{
			currentPoints = playerOne->GetGoodPoints();
			subject->UpdatePlayerGoods(playerOne->GetGoods());
		}
		else if (i == 4 && currentPoints == 0)
		{
			Deck::Card card;
			Action act;
			act.type = ActionType::null;
			act.amount = 0;
			card.actions[0] = act;
			card.numberOfActions = 1;
			card.good = GoodType::gem;
			
			playerOne->readCard(&card);
			subject->UpdatePlayerGoods(playerOne->GetGoods());
		}
	}
	
}
