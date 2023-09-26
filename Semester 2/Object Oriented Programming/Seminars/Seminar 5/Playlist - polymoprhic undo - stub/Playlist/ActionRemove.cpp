#include "ActionRemove.h"

void ActionRemove::executeUndo()
{
	this->repository.removeSong(this->songRemoved);
}

void ActionRemove::executeRedo()
{
	this->repository.addSong(this->songRemoved);
}
