#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* da = malloc(sizeof(DynamicArray));
	// make sure that the space was allocated
	if (da == NULL)
		return NULL;

	da->capacity = capacity;
	da->length = 0;

	// allocate space for the elements
	da->elems = malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;

	return da;
}

void destroy(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	// free the space allocated for the planets
	free(arr->elems);
	arr->elems = NULL;

	// free the space allocated for the dynamic array
	free(arr);
	//arr = NULL; // !!!
}

// Resizes the array, allocating more space.
void resize(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	arr->capacity *= 2;
	TElement* aux = realloc(arr->elems, arr->capacity * sizeof(TElement));
	if (aux == NULL)
		return; // array cannot be resized (TODO - return error code and check when resizing)
	arr->elems = aux;
}

void add(DynamicArray* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	// resize the array, if necessary
	if (arr->length == arr->capacity)
		resize(arr);
	arr->elems[arr->length] = t;
	arr->length++;
}

int getLength(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->length;
}

int getCapacity(DynamicArray* arr)
{
	if (arr == NULL)
		return 0;
	return arr->capacity;
}

void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(getCapacity(da) == 2);
	assert(getLength(da) == 0);

	Planet p1 = createPlanet("Wolf 1061 c", "terrestrial", 13.8);
	add(da, p1);
	assert(getLength(da) == 1);

	Planet p2 = createPlanet("HAT-P-26b", "Neptune-like", 450);
	add(da, p2);
	assert(getLength(da) == 2);

	// capacity must double
	Planet p3 = createPlanet("Proxima Centauri b", "terrestrial", 4.2);
	add(da, p3);
	assert(getLength(da) == 3);
	assert(getCapacity(da) == 4);

	destroy(da);
}