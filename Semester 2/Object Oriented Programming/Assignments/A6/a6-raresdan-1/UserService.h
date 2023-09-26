#pragma once
#include "Repository.h"
#include <vector>

class UserService
{
private:
	Repository tutorialsRepository;
	std::vector<Tutorial> watchlist;
public:
	UserService(Repository initialTutorialsRepository);
	bool addTutorialToWatchlist(Tutorial tutorialToAdd);
	bool removeTutorialFromWatchlist(std::string title, std::string presenter);
	std::vector<Tutorial> getTutorialsOfGivenPresenter(std::vector<Tutorial> allTutorials, std::string presenter);
	std::vector<Tutorial> getWatchlist();
};

