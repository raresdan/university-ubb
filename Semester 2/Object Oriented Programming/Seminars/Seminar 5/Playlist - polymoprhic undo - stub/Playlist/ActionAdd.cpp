#include "ActionAdd.h"

void ActionAdd::executeUndo()
{
	this->repository.addSong(this->songAdded);
}

void ActionAdd::executeRedo()
{
	this->repository.removeSong(this->songAdded);
}
