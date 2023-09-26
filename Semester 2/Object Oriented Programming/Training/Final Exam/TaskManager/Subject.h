#pragma once
#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> observers;
public:
	void registerObserver(Observer* observerToRegister) { this->observers.push_back(observerToRegister); }
	void notify()
	{
		for (auto observer : this->observers)
			observer->update();
	}
};

