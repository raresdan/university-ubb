#include "AdministratorService.h"

AdministratorService::AdministratorService(Repository initialTutorialsRepository) : tutorialsRepository{initialTutorialsRepository}
{
}

bool AdministratorService::addTutorial(std::string title, std::string presenter, Duration duration, int likes, std::string link)
{
    Tutorial tutorialToAdd{ title, presenter, duration, likes, link };
    bool added = this->tutorialsRepository.addTutorial(tutorialToAdd);
    if (added == false)
        throw std::exception("Tutorial already exists!");
    else
        return true;
}

bool AdministratorService::removeTutorial(std::string title, std::string presenter)
{
    Tutorial tutorialToRemove{ title, presenter, {0,0}, 0, ""};
    int indexOfTutorialToRemove = this->tutorialsRepository.getTutorialPosition(tutorialToRemove);
    bool removed = this->tutorialsRepository.removeTutorial(indexOfTutorialToRemove);
    if (removed == false)
        throw std::exception("Tutorial doesn't exists!");
    else
        return true;
}

void AdministratorService::updateTutorial(std::string title, std::string presenter, std::string newTitle, std::string newPresenter, Duration newDuration, int newLikes, std::string newLink)
{
    Tutorial tutorialToUpdate{ title, presenter, {0,0}, 0, ""};
    Tutorial updatedTutorial{ newTitle, newPresenter, newDuration, newLikes, newLink };
    int indexOfTutorialToUpdate = this->tutorialsRepository.getTutorialPosition(tutorialToUpdate);
    this->tutorialsRepository.updateTutorial(indexOfTutorialToUpdate, updatedTutorial);
}

void AdministratorService::increaseLikes(std::string title, std::string presenter)
{
    Tutorial tutorialToUpdate{ title, presenter, {0,0}, 0, ""};
    int indexOfTutorialToUpdate = this->tutorialsRepository.getTutorialPosition(tutorialToUpdate);
    Tutorial tutorialToIncreaseLikes = this->tutorialsRepository.getAllTutorials()[indexOfTutorialToUpdate];
    int likes = tutorialToIncreaseLikes.getLikes() + 1;
    tutorialToIncreaseLikes.setLikes(likes);
    this->tutorialsRepository.updateTutorial(indexOfTutorialToUpdate, tutorialToIncreaseLikes);
}

std::vector<Tutorial> AdministratorService::getAllTutorials()
{
    return this->tutorialsRepository.getAllTutorials();
}

void AdministratorService::initializeAllTutorials()
{
    this->addTutorial("Learn C++ in 24h", "FreeCodeCamp", { rand() % 60, rand() % 60 }, 100785, "https://www.youtube.com");
    this->addTutorial("C++ Data Structures", "CS Dojo", { rand() % 60, rand() % 60 }, 184946, "https://www.odysee.com");
    this->addTutorial("C++ - From Zero To Hero", "Academind", { rand() % 60, rand() % 60 }, 1054165, "https://www.vimeo.com");
    this->addTutorial("C & C++ for Beginners", "BroCode", { rand() % 60, rand() % 60 }, 546354, "https://www.youtube.com");
    this->addTutorial("Game Devlopement with C++", "FreeCodeCamp", { rand() % 60, rand() % 60 }, 456434, "https://www.youtube.com");
    this->addTutorial("How to learn C++?", "Programming with Mosh", { rand() % 60, rand() % 60 }, 645654, "https://www.youtube.com");
    this->addTutorial("C++ Developer Roadmap", "Fireship", { rand() % 60, rand() % 60 }, 54656, "https://www.vimeo.com");
    this->addTutorial("How to master C++", "CS Dojo", { rand() % 60, rand() % 60 }, 100596, "https://www.odysee.com");
    this->addTutorial("Full Course - OOP in C++", "FreeCodeCamp", { rand() % 60, rand() % 60 }, 563000, "https://www.youtube.com");
    this->addTutorial("Introduction in C++", "BroCode", { rand() % 60, rand() % 60 }, 1674500, "https://www.youtube.com");
}
