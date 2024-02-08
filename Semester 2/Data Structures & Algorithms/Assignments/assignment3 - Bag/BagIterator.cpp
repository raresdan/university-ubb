#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentNode = bag.head;
	this->currentFrequency = 0;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
void BagIterator::first() {
	this->currentNode = bag.head;
	this->currentFrequency = 0;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
void BagIterator::next() {
    if (!this->valid())
        throw std::exception("Invalid iterator.");

    this->currentFrequency++;
    if (this->currentFrequency < bag.elems[this->currentNode].second) {
        return;
    }
    this->currentNode = bag.next[this->currentNode];
    this->currentFrequency = 0;
	
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
bool BagIterator::valid() const {
	return this->currentNode != -1 && this->currentNode < bag.capacity;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
TElem BagIterator::getCurrent() const
{
	if (!this->valid())
		throw std::exception("Invalid iterator.");

	return bag.elems[this->currentNode].first;
}
