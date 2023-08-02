#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
	this->relation = r;
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
TValue SortedMap::add(TKey k, TValue v) {
    
    // Start from the head
    Node* current = this->head;
    Node* previous = nullptr;
    while (current != nullptr && !this->relation(k, current->pair.first)) {
        previous = current;
        current = current->next;
    }
    // Key exists, replace value
    if (current != nullptr && current->pair.first == k) {
        TValue old_value = current->pair.second;
        current->pair.second = v;
        return old_value;
    }
    // Key doesn't exist, create new node
    Node* new_node = new Node{ {k, v}, nullptr, nullptr };
    // Update the head if the new node is at the beginning
    if (previous == nullptr) 
        this->head = new_node;
    else 
        previous->next = new_node;
    new_node->previous = previous;
    new_node->next = current;
    // Update the tail if the new node is at the end
    if (current == nullptr) 
        this->tail = new_node;
    else 
        current->previous = new_node;
    this->length++;
    // New key, return NULL_TVALUE
    if (current == nullptr || current->pair.first != k) 
        return NULL_TVALUE;
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
TValue SortedMap::search(TKey k) const {
    Node* current = this->head;
    while (current != nullptr && current->pair.first != k) 
        current = current->next;
    if (current != nullptr && current->pair.first == k)
        return current->pair.second;
    return NULL_TVALUE;
}



// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
TValue SortedMap::remove(TKey k) {
    Node* current = this->head;
    TValue old_value = NULL_TVALUE;
    while (current != nullptr) 
    {
        if (current->pair.first == k) 
        {
            // Key was found, remove the node
            Node* to_remove = current;
            old_value = current->pair.second;
            current = current->next;
            if (to_remove->previous == nullptr)
                // Node is the head, update it
                this->head = current;
            else 
                // We update surroundings of the node, so it is placed right
                to_remove->previous->next = current;
            if (current == nullptr)
                // Node is the tail, update it
                this->tail = to_remove->previous;
            else 
                // We update surroundings of the node, so it is placed right
                current->previous = to_remove->previous;
            delete to_remove;
            this->length--;
        }
        else
            // Key was not found, go next
            current = current->next;
    }
    return old_value;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
int SortedMap::size() const {
    return this->length;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
bool SortedMap::isEmpty() const {
    return this->length == 0;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
int SortedMap::addIfNotPresent(SortedMap& sm)
{
    int counter = 0;
    SMIterator iterator = sm.iterator();
    iterator.first();
    while (iterator.valid())
    {
        TElem currentPair = iterator.getCurrent();
        if (this->search(currentPair.first) == NULL_TVALUE)
        {
            this->add(currentPair.first, currentPair.second);
            counter++;
        }
        iterator.next();
    }
    return counter;
}


// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
SortedMap::~SortedMap() {
    Node* current = this->head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
