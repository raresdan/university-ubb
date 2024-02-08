#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
	//TODO - Implementation
	this->length = 0;
	this->capacity = 1;
	this->relation = r;
	this->elements = new Pair[this->capacity];
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)

void SortedBag::add(TComp e) {
	//resizing
	if (this->length == this->capacity)
	{
		int new_capacity = this->capacity *= 2;
		Pair* new_elements = new Pair[this->capacity];
		if (new_elements == nullptr)
			return;
		for (int i = 0; i < this->length; i++) 
			new_elements[i] = this->elements[i];
		delete[] this->elements;
		this->elements = new_elements;
		this->capacity = new_capacity;
	}

	//length = 0; first element added
	if (this->length == 0) 
	{
		this->elements[0].first = e;
		this->elements[0].second = 1;
		this->length++;
		return;
	}

	//length > 0; element already exists
	bool found = false;
	for (int i = 0; i < this->length - 1; i++) {
		if (elements[i].first == e) {
			this->elements[i].second ++;
			found = true;
			break;
		}
	}

	//length > 0; new element
	if (found == true)
		return;
	else
	{	
		int i = this->length - 1;
		while (i >= 0 && this->relation(e,this->elements[i].first))
		{
			this->elements[i + 1] = this->elements[i];
			i--;
		}
		this->elements[i + 1].first = e;
		this->elements[i + 1].second = 1;
		this->length++;
	}
}



// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)

bool SortedBag::remove(TComp e) {
	// length = 0
	//if (this->length == 0) {
	//	return false;
	//}

	//length > 0; element already exists
	for (int i = 0; i < this->length; i++) {
		if (elements[i].first == e && elements[i].second > 0) {
			this->elements[i].second--;
			if (this->elements[i].second == 0)
			{
				for (int j = i; j < this->length; j++) {
					this->elements[j] = this->elements[j + 1];
				}
			}
			return true;
		}
	}
	return false;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)

bool SortedBag::search(TComp elem) const {
	for (int i = 0; i < this->length; i++) 
		if (elements[i].first == elem && elements[i].second > 0)
			return true;
	return false;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)

int SortedBag::nrOccurrences(TComp elem) const {
	int count = 0;
	for (int i = 0; i < this->length; i++) {
		if (this->elements[i].first == elem) {
			count += this->elements[i].second;
		}
	}
	return count;
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)

int SortedBag::size() const {
	int s = 0;
	for (int i = 0; i < this->length; i++) {
		s += this->elements[i].second;
	}
	return s;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)

bool SortedBag::isEmpty() const {
	if (this->size() == 0)
		return true;
	return false;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)

SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)

SortedBag::~SortedBag() {
	delete[] this->elements;
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)

TElem SortedBag::mostFrequent() const
{	
	int currentMax;
	int maxFreq = 0;
	TComp maxFreqElem = NULL_TCOMP;
	if (this->isEmpty())
		return NULL_TCOMP;
	for (int i = 0; i < this->length; i++)
	{
		currentMax = this->nrOccurrences(this->elements[i].first);
		if (currentMax > maxFreq)
		{
			maxFreq = currentMax;
			maxFreqElem = this->elements[i].first;
		}
	}
	return maxFreqElem;
}
