#pragma once
#include <stack>
#include "Repository.h"

class Action
{
public:
	virtual void executeUndo() = 0;
	virtual void executeRedo() = 0;

};

