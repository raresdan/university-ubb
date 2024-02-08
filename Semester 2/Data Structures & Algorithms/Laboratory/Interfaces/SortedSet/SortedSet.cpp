#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
	//TODO - Implementation
}


bool SortedSet::add(TComp elem) {
	//TODO - Implementation
	return false;
}


bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	return false;
}


bool SortedSet::search(TComp elem) const {
	//TODO - Implementation
	return true;
}


int SortedSet::size() const {
	//TODO - Implementation
	return 0;
}



bool SortedSet::isEmpty() const {
	//TODO - Implementation
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation
}


