#include "repository.h"
#ifndef UNDOREDOREPOSITORY_H
#define UNDOREDOREPOSITORY_H

typedef struct {
    Repository* undo;
    Repository* redo;
    int undoSize;
    int redoSize;
    int undoCapacity;
    int redoCapacity;
}UndoRedoRepository;

UndoRedoRepository createUndoRedoRepository(int initialCapacity);
void destroyUndoRedoRepository(UndoRedoRepository* undoRedoRepository);
void addUndoElement(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository);
void addRedoElement(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository);
void popLastUndo(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository);
void popLastRedo(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository);
void resizeArrayUndo(UndoRedoRepository* undoRedoRepository);
void resizeArrayRedo(UndoRedoRepository* undoRedoRepository);

#endif UNDOREDOREPOSITORY_H