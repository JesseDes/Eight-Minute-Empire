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
		gameHand.addCard(testDeck.Draw());

	gameHand.showHand();
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

	card.good = Good::metal;
	card.numberOfActions = 2;
	Action action1;
	Action action2;
	action1.amount = 2;
	action1.type = ActionType::build;
	action2.amount = 3;
	action2.type = ActionType::recruit;

	card.actions[0] = action1;
	card.actions[1] = action2;

	playerOne.readCard(card);	
}

void Testers::MapTest()
{

	MapLoader mapLoader;

	EmpireMap test = *MapLoader::readMapData("EmpireData2.txt");

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
	test.country(3)->writeOwner("Siamak");

	std::cout << "owner name is now: " << test.country(3)->getOwner() << std::endl;

	std::cout << std::endl << std::endl << "ARE COUNTRIES CONNECTED?: " << test.IsCountriesConnected()<< std::endl;
	std::cout << std::endl << std::endl << "ARE CONTINENTS CONNECTED?: " << test.IsContinentsConnected() << std::endl;
	std::cout << std::endl << std::endl << "ARE COUNTRIES UNIQUE?: " << test.isNotDuplicated() << std::endl;
}


