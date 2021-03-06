#pragma once
#include<list>
#include "Observer.h"
class Observer;

class Subject
{
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();

private:
	std::list<Observer*> *_observers;
};