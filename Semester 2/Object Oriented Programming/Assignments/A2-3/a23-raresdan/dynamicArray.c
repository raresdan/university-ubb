#include "dynamicArray.h"
#include <stdlib.h>
#include <stdio.h>
#pragma once

DynamicArray* createDynamicArray(int initialCapacityOfTheDynamicArray)
{
    DynamicArray* dynamicArray = (DynamicArray*)malloc(sizeof(DynamicArray));
    if (dynamicArray == NULL)
        return NULL;
    dynamicArray->size = 0;
    dynamicArray->capacity = initialCapacityOfTheDynamicArray;
    dynamicArray->elements = (Country*)malloc(initialCapacityOfTheDynamicArray * sizeof(TElem));
    return dynamicArray;
}

void destroyDynamicArray(DynamicArray* dynamicArrayToBeDestroyed)
{
    if (dynamicArrayToBeDestroyed == NULL)
        return;
    free(dynamicArrayToBeDestroyed->elements);
}

void addElement(DynamicArray* dynamicArray, TElem elementToBeAdded)
{
    if (dynamicArray->size >= dynamicArray->capacity) {
        dynamicArray->capacity *= 2;
        TElem* newElements = realloc(dynamicArray->elements, dynamicArray->capacity * sizeof(TElem));
        if (newElements == NULL) {
            exit(1);
        }
        dynamicArray->elements = newElements;
    }
    dynamicArray->elements[dynamicArray->size] = elementToBeAdded;
    dynamicArray->size++;
}

void deleteElement(DynamicArray* dynamicArray, int indexOfTheElementToBeDeleted)
{
    for (int i = indexOfTheElementToBeDeleted; i < dynamicArray->size - 1; i++) 
    {
        dynamicArray->elements[i] = dynamicArray->elements[i + 1];
    }
    dynamicArray->size--;
}

void updateElement(DynamicArray* dynamicArray, int indexOfTheElementToBeUpdated, TElem updatedElement)
{
    dynamicArray->elements[indexOfTheElementToBeUpdated] = updatedElement;
}

int getDynamicArraySize(DynamicArray* dynamicArray)
{
	return dynamicArray->size;
}

int getDynamicArrayCapacity(DynamicArray* dynamicArray)
{
	return dynamicArray->capacity;
}
