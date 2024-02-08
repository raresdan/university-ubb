#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	Node* currentNode;
	SMIterator(const SortedMap& mapionar);
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

