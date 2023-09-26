#include "Tests.h"
#include <assert.h>
#include <iostream>
#include <vector>


void Tests::testDomain()
{
    Duration duration;
    duration.minutes = 1;
    duration.seconds = 30;
    Tutorial validTutorial("Object Oriented Programming", "John Smith", duration, 100, "www.example.com");

    assert(validTutorial.getTitle() == "Object Oriented Programming");
    assert(validTutorial.getPresenter() == "John Smith");
    assert(validTutorial.getDuration().minutes == 1);
    assert(validTutorial.getDuration().seconds == 30);
    assert(validTutorial.getLikes() == 100);
    assert(validTutorial.getLink() == "www.example.com");

    validTutorial.setTitle("Data Structures and Algorithms");
    assert(validTutorial.getTitle() == "Data Structures and Algorithms");
    validTutorial.setPresenter("Jane Doe");
    assert(validTutorial.getPresenter() == "Jane Doe");
    Duration newDuration;
    newDuration.minutes = 2;
    newDuration.seconds = 15;
    validTutorial.setDuration(newDuration);
    assert(validTutorial.getDuration().minutes == 2 && validTutorial.getDuration().seconds == 15);
    validTutorial.setLikes(200);
    assert(validTutorial.getLikes() == 200);
    validTutorial.setLink("www.example2.com");
    assert(validTutorial.getLink() == "www.example2.com");

    Tutorial equalToValidTutotrial("Data Structures and Algorithms", "Jane Doe", newDuration, 200, "www.example2.com");
    assert(validTutorial == equalToValidTutotrial);

    Tutorial validTutorialToAssign("Intro to C++", "Sarah Johnson", duration, 50, "www.cpp.com");
    validTutorial = validTutorialToAssign;
    assert(validTutorial.getTitle() == "Intro to C++");
    assert(validTutorial.getPresenter() == "Sarah Johnson");
    assert(validTutorial.getDuration().minutes == 1);
    assert(validTutorial.getLikes() == 50);
    assert(validTutorial.getLink() == "www.cpp.com");
}

void Tests::testRepository()
{
    this->testGetAllTutorials();
    this->testAddTutorialToRepository();
    this->testRemoveTutorialFromRepository();
    this->testUpdateTutorialToRepository();
    this->testGetTutorialPositionInRepository();
}

void Tests::testGetAllTutorials()
{
    Tutorial validTutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository(initialTutorials);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
    assert(allTutorials[0] == Tutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com"));

}

void Tests::testAddTutorialToRepository()
{

    Tutorial validTutorial("Title 1", "Presenter 1", Duration{ 0, 30 }, 25, "https://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    Repository repository(initialTutorials);
    
    bool added = repository.addTutorial(validTutorial);
    assert(added == true);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
    assert(allTutorials[0] == validTutorial);
    
    added = repository.addTutorial(validTutorial);
    assert(added == false);
    allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
}

void Tests::testRemoveTutorialFromRepository()
{
    Tutorial validTutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository(initialTutorials);
    
    bool removed = repository.removeTutorial(0);
    assert(removed == true);
   std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 0);
    assert(allTutorials.empty() == true);
    
    repository.addTutorial(validTutorial);
    removed = repository.removeTutorial(77);
    assert(removed == false);
    allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
    assert(allTutorials[0] == validTutorial);
}

void Tests::testUpdateTutorialToRepository()
{
    Tutorial validTutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    Tutorial updatedValidTutorial("Title 2", "Presenter 2", Duration{ 0, 45 }, 15, "https://www.youtube.com");

    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository(initialTutorials);

    bool updated = repository.updateTutorial(0, updatedValidTutorial);
    assert(updated == true);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
    assert(allTutorials[0] == updatedValidTutorial);

    updated = repository.updateTutorial(77, updatedValidTutorial);
    assert(updated == false);
    allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 1);
    assert(allTutorials[0] == updatedValidTutorial);
}

void Tests::testGetTutorialPositionInRepository()
{
    Tutorial validTutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com");

    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository(initialTutorials);

    int position = repository.getTutorialPosition(validTutorial);
    assert(position == 0);

    Tutorial nonExistingTutorial("Non-Existing", "Presenter", Duration{ 0, 30 }, 25, "https://www.youtube.com");
    position = repository.getTutorialPosition(nonExistingTutorial);
    assert(position == -1);
}

void Tests::testAdministratorService()
{
    std::vector<Tutorial> initialTutorials;
    Repository repository{ initialTutorials };
    AdministratorService administratorService{ repository };

    assert(administratorService.addTutorial("Title 1", "Presenter 1", Duration{ 1, 0 }, 10, "https://www.youtube.com") == true);

    std::vector<Tutorial> allTutorials = administratorService.getAllTutorials();
    assert(allTutorials.size() == 1);

    assert(administratorService.removeTutorial("Title 1", "Presenter 1") == true);
    assert(administratorService.getAllTutorials().size() == 0);

    administratorService.addTutorial("Title 2", "Presenter 2", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    assert(administratorService.updateTutorial("Title 2", "Presenter 2", "New Title", "New Presenter", Duration{ 3, 0 }, 30, "https://www.youtube.com") == true);
    Tutorial updatedTutorial = administratorService.getAllTutorials()[0];
    assert(updatedTutorial.getTitle() == "New Title");
    assert(updatedTutorial.getPresenter() == "New Presenter");
    assert(updatedTutorial.getDuration().minutes == 3);
    assert(updatedTutorial.getDuration().seconds == 0);
    assert(updatedTutorial.getLikes() == 30);
    assert(updatedTutorial.getLink() == "https://www.youtube.com");

    assert(administratorService.increaseLikes("New Title", "New Presenter") == true);
    updatedTutorial = administratorService.getAllTutorials()[0];
    assert(updatedTutorial.getLikes() == 31);
}


void Tests::testUserService()
{
    Tutorial validTutorial{ "Title 1", "Presenter 1", Duration{ 10, 0 }, 20, "https://www.youtube.com" };
    std::vector<Tutorial> initialTutorials;
    Repository repository{ initialTutorials };
    UserService userService{repository};

    assert(userService.addTutorialToWatchlist(validTutorial) == true);
    assert(userService.addTutorialToWatchlist(validTutorial) == false);
    assert(userService.getWatchlist().size() == 1);

    assert(userService.removeTutorialFromWatchlist("Title 1", "Presenter 1") == true);
    assert(userService.removeTutorialFromWatchlist("Title 1", "Presenter 1") == false);
    assert(userService.getWatchlist().size() == 0);

    std::vector<Tutorial> allTutorials;
    allTutorials.push_back(validTutorial);
    std::vector<Tutorial> neededTutorials = userService.getTutorialsOfGivenPresenter(allTutorials, "");
    assert(neededTutorials.size() == allTutorials.size());
    neededTutorials = userService.getTutorialsOfGivenPresenter(allTutorials, "Presenter 1");
    assert(neededTutorials.size() == 1);
}

void Tests::testAll()
{
    this->testDomain();
    this->testRepository();
    this->testAdministratorService();
    this->testUserService();
}
