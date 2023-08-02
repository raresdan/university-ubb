#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::IndexedList() {
	//TODO - Implementation
}

int IndexedList::size() const {
    //TODO - Implementation
	return 0;
}


bool IndexedList::isEmpty() const {
    //TODO - Implementation
	return false;
}

TElem IndexedList::getElement(int pos) const {
    //TODO - Implementation
	return NULL_TELEM;
}

TElem IndexedList::setElement(int pos, TElem e) {
    //TODO - Implementation
	return NULL_TELEM;
}

void IndexedList::addToEnd(TElem e) {
    //TODO - Implementation
}

void IndexedList::addToPosition(int pos, TElem e) {
    //TODO - Implementation
}

TElem IndexedList::remove(int pos) {
    //TODO - Implementation
	return NULL_TELEM;
}

int IndexedList::search(TElem e) const{
    //TODO - Implementation
	return 0;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
	//TODO - Implementation
}