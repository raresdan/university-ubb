#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
    this->capacity = 10;
    this->elems = new Pair[capacity];
    this->next = new int[capacity];
    for (int i = 0; i < capacity - 1; i++) {
        this->next[i] = i + 1;
    }
    this->next[capacity - 1] = -1;
    this->head = -1;
    this->firstFree = 0;
    this->length = 0;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = O(n)
void Bag::add(TElem elem) 
{
    int prev = -1;
    int curr = this->head;
    
    // Searching if the element already exists
    while (curr != -1 && this->elems[curr].first != elem) {
        prev = curr;
        curr = this->next[curr];
    }
    // Element found
    if (curr != -1) 
    { 
        this->elems[curr].second++;
        this->length++;
    }
    // Element not in the bag
    else 
    {
        // Resize if at the end of the bag
        if (this->firstFree == -1) 
        {
            int newCapacity = this->capacity * 2;
            Pair* newElems = new Pair[newCapacity];
            int* newNext = new int[newCapacity];
            for (int i = 0; i < this->capacity; i++) 
            {
                newElems[i] = this->elems[i];
                newNext[i] = this->next[i];
            }
            for (int i = this->capacity; i < newCapacity - 1; i++)
                newNext[i] = i + 1;
            newNext[newCapacity - 1] = -1;
            delete[] this->elems;
            delete[] this->next;
            this->elems = newElems;
            this->next = newNext;
            this->firstFree = this->capacity;
            this->capacity = newCapacity;
        }

        // Add the new element if it doesn't exist
        int newPos = this->firstFree;
        if (newPos < this->capacity) 
        {
            this->firstFree = this->next[this->firstFree];
            this->elems[newPos].first = elem;
            this->elems[newPos].second = 1;
            this->next[newPos] = head;
            this->head = newPos;
            this->length++;
        }
    }
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
bool Bag::remove(TElem elem) 
{
    int prev = -1;
    int current = this->head;
    // Searching for the element
    while (current != -1 && this->elems[current].first != elem) 
    {
        prev = current;
        current = this->next[current];
    }
    // Element found
    if (current != -1)
    {
        this->elems[current].second--;
        // Remove if the frequency is 0
        if (this->elems[current].second == 0)
        {
            // If the head is the only element remove it
            if (prev == -1)
                this->head = this->next[current];
            else
                this->next[prev] = this->next[current];
            this->next[current] = this->firstFree;
            this->firstFree = current;
        }
        this->length--;
        return true;
    }
    // element not found
    else
        return false;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
bool Bag::search(TElem elem) const {
    int current = this->head;
    while (current != -1) {
        if (this->elems[current].first == elem) {
            return true;
        }
        current = this->next[current];
    }
    return false;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
int Bag::nrOccurrences(TElem elem) const {
    int current = this->head;
    int count = 0;
    while (current != -1) {
        if (this->elems[current].first == elem) {
            count += this->elems[current].second;
        }
        current = this->next[current];
    }
    return count;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
int Bag::size() const {
    return this->length;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
bool Bag::isEmpty() const {
    if (this->length == 0)
        return true;
    return false;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
TElem Bag::leastFrequent() const
{
    if (this->isEmpty())
        return NULL_TELEM;
    int position = -1;
    int leastFreq = INT_MAX;
    int current = this->head;
    while (current != -1)
    {
        if (this->elems[current].second == 1)
            return this->elems[current].first;
        if (this->elems[current].second <= leastFreq)
        {
            leastFreq = this->elems[current].second;
            position = current;
        }
        current = this->next[current];
    }
    return this->elems[position].first;
}

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
    delete[] this->elems;
    delete[] this->next;
}

