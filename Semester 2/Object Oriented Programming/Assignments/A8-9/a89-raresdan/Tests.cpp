#include "Tests.h"
#include "HtmlWatchlist.h"
#include "FakeRepository.h"
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

void Tests::testAll()
{
    testDomain();
    testAdd();
    testRemove();
}

void Tests::testAdd()
{
    FakeRepository* fakeRepository = new FakeRepository{};
    AdministratorService testService{ *fakeRepository };
    Tutorial validTutorial = Tutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");
    fakeRepository->boolValue = true;
    assert(testService.addTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com") == true);
    fakeRepository->boolValue = false;
    try {
        testService.addTutorial("Title", "Presenter", Duration{ 1, 0 }, 10, "https://www.youtube.com");
        assert(false);
    }
    catch (std::exception )
    {
        assert(true);
    }
}

void Tests::testRemove()
{
    FakeRepository* fakeRepository = new FakeRepository{};
    AdministratorService testService{ *fakeRepository };
    fakeRepository->boolValue = true;
    assert(testService.removeTutorial("Title", "Presenter") == true);
    fakeRepository->boolValue = false;
    try {
        testService.removeTutorial("Title", "Presenter");
        assert(false);
    }
    catch (const std::exception e)
    {
        assert(true);
    }

}

