#pragma once
#include "Repository.h"
#include "FileWatchlist.h"
#include <vector>

class UserService
{
private:
	Repository tutorialsRepository;
	FileWatchlist* watchlist;
public:
	UserService(Repository initialTutorialsRepository, FileWatchlist* initialWatchlist = nullptr);
	bool addTutorialToWatchlist(Tutorial tutorialToAdd);
	bool removeTutorialFromWatchlist(std::string title, std::string presenter);
	std::vector<Tutorial> getTutorialsOfGivenPresenter(std::vector<Tutorial> allTutorials, std::string presenter);
	FileWatchlist* getWatchlist();
	void setWatchlist(std::string watchlistType);
	void saveWatchlist();
	void openWatchlist();
};

