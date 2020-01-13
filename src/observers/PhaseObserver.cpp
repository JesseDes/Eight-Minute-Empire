#include "PhaseObserver.h"
#include <iostream>
#include "../utils/Utils.h"

PhaseObserver::PhaseObserver(PhaseObservable *observable): Observer()
{
	_subject = observable;
	_subject->Attach(this);
}

PhaseObserver::~PhaseObserver()
{
	_subject->Detach(this);
	_subject = NULL;
}

void PhaseObserver::Update()
{
	if (_subject->GetState() == PhaseState::START)
		DisplayTurn();
	else if (_subject->GetState() == PhaseState::ACTION)
		DisplayAction();
	else
		DisplayCost();
}

void PhaseObserver::DisplayTurn()
{
	std::string output;
	int i = 0;
	for (; i < HEADER_SIZE; i++)
		output += "=";
	
	output +=  "\n";
	int half_minus_name_length = HEADER_SIZE / 2 - _subject->GetName()->length();

	output += "||";
	for (i = 0; i < half_minus_name_length ; i++)
		output += " ";
	output += *_subject->GetName();

	for (; i < HEADER_SIZE - _subject->GetName()->length() - 4; i++)
		output += " ";
	
	output += "||\n";

	for(i =0; i < HEADER_SIZE; i++)
		output += "=";

	output += "\n";

	Utils::View(output);
}

void PhaseObserver::DisplayCost()
{
	std::string output;
	if (_subject->GetState() == PhaseState::PAYMENT)
		output =  *_subject->GetName() + " : Paid " + std::to_string(_subject->GetCost()) + " coins. for card " + std::to_string(_subject->GetHandIndex()) + "\n";
	else
		output =  *_subject->GetName() + " : Bid " + std::to_string(_subject->GetCost()) + " coins.\n";

	Utils::View(output);
}

void PhaseObserver::DisplayAction()
{
	std::string output =  *_subject->GetName() + ": ";

	switch (_subject->GetAction()->type)
	{
	case ActionType::build: output += "has built " + std::to_string(_subject->GetAction()->amount) + " cities"; break;
	case ActionType::kill: output += "Attacked another destroyed " + std::to_string(_subject->GetAction()->amount) +" armies "; break;
	case ActionType::moveGround: output += "has moved by ground " + std::to_string(_subject->GetAction()->amount) + " times "; break;
	case ActionType::moveSea:  output += "has moved by seas " + std::to_string(_subject->GetAction()->amount) + " times "; break;
	case ActionType::recruit: output += "has Recruited " + std::to_string(_subject->GetAction()->amount) + " armies "; break;
	case ActionType::null: output += " did nothing"; break;

	default: output += " did nothing"; break;
	}
	output += "\n";

	Utils::View(output);
}