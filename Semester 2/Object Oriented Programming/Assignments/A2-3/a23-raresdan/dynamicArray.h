#pragma once
#include "country.h"

typedef Country TElem;

typedef struct
{
	TElem* elements;
	int size, capacity;
}DynamicArray;

DynamicArray* createDynamicArray(int initialCapacityOfTheDynamicArray);
void destroyDynamicArray(DynamicArray* dynamicArrayToBeDestroyed);
void addElement(DynamicArray* dynamicArray, TElem elementToBeAdded);
void deleteElement(DynamicArray* dynamicArray, int indexOfTheElementToBeDeleted);
void updateElement(DynamicArray* dynamicArray, int indexOfTheElementToBeUpdated, TElem updatedElement);
int getDynamicArraySize(DynamicArray* dynamicArray);
int getDynamicArrayCapacity(DynamicArray* dynamicArray);
