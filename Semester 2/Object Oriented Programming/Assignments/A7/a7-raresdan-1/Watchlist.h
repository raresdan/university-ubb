#pragma once
#include "Tutorial.h"
#include <vector>

class Watchlist
{
protected:
	std::vector<Tutorial> allTutorials;
public:
	Watchlist(std::vector<Tutorial> initialWatchlist = {}) {};
	std::vector<Tutorial> getAllTutorials();
	bool addTutorial(Tutorial tutorialToAdd);
	bool removeTutorial(Tutorial tutorialToRemove);
	virtual ~Watchlist() {};
};

