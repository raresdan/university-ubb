#include "UserService.h"
#include <algorithm>
#include <iterator>

UserService::UserService(Repository initialTutorialsRepository) :
	tutorialsRepository{initialTutorialsRepository}
{
}

bool UserService::addTutorialToWatchlist(Tutorial tutorialToAdd)
{
	auto iterator = std::find(this->watchlist.begin(), this->watchlist.end(), tutorialToAdd);
	if (iterator != this->watchlist.end())
		return false;
	this->watchlist.push_back(tutorialToAdd);
	return true;
}


bool UserService::removeTutorialFromWatchlist(std::string title, std::string presenter)
{
	Duration nullDuration;
	nullDuration.minutes = 0;
	nullDuration.seconds = 0;
	Tutorial tutorialToRemove{ title, presenter, nullDuration, 0, "" };
	auto iterator = std::find(this->watchlist.begin(), this->watchlist.end(), tutorialToRemove);
	if (iterator == this->watchlist.end())
		return false;
	this->watchlist.erase(iterator);
	return true;
}

std::vector<Tutorial> UserService::getTutorialsOfGivenPresenter(std::vector<Tutorial> allTutorials, std::string presenter)
{
	if (presenter.compare("") == 0)
		return allTutorials;
	std::vector<Tutorial> neededTutorials;
	std::copy_if(allTutorials.begin(), allTutorials.end(), std::back_inserter(neededTutorials),
		[presenter](const Tutorial& tutorial) { return tutorial.getPresenter() == presenter; });
	return neededTutorials;
}

std::vector<Tutorial> UserService::getWatchlist()
{
	return this->watchlist;
}
