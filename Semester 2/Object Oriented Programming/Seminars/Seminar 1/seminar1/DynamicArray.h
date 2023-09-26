#pragma once

typedef int TElem;

typedef struct
{
	TElem* elems;
	int size, capacity;
}DynamicArray;

DynamicArray* createArray(int capcacity);
void destroyArray(DynamicArray* arr);
int getCapacity(DynamicArray* arr);
int getSize(DynamicArray* arr);
void addElem(DynamicArray* arr, TElem elem);


void testDynamicArray();
