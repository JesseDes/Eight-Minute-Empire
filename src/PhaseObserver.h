#pragma once
#include "Observer.h"
#include "PhaseObservable.h"

class PhaseObserver : public Observer
{
public:
	PhaseObserver(PhaseObservable *observable);
	~PhaseObserver();

private:
	void Update();
	void DisplayTurn();
	void DisplayCost();
	void DisplayAction();
	PhaseObservable *_subject;
	const int HEADER_SIZE = 75;
};