#pragma once
#include "Tutorial.h"
#include <vector>

class Repository
{
private:
	std::vector<Tutorial> allTutorials;
	std::string filename;
public:
	Repository(std::string filename, std::vector<Tutorial> initialTutorials = {});
	std::vector<Tutorial> getAllTutorials();
	void addTutorial(Tutorial tutorialToAdd);
	void removeTutorial(int indexOfTutorialToRemove);
	void updateTutorial(int indexOfTutorialToUpdate, Tutorial updatedTutorial);
	int getTutorialPosition(Tutorial tutorialToGetPosition);
private:
	void readFromFile();
	void writeToFile();
};

