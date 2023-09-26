#pragma once
#include "Repository.h"
class FakeRepository :
    public Repository
{
public:
    bool boolValue;
    FakeRepository() : boolValue{ true } {};
    bool addTutorial(Tutorial tutorialToAdd) override;
    bool removeTutorial(int indexOfTutorialToRemove) override;
};

