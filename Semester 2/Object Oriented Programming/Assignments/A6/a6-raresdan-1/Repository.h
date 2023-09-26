#pragma once
#include "Tutorial.h"
#include <vector>

class Repository
{
private:
	std::vector<Tutorial> allTutorials;
public:
	Repository(std::vector<Tutorial> initialTutorials = {});
	std::vector<Tutorial> getAllTutorials();
	bool addTutorial(Tutorial tutorialToAdd);
	bool removeTutorial(int indexOfTutorialToRemove);
	bool updateTutorial(int indexOfTutorialToUpdate, Tutorial updatedTutorial);
	int getTutorialPosition(Tutorial tutorialToGetPosition);
};

