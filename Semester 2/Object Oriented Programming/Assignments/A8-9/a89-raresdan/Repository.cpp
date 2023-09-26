#include "Repository.h"
#include "Utils.h"
#include "Exception.h"
#include <algorithm>
#include <fstream>

Repository::Repository(std::string filename, std::vector<Tutorial> initialTutorials) :
    allTutorials{initialTutorials},
    filename{filename}
{
    this->readFromFile();
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
    this->writeToFile();
    return true;
}

bool Repository::removeTutorial(int indexOfTutorialToRemove)
{
    if (indexOfTutorialToRemove < 0 || indexOfTutorialToRemove >= this->allTutorials.size())
        return false;
    this->allTutorials.erase(this->allTutorials.begin() + indexOfTutorialToRemove);
    this->writeToFile();
    return true;
}

void Repository::updateTutorial(int indexOfTutorialToUpdate, Tutorial updatedTutorial)
{
    if (indexOfTutorialToUpdate < 0 || indexOfTutorialToUpdate >= this->allTutorials.size())
        throw std::exception("Tutorial doesn't exists!");
    this->allTutorials[indexOfTutorialToUpdate] = updatedTutorial;
    this->writeToFile();
}

int Repository::getTutorialPosition(Tutorial tutorialToGetPosition)
{
    auto iterator = std::find(this->allTutorials.begin(), this->allTutorials.end(), tutorialToGetPosition);
    if (iterator == this->allTutorials.end())
        return -1;
    return std::distance(this->allTutorials.begin(), iterator);
}

void Repository::readFromFile()
{
    std::ifstream inputFile(this->filename);
    if (!inputFile.is_open())
        throw FileException("The file could not be opened!");
    Tutorial tutorialToRead;
    while (inputFile >> tutorialToRead)
        this->allTutorials.push_back(tutorialToRead);
    inputFile.close();
}

void Repository::writeToFile()
{
    std::ofstream outputFile(this->filename);
    if (!outputFile.is_open())
        throw FileException("The file could not be opened!");
    for (auto currentTutorial : this->allTutorials)
    {
        outputFile << currentTutorial;
    }
    outputFile.close();
}
