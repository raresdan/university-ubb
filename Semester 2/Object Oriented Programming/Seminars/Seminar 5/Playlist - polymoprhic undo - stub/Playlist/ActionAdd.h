#pragma once
#include "Action.h"

class ActionAdd :
    public Action
{
private:
    Song songAdded;
    Repository repository;
public:
    ActionAdd(Repository r, Song s) : repository{ r }, songAdded{ s } {};
    void executeUndo() override;
    void executeRedo() override;

};

