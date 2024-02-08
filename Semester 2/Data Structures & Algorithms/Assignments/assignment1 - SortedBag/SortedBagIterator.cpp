#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

//BC = WC = AC = Theta(1)
// Overall = Theta(1)

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	if (this->bag.length == 0) {
		this->currentIndex = -1; // bag is empty
	}
	else {
		this->currentIndex = 0; // bag has at least one element
	}
	this->currentFrequency = 0;
}


//BC = WC = AC = Theta(1)
// Overall = Theta(1)

TComp SortedBagIterator::getCurrent() {
	if (!(this->valid())) {
		throw exception("Invalid!");
	}
	return bag.elements[this->currentIndex].first;
}

//BC = WC = AC = Theta(1)
// Overall = Theta(1)

bool SortedBagIterator::valid() {
	if (this->currentIndex >= 0 && this->currentIndex < bag.length && bag.elements[this->currentIndex].second > 0 && this->currentFrequency <= bag.elements[this->currentIndex].second)
		return true;
	return false;
}


//BC = WC = AC = Theta(1)
// Overall = Theta(1)

void SortedBagIterator::next() {
	if (!this->valid()) {
		throw exception("Invalid!");
	}
	this->currentFrequency ++;
	if (this->currentFrequency == bag.elements[this->currentIndex].second)
	{
		this->currentIndex += 1;
		if (this->currentIndex == bag.length) {
			// Iterator is at end of bag
			this->currentIndex = bag.length;
		}
		this->currentFrequency = 0;
	}

}


//BC = WC = AC = Theta(1)
// Overall = Theta(1)

void SortedBagIterator::first() {
	this->currentIndex = 0;
}

