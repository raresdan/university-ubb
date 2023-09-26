#pragma once
#include "Action.h"

class ActionRemove :
    public Action
{
private:
    Song songRemoved;
    Repository repository;
public:
    ActionRemove(Repository r, Song s) : repository{ r }, songRemoved{ s } {};
    void executeUndo() override;
    void executeRedo() override;
};

