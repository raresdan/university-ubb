#include "Observer.h"

void Subject::addObserver(Observer* o)
{
	this->observers.push_back(o);
}

void Subject::removeObserver(Observer* o)
{
	this->observers.erase(std::find(this->observers.begin(),
		this->observers.end(), o));
}

void Subject::notify()
{
	for (Observer* o : observers)
		o->update();
}
