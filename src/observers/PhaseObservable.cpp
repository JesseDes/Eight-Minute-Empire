#include "PhaseObservable.h"

PhaseObservable::PhaseObservable() : Subject()
{
	_currentAction = new Action();
	_currentAction->amount = 1;
	_currentAction->type = ActionType::null;
}

PhaseObservable::~PhaseObservable()
{
	_currentAction = NULL; //Don't delete just remove reference;

	delete _cost;
	_cost = NULL;

	delete _name;
	_name = NULL;

	delete _handIndex;
	_handIndex = NULL;
}

Action* PhaseObservable::GetAction()
{
	return _currentAction;
}

std::string* PhaseObservable::GetName()
{
	return _name;
}

PhaseState PhaseObservable::GetState()
{
	return _currentState;
}

int PhaseObservable::GetCost()
{
	return *_cost;
}


void PhaseObservable::SetAction(Action *playerAction, std::string name)
{
	_currentState = PhaseState::ACTION;
	_currentAction = playerAction;
	delete _name;
	_name = new std::string(name);
	Notify();
}

void PhaseObservable::PayPrice(int price, int handIndex ,std::string name)
{
	delete _cost;
	delete _name;
	delete _handIndex;
	_handIndex = new int(handIndex);
	_cost = new int(price);
	_name = new std::string(name);
	_currentState = PhaseState::PAYMENT;
	Notify();
}

void PhaseObservable::StartTurn(std::string name)
{
	delete _name;
	_name = new std::string(name);
	_currentState = PhaseState::START;
	Notify();
}

void PhaseObservable::Bid(int cost, std::string name)
{
	delete _cost;
	delete _name;
	_cost = new int(cost);
	_name = new std::string(name);
	_currentState = PhaseState::BID;
	Notify();
}

int PhaseObservable::GetHandIndex()
{
	return *_handIndex;
}