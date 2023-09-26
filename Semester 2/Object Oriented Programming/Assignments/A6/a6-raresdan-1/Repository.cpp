#include "Repository.h"
#include <algorithm>

Repository::Repository(std::vector<Tutorial> initialTutorials) :
    allTutorials{initialTutorials}
{
}

std::vector<Tutorial> Repository::getAllTutorials()
{
    return this->allTutorials;
}

bool Repository::addTutorial(Tutorial tutorialToAdd)
{
    auto iterator = std::find(this->allTutorials.begin(), this->allTutorials.end(), tutorialToAdd);
    if (iterator != this->allTutorials.end())
        return false;
    this->allTutorials.push_back(tutorialToAdd);
    return true;
}

bool Repository::removeTutorial(int indexOfTutorialToRemove)
{
    if (indexOfTutorialToRemove < 0 || indexOfTutorialToRemove >= this->allTutorials.size())
        return false;
    this->allTutorials.erase(this->allTutorials.begin() + indexOfTutorialToRemove);
    return true;
}

bool Repository::updateTutorial(int indexOfTutorialToUpdate, Tutorial updatedTutorial)
{
    if (indexOfTutorialToUpdate < 0 || indexOfTutorialToUpdate >= this->allTutorials.size())
        return false;
    this->allTutorials[indexOfTutorialToUpdate] = updatedTutorial;
    return true;

}

int Repository::getTutorialPosition(Tutorial tutorialToGetPosition)
{
    auto iterator = std::find(this->allTutorials.begin(), this->allTutorials.end(), tutorialToGetPosition);
    if (iterator == this->allTutorials.end())
        return -1;
    return std::distance(this->allTutorials.begin(), iterator);
}
