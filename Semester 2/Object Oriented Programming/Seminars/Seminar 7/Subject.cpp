#include "Subject.h"

void Subject::registerObserver(Observer* observerToAdd)
{
	observers.push_back(observerToAdd);
}

void Subject::unregisterObserver(Observer* observerToRemove)
{
}

void Subject::notify()
{
	for (auto& o : observers)
	{
		o->update();
	}
}
