#include "undoRedo.h"
#include <stdlib.h>

UndoRedoRepository createUndoRedoRepository(int initialCapacity)
{
    UndoRedoRepository undoRedoRepository;
    undoRedoRepository.undo = (Repository*)malloc(initialCapacity * sizeof(Repository));
    undoRedoRepository.undoSize = 0;
    undoRedoRepository.undoCapacity = initialCapacity;
    undoRedoRepository.redo = (Repository*)malloc(initialCapacity * sizeof(Repository));
    undoRedoRepository.redoSize = 0;
    undoRedoRepository.redoCapacity = initialCapacity;
    return undoRedoRepository;
}

void destroyUndoRedoRepository(UndoRedoRepository* undoRedoRepository)
{
    int index;
    for (index = 0; index < undoRedoRepository->redoSize; index++) {
        destroyDynamicArray(&undoRedoRepository->redo[index].allCountries);
    }
    free(undoRedoRepository->redo);
    for (index = 0; index < undoRedoRepository->undoSize; index++) {
        destroyDynamicArray(&undoRedoRepository->undo[index].allCountries);
    }
    free(undoRedoRepository->undo);
}

void addUndoElement(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository)
{
    if (undoRedoRepository->undoSize == undoRedoRepository->undoCapacity) {
        resizeArrayUndo(undoRedoRepository);
    }
    undoRedoRepository->undo[undoRedoRepository->undoSize].allCountries.elements = (Country*)malloc(countriesRepository->allCountries.capacity * sizeof(Country));
    for (int index = 0; index < countriesRepository->allCountries.size; index++)
        undoRedoRepository->undo[undoRedoRepository->undoSize].allCountries.elements[index] = countriesRepository->allCountries.elements[index];
    undoRedoRepository->undo[undoRedoRepository->undoSize].allCountries.size = countriesRepository->allCountries.size;
    undoRedoRepository->undo[undoRedoRepository->undoSize].allCountries.capacity = countriesRepository->allCountries.capacity;
    undoRedoRepository->undoSize++;

}

void addRedoElement(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository)
{
    if (undoRedoRepository->redoSize == undoRedoRepository->redoCapacity)
        resizeArrayRedo(undoRedoRepository);
    //allocate space for the elements to be copied
    undoRedoRepository->redo[undoRedoRepository->redoSize].allCountries.elements = (Country*)malloc(countriesRepository->allCountries.capacity * sizeof(Country));
    //copy the elements
    for (int index = 0; index < countriesRepository->allCountries.size; index++)
        undoRedoRepository->redo[undoRedoRepository->redoSize].allCountries.elements[index] = countriesRepository->allCountries.elements[index];
    undoRedoRepository->redo[undoRedoRepository->redoSize].allCountries.size = countriesRepository->allCountries.size;
    undoRedoRepository->redo[undoRedoRepository->redoSize].allCountries.capacity = countriesRepository->allCountries.capacity;
    undoRedoRepository->redoSize++;
}

void popLastUndo(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository)
{
    free(countriesRepository->allCountries.elements); 
    //copy the elements
    countriesRepository->allCountries.elements = undoRedoRepository->undo[undoRedoRepository->undoSize - 1].allCountries.elements;
    countriesRepository->allCountries.size = undoRedoRepository->undo[undoRedoRepository->undoSize - 1].allCountries.size;
    countriesRepository->allCountries.capacity = undoRedoRepository->undo[undoRedoRepository->undoSize - 1].allCountries.capacity;
    //delete the las element of the undo array
    Repository* temporaryRepository;
    temporaryRepository = (Repository*)malloc(undoRedoRepository->undoCapacity * sizeof(Repository));
    for (int index = 0; index < undoRedoRepository->undoSize - 1; index++)
        temporaryRepository[index] = undoRedoRepository->undo[index];
    free(undoRedoRepository->undo);
    undoRedoRepository->undo = temporaryRepository;
    undoRedoRepository->undoSize--;
}

void popLastRedo(UndoRedoRepository* undoRedoRepository, Repository* countriesRepository)
{
    free(countriesRepository->allCountries.elements);
    //copy the elements
    countriesRepository->allCountries.elements = undoRedoRepository->redo[undoRedoRepository->redoSize - 1].allCountries.elements;
    countriesRepository->allCountries.size = undoRedoRepository->redo[undoRedoRepository->redoSize - 1].allCountries.size;
    countriesRepository->allCountries.capacity = undoRedoRepository->redo[undoRedoRepository->redoSize - 1].allCountries.capacity;
    //delete the las element of the redo array
    Repository* temporaryRepository;
    temporaryRepository = (Repository*)malloc(undoRedoRepository->redoCapacity * sizeof(Repository));
    for (int index = 0; index < undoRedoRepository->redoSize - 1; index++)
        temporaryRepository[index] = undoRedoRepository->redo[index];
    free(undoRedoRepository->redo);
    undoRedoRepository->redo = temporaryRepository;
    undoRedoRepository->redoSize--;
}

void resizeArrayUndo(UndoRedoRepository* undoRedoRepository)
{
    Repository* temporaryRepository;
    temporaryRepository = (Repository*)malloc(undoRedoRepository->undoCapacity * 2 * sizeof(Repository));
    for (int index = 0; index < undoRedoRepository->undoSize - 1; index++)
        temporaryRepository[index] = undoRedoRepository->undo[index];
    free(undoRedoRepository->undo);
    undoRedoRepository->undo = temporaryRepository;
    undoRedoRepository->undoCapacity *= 2;
}

void resizeArrayRedo(UndoRedoRepository* undoRedoRepository)
{
    Repository* temporaryRepository;
    temporaryRepository = (Repository*)malloc(undoRedoRepository->redoCapacity * 2 * sizeof(Repository));
    for (int index = 0; index < undoRedoRepository->redoSize - 1; index++)
        temporaryRepository[index] = undoRedoRepository->redo[index];
    free(undoRedoRepository->redo);
    undoRedoRepository->redo = temporaryRepository;
    undoRedoRepository->redoCapacity *= 2;
}
