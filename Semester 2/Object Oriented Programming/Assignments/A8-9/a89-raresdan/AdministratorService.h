#pragma once
#include "Repository.h"
#include <vector>

class AdministratorService
{
private:
	Repository tutorialsRepository;
public:
	AdministratorService(Repository initialTutorialsRepository);
	bool addTutorial(std::string title, std::string presenter, Duration duration, int likes, std::string link);
	bool removeTutorial(std::string title, std::string presenter);
	void updateTutorial(std::string title, std::string presenter, std::string newTitle, std::string newPresenter, Duration newDuration, int newLikes, std::string newLink);
	void increaseLikes(std::string title, std::string presenter);
	std::vector<Tutorial> getAllTutorials();
	void initializeAllTutorials();
};

