#pragma once
#include "Song.h"

typedef Song TElement;

class DynamicVector
{
private:
	TElement* elems;
	int size;
	int capacity;

public:
	// default constructor for a DynamicVector
	DynamicVector(int capacity = 10);

	// copy constructor for a DynamicVector
	DynamicVector(const DynamicVector& v);
	~DynamicVector();

	// assignment operator for a DynamicVector
	DynamicVector& operator=(const DynamicVector& v);

	// Adds an element to the current DynamicVector.
	void add(const TElement& e);

	int getSize() const;

	// returns the element on a given position
	// he position must be a valid one
	TElement get(int position);

private:
	// Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
	void resize(double factor = 2);
};

