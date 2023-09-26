#include "UserService.h"
#include "CsvWatchlist.h"
#include "HtmlWatchlist.h"
#include <algorithm>
#include <iterator>

UserService::UserService(Repository initialTutorialsRepository, FileWatchlist* initialWatchlist) :
	tutorialsRepository{initialTutorialsRepository}, watchlist{initialWatchlist}
{
}

bool UserService::addTutorialToWatchlist(Tutorial tutorialToAdd)
{
	return this->watchlist->addTutorial(tutorialToAdd);
}

bool UserService::removeTutorialFromWatchlist(std::string title, std::string presenter)
{
	if (this->watchlist == nullptr)
		return false;
	Tutorial tutorialToRemove{ title, presenter, {0,0}, 0, "" };
	return this->watchlist->removeTutorial(tutorialToRemove);
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

FileWatchlist* UserService::getWatchlist()
{
	return this->watchlist;
}

void UserService::setWatchlist(std::string watchlistType)
{
	if (watchlistType == "CSV")
		this->watchlist = new CsvWatchlist{ "watchlist.csv" };
	else if (watchlistType == "HTML")
		this->watchlist = new HtmlWatchlist{ "watchlist.html" };
}

void UserService::saveWatchlist()
{
	this->watchlist->writeToFile();
}

void UserService::openWatchlist()
{
	this->watchlist->displayWatchlist();
}
