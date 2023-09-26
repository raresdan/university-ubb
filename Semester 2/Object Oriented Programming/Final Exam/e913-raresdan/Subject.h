#pragma once
#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void registerObserver(Observer* observer)
	{
		this->observers.push_back(observer);
	}
	void notify()
	{
		for (auto o : observers)
		{
			o->update();
		}
	}
};

