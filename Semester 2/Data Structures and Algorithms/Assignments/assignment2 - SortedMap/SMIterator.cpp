#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->currentNode = this->map.head;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
void SMIterator::first(){
	this->currentNode = this->map.head;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
void SMIterator::next(){
	if (!this->valid()) {
		throw exception("Invalid!");
	}
	this->currentNode = this->currentNode->next;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
bool SMIterator::valid() const{
	return this->currentNode != nullptr;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
TElem SMIterator::getCurrent() const{
	if (!(this->valid())) {
		throw exception("Invalid!");
	}
	return this->currentNode->pair;
}


