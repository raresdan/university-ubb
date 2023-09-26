#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void registerObserver(Observer* observerToAdd);
	void unregisterObserver(Observer* observerToRemove);

	void notify();
};

