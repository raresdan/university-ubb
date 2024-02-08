#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list) {
	this->current = -1;
	this->currentIndex = 0;
	this->elements = this->sortArray();
	this->length = list.size();
}


void ListIterator::first() {

	this->current = this->elements[0];
	this->currentIndex = 0;
}

void ListIterator::next() {
	if (!valid()) {
		throw std::exception();
	}
	this->currentIndex++;
	if (this->currentIndex >= this->length) {
		this->current = -1;
	}
	else {
		this->current = this->elements[this->currentIndex];
	}
}

bool ListIterator::valid() const {
	return this->currentIndex < this->length;
}

TComp ListIterator::getCurrent() const {
	if (!valid())
		throw std::exception("Invalid iterator!");
	return this->current;
}

TComp* ListIterator::inorderTraversal(int node, TComp* array, int& index)
{
	if (node == -1) {
		return nullptr;
	}
	
	const BSTNode& currentNode = list.elements[node];
	inorderTraversal(currentNode.left, array, index);
	array[index++] = currentNode.data;
	inorderTraversal(currentNode.right, array, index);
}

TComp* ListIterator::sortArray()
{
	TComp* array = new TComp[list.sizeOfList];
	int index = 0;
	array = this->inorderTraversal(list.root, array, index);
	bool swapped;

	for (int i = 0; i < this->length - 1; i++) {
		swapped = false;

		// Compare adjacent elements and swap them if necessary
		for (int j = 0; j < this->length - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				int aux = array[j];
				array[j] = array[j + 1];
				array[j + 1] = aux;
				swapped = true;
			}
		}
		if (!swapped) {
			break;
		}
	}
	return array;
}


