#include "DynamicArray.h"
#include <stdio.h>
#pragma once

DynamicArray* createArray(int capacity)
{
	DynamicArray* arr = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (arr == NULL)
		return NULL;
	arr->capacity = capacity;
	arr->size = 0;
	arr->elems = malloc(capacity * sizeof(TElem));

}

void destroyArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;
	free(arr->elems);
	free(arr);
}

void testDynamicArray()
{
}
