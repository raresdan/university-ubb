#pragma once

template <typename T>
class List
{
public:
	virtual T& operator[](int pos) = 0;

	// Adds an element to the current list.
	virtual void add(const T& e) = 0;

	virtual int getSize() const = 0;

	virtual ~List() {}
};