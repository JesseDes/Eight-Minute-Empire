#include "Observer.h"
#include "StatsObservable.h"

class StatsObserver : Observer {
public:
	StatsObserver(StatsObservable *observable);
	~StatsObserver();

private:
	void Update();
	void DisplayCountriesChart();
	void DisplayGoodsChart();
	StatsObservable *_subject;

};
