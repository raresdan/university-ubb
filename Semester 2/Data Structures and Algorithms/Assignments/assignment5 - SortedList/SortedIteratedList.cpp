#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    this->capacity = 1;
    this->sizeOfList = 0;
    this->relation = r;
    this->elements = new BSTNode[capacity];
    this->root = -1;
}

int SortedIteratedList::size() const {
	return this->sizeOfList;

}

bool SortedIteratedList::isEmpty() const {
	return this->sizeOfList == 0;

}

ListIterator SortedIteratedList::first() const {
	ListIterator it = ListIterator(*this);
    it.first();
	return it;
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (poz.valid() == false)
		throw exception();
	return poz.getCurrent();

}

TComp SortedIteratedList::remove(ListIterator& pos) {
    if (!pos.valid()) {
        throw std::exception("Invalid position!");
    }

    int currentNodeIndex = pos.current;
    BSTNode& currentNode = this->elements[currentNodeIndex];
    TComp removedElement = currentNode.data;

    if (currentNode.left != -1 && currentNode.right != -1) {
        // Case 1: Node to be removed has both left and right children
        int successorNodeIndex = currentNode.right;
        while (this->elements[successorNodeIndex].left != -1) {
            successorNodeIndex = this->elements[successorNodeIndex].left;
        }
        pos.current = successorNodeIndex;
        currentNode.data = this->elements[successorNodeIndex].data;
        this->remove(pos);
    }
    else if (currentNode.left != -1) {
        // Case 2: Node to be removed has only the left child
        int parentNodeIndex = this->parent(currentNode.data);
        if (parentNodeIndex == -1) {
            this->root = currentNode.left;
        }
        else if (this->elements[parentNodeIndex].left == currentNodeIndex) {
            this->elements[parentNodeIndex].left = currentNode.left;
        }
        else {
            this->elements[parentNodeIndex].right = currentNode.left;
        }
    }
    else if (currentNode.right != -1) {
        // Case 3: Node to be removed has only the right child
        int parentNodeIndex = this->parent(currentNode.data);
        if (parentNodeIndex == -1) {
            this->root = currentNode.right;
        }
        else if (this->elements[parentNodeIndex].left == currentNodeIndex) {
            this->elements[parentNodeIndex].left = currentNode.right;
        }
        else {
            this->elements[parentNodeIndex].right = currentNode.right;
        }
    }
    else {
        // Case 4: Node to be removed is a leaf node (no children)
        int parentNodeIndex = this->parent(currentNode.data);
        if (parentNodeIndex == -1) {
            this->root = -1;
        }
        else if (this->elements[parentNodeIndex].left == currentNodeIndex) {
            this->elements[parentNodeIndex].left = -1;
        }
        else {
            this->elements[parentNodeIndex].right = -1;
        }
    }

    // Update the sizes of the left subtrees of all ancestors
    int ancestorIndex = this->parent(currentNode.data);
    while (ancestorIndex != -1) {
        this->elements[ancestorIndex].leftSize--;
        ancestorIndex = this->parent(this->elements[ancestorIndex].data);
    }

    // Decrease the size of the list
    this->sizeOfList--;

    return removedElement;

}

void SortedIteratedList::add(TComp e) {
    // Resize if needed
    if (this->sizeOfList == this->capacity)
    {
        int newCapacity = this->capacity * 2;
        BSTNode* newElements = new BSTNode[newCapacity];
        for (int i = 0; i < this->sizeOfList; i++) {
            newElements[i] = this->elements[i];
        }
        delete[] this->elements;
        this->elements = newElements;
        this->capacity = newCapacity;
    }
    BSTNode newNode;
    newNode.data = e;
    newNode.left = -1;
    newNode.right = -1;
    newNode.leftSize = 0;

    // If the list is empty, set the new node as the root
    if (this->isEmpty()) {
        this->root = e;
        this->elements[0] = newNode;
        this->sizeOfList++;
        return;
    }

    int currentNodeIndex = this->root;
    while (currentNodeIndex != -1) {
        BSTNode& currentNode = this->elements[currentNodeIndex];
        currentNode.leftSize++;  // Increment the size of the left subtree

        // Determine the direction to traverse based on the relation between the new element and the current node's data
        if (relation(e, currentNode.data)) {
            // Go to the left subtree
            if (currentNode.left == -1) {
                // Found an empty spot on the left, insert the new node here
                currentNode.left = this->sizeOfList;
                this->elements[this->sizeOfList] = newNode;
                this->sizeOfList++;
                return;
            }
            currentNodeIndex = currentNode.left;
        }
        else {
            // Go to the right subtree
            if (currentNode.right == -1) {
                // Found an empty spot on the right, insert the new node here
                currentNode.right = this->sizeOfList;
                this->elements[this->sizeOfList] = newNode;
                this->sizeOfList++;
                return;
            }
            currentNodeIndex = currentNode.right;
        }
    }
}

SortedIteratedList::~SortedIteratedList() {
	delete[] this->elements;
}


ListIterator SortedIteratedList::search(TComp e) const
{
    ListIterator iterator = ListIterator(*this);
    int currentNode = this->root;
    bool found = false;
    while (currentNode != -1 && !found)
    {
        if (this->elements[currentNode].data = e)
            found = true;
        else if (relation(e, this->elements[currentNode].data))
            currentNode = this->elements[currentNode].left;
        else
            currentNode = this->elements[currentNode].right;
    }
    if (found)
    {
        iterator.current = currentNode;
        return iterator;
    }
    return iterator;
}

int SortedIteratedList::parent(TComp e) const {
    int parentNode;
    int currentNode = this->root;
    if (this->elements[currentNode].data == e)
    {
        parentNode = -1;
    }
    else
    {
        while (currentNode != -1 && this->elements[currentNode].left != e && this->elements[currentNode].right != e)
        {
            if(relation(this->elements[currentNode].data, e))
                currentNode = this->elements[currentNode].left;
            else
                currentNode = this->elements[currentNode].right;
        }
        parentNode = currentNode;
    }
    return parentNode;
}