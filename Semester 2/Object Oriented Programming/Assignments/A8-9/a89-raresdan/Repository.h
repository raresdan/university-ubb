#pragma once
#include "Tutorial.h"
#include <vector>

class Repository
{
private:
	std::vector<Tutorial> allTutorials;
	std::string filename;
public:
	Repository(std::string filename = {"Tutorials.txt"}, std::vector<Tutorial> initialTutorials = {});
	std::vector<Tutorial> getAllTutorials();
	virtual bool addTutorial(Tutorial tutorialToAdd);
	virtual bool removeTutorial(int indexOfTutorialToRemove);
	void updateTutorial(int indexOfTutorialToUpdate, Tutorial updatedTutorial);
	int getTutorialPosition(Tutorial tutorialToGetPosition);
private:
	void readFromFile();
	void writeToFile();
};

