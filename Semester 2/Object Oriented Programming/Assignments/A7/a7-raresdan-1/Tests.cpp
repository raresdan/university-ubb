#include "Tests.h"
#include "HtmlWatchlist.h"
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
    validTutorial.setDuration({2,15});
    assert(validTutorial.getDuration().minutes == 2 && validTutorial.getDuration().seconds == 15);
    validTutorial.setLikes(200);
    assert(validTutorial.getLikes() == 200);
    validTutorial.setLink("www.example2.com");
    assert(validTutorial.getLink() == "www.example2.com");

    Tutorial equalToValidTutotrial("Data Structures and Algorithms", "Jane Doe", { 2,15 }, 200, "www.example2.com");
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
    std::vector<Tutorial> initialTutorials;
    Repository repository("Tutorials.txt", initialTutorials);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 10);
}

void Tests::testAddTutorialToRepository()
{

    Tutorial validTutorial("Title", "Presenter", Duration{ 0, 30 }, 25, "https://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    Repository repository("Tutorials.txt", initialTutorials);
    
    repository.addTutorial(validTutorial);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 11);
    assert(allTutorials[10] == validTutorial);
    repository.removeTutorial(repository.getTutorialPosition(validTutorial));
}

void Tests::testRemoveTutorialFromRepository()
{
    Tutorial validTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository("Tutorials.txt", initialTutorials);
 
    repository.removeTutorial(0);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 10);
    
    repository.addTutorial(validTutorial);
    repository.removeTutorial(77);
    allTutorials = repository.getAllTutorials();
    assert(allTutorials.size() == 11);
    assert(allTutorials[10] == validTutorial);
    repository.removeTutorial(repository.getTutorialPosition(validTutorial));
}

void Tests::testUpdateTutorialToRepository()
{
    Tutorial updatedValidTutorial("Title", "Presenter", Duration{ 0, 45 }, 15, "https://www.youtube.com");
    Tutorial revertChanges("Learn C++ in 24h", "FreeCodeCamp", Duration{ 10, 20 }, 100786, "https ://www.youtube.com");
    std::vector<Tutorial> initialTutorials;
    Repository repository("Tutorials.txt", initialTutorials);

    repository.updateTutorial(0, updatedValidTutorial);
    std::vector<Tutorial> allTutorials = repository.getAllTutorials();
    assert(allTutorials[0] == updatedValidTutorial);
    repository.updateTutorial(77, updatedValidTutorial);

    repository.updateTutorial(0, revertChanges);
}

void Tests::testGetTutorialPositionInRepository()
{
    Tutorial validTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");

    std::vector<Tutorial> initialTutorials;
    initialTutorials.push_back(validTutorial);
    Repository repository("Tutorials.txt", initialTutorials);

    int position = repository.getTutorialPosition(validTutorial);
    assert(position == 0);

    Tutorial nonExistingTutorial("Non-Existing", "Presenter", Duration{ 0, 30 }, 25, "https://www.youtube.com");
    position = repository.getTutorialPosition(nonExistingTutorial);
    assert(position == -1);
}

void Tests::testAdministratorService()
{
    std::vector<Tutorial> initialTutorials;
    Repository repository{ "Tutorials.txt", initialTutorials };
    AdministratorService administratorService{ repository };

    administratorService.addTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");

    std::vector<Tutorial> allTutorials = administratorService.getAllTutorials();
    assert(allTutorials.size() == 11);

    administratorService.removeTutorial("Title", "Presenter");
    assert(administratorService.getAllTutorials().size() == 10);

    administratorService.addTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    administratorService.updateTutorial("Title", "Presenter", "New Title", "New Presenter", Duration{ 3, 0 }, 30, "https://www.youtube.com");
    Tutorial updatedTutorial = administratorService.getAllTutorials()[10];
    assert(updatedTutorial.getTitle() == "New Title");
    assert(updatedTutorial.getPresenter() == "New Presenter");
    assert(updatedTutorial.getDuration().minutes == 3);
    assert(updatedTutorial.getDuration().seconds == 0);
    assert(updatedTutorial.getLikes() == 30);
    assert(updatedTutorial.getLink() == "https://www.youtube.com");

    administratorService.increaseLikes("New Title", "New Presenter");
    updatedTutorial = administratorService.getAllTutorials()[10];
    assert(updatedTutorial.getLikes() == 31);

    administratorService.removeTutorial("New Title", "New Presenter");
}


void Tests::testUserService()
{
    Tutorial validTutorial{ "Title", "Presenter", Duration{ 10, 0 }, 20, "https://www.youtube.com" };
    std::vector<Tutorial> initialTutorials;
    FileWatchlist* watchlist = nullptr;
    watchlist = new HtmlWatchlist{ "watchlist.html" };
    Repository repository{ "Tutorials.txt", initialTutorials };
    UserService userService{repository, watchlist};

    assert(userService.addTutorialToWatchlist(validTutorial) == true);
    assert(userService.addTutorialToWatchlist(validTutorial) == false);
    assert(userService.getWatchlist()->getAllTutorials().size() == 1);

    assert(userService.removeTutorialFromWatchlist("Title", "Presenter") == true);
    assert(userService.removeTutorialFromWatchlist("Title", "Presenter") == false);
    assert(userService.getWatchlist()->getAllTutorials().size() == 0);

    std::vector<Tutorial> allTutorials;
    allTutorials.push_back(validTutorial);
    std::vector<Tutorial> neededTutorials = userService.getTutorialsOfGivenPresenter(allTutorials, "");
    assert(neededTutorials.size() == allTutorials.size());
    neededTutorials = userService.getTutorialsOfGivenPresenter(allTutorials, "Presenter");
    assert(neededTutorials.size() == 1);
}

void Tests::testAll()
{
    this->testDomain();
    this->testRepository();
    this->testAdministratorService();
    this->testUserService();
}
