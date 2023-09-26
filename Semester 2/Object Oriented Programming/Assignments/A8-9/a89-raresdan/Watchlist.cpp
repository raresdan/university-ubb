#include "Watchlist.h"

std::vector<Tutorial> Watchlist::getAllTutorials()
{
	return this->allTutorials;
}

bool Watchlist::addTutorial(Tutorial tutorialToAdd)
{
	auto iterator = std::find(this->allTutorials.begin(), this->allTutorials.end(), tutorialToAdd);
	if (iterator != this->allTutorials.end())
		return false;
	this->allTutorials.push_back(tutorialToAdd);
	return true;
}

bool Watchlist::removeTutorial(Tutorial tutorialToRemove)
{
	auto iterator = std::find(this->allTutorials.begin(), this->allTutorials.end(), tutorialToRemove);
	if (iterator == this->allTutorials.end())
		return false;
	this->allTutorials.erase(iterator);
	return true;
}
