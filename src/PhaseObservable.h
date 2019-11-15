#pragma once
#include "Subject.h"
#include "Action.h"

enum class PhaseState
{
	START,
	PAYMENT,
	ACTION,
	BID
};

class PhaseObservable : public Subject
{
public:
	PhaseObservable();
	~PhaseObservable();
	void SetAction(Action *playerAction,std::string name);
	void PayPrice(int price, int index, std::string name);
	void StartTurn(std::string name);
	void Bid(int bid, std::string name);
	Action* GetAction();
	std::string* GetName();
	PhaseState GetState();
	int GetCost();
	int GetHandIndex();

private:
	Action *_currentAction;
	std::string *_name;
	PhaseState _currentState;
	int *_cost;
	int *_handIndex;
};