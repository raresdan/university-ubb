#pragma once
#include "SortedIteratedList.h"

//DO NOT CHANGE THIS PART
class ListIterator{
	friend class SortedIteratedList;
private:
	TComp* elements;
	const SortedIteratedList& list;
	int current, currentIndex, length;
	ListIterator(const SortedIteratedList& list);

public:
	void first();
	void next();
	bool valid() const;
    TComp getCurrent() const;

	TComp* inorderTraversal(int node, TComp* array, int& index);
	TComp* sortArray();
};


