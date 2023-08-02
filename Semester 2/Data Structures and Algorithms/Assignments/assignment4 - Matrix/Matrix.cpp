#include "Matrix.h"
#include <exception>
#include <utility>
using namespace std;

// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
int Matrix::hashFunction(int line, int column) const
{
	return (line +  column)  % this->capacity;
}


// BC = Theta(n)
// WC = Theta(n)
// AC = Theta(n)
// Overall = Theta(n)
void Matrix::resizeAndRehash()
{
	int newCapacity = this->capacity * 2;
	Triple* newElements = new Triple[newCapacity];
	int* newNext = new int[newCapacity];
	int* newHead = new int[newCapacity];
	for (int i = 0; i < newCapacity; i++) {
		newNext[i] = -1;
		newHead[i] = -1;
	}
	for (int i = 0; i <= this->size; i++)
	{
		newElements[i] = elements[i];
	}
	// rehash the elements into the new hashtable
	for (int i = 0; i < this->size; i++) {
		int hash = hashFunction(this->elements[i].line, this->elements[i].column);

		if (newHead[hash] == -1)
			newHead[hash] = i;
		else {
			int index = newHead[hash];
			while (newNext[index] != -1)
				index = newNext[index];
			newNext[index] = i;
		}
	}

	delete[] this->elements;
	delete[] this->next;
	delete[] this->head;

	this->elements = newElements;
	this->next = newNext;
	this->head = newHead;
	this->capacity = newCapacity;
}

Matrix::Matrix(int nrLines, int nrCols) : size(0), lines(nrLines), columns(nrCols){
	this->columns = nrCols;
	this->lines = nrLines;
	this->capacity = this->lines + this->columns;
	this->elements = new Triple[capacity];
	this->next = new int[capacity];
	this->head = new int[capacity];
	for (int i = 0; i < capacity; i++) {
		this->next[i] = -1;
		this->head[i] = -1;
	}
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
int Matrix::nrLines() const {
	return this->lines;
}


// BC = Theta(1)
// WC = Theta(1)
// AC = Theta(1)
// Overall = Theta(1)
int Matrix::nrColumns() const {
	return this->columns;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = O(n)
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i > this->lines || j < 0 || j > this->columns)
		throw std::exception("Invalid position");

	int index = this->head[hashFunction(i, j)];
	while (index != -1) {
		if (this->elements[index].line == i && this->elements[index].column == j)
			return this->elements[index].value;
		index = this->next[index];
	}

	return NULL_TELEM;
}

// BC = Theta(1)
// WC = Theta(n)
// AC = Theta(n)
// Overall = O(n)
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i > this->lines || j < 0 || j > this->columns)
		throw std::exception("Invalid position");
	
	double loadFactor = static_cast<double>(this->size) / this->capacity;
	if (loadFactor > 0.75)
		this->resizeAndRehash();
	
	int hash = hashFunction(i, j);
	int prevIndex = -1;
	int index = this->head[hash];

	// search for the element in the hashtable
	while (index != -1) {
		if (this->elements[index].line == i && this->elements[index].column == j) {
			TElem prevValue = this->elements[index].value;
			this->elements[index].value = e;
			return prevValue;
		}
		prevIndex = index;
		index = this->next[index];
	}

	// element not found, insert a new triple
	Triple newTriple = { i, j, e };
	int newIndex = this->size;
	this->elements[newIndex] = newTriple;

	// update next and head for coalesced chaining
	if (prevIndex != -1)
		this->next[prevIndex] = newIndex;
	else
		this->head[hash] = newIndex;

	this->next[newIndex] = -1;
	this->size++;

	return NULL_TELEM;
}

// BC = Theta(n)
// WC = Theta(n^2)
// AC = Theta(n^2)
// Overall = O(n^2)
void Matrix::setMainDiagonal(TElem elem)
{	
	if (this->lines != this->columns)
		throw std::exception("Matrix is not square!");

	for (int i = 0; i < this->lines; i++)
		if(this->element(i,i) != elem)
			this->modify(i, i, elem);

}


