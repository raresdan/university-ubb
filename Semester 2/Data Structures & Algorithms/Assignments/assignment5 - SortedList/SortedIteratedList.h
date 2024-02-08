#pragma once
//DO NOt INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
typedef bool (*Condition)(TComp);
#define NULL_TCOMP -11111


struct BSTNode {
	TComp data;
	int left;
	int right;
	int leftSize;
};

class SortedIteratedList {
private:
	friend class ListIterator;
private:
	//TODO - Representation
	// Using a BST with linked representation on an array.
	// Every node of the BST will retain the number of elements to the left of the node as well.
	BSTNode* elements;
	int root;
	int capacity;
	int sizeOfList;
	Relation relation;
	
public:
	// constructor
	SortedIteratedList(Relation r);

	// returns the number of elements from the list
	int size() const;

	// verifies if the list is empty
	bool isEmpty() const;

	// returns the first position from the list
	ListIterator first() const;

	// returns the element from the given position
	//throws an exception if the position is not valid
	TComp getElement(ListIterator pos) const;

	// adds a new element to the list
	void add(TComp e);

	// removes the element from position pos
	//returns the removed element
	//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	//throws an exception if the position is not valid
	TComp remove(ListIterator& poz);

	// searches for the first occurrence of an element 
	//returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TComp e) const;

	int parent(TComp e) const;
	//TODO elimina
	//void print();

	//destructor
	~SortedIteratedList();

	
	
	//Extra functionality
	//keeps in the SortedList only the elements that respect the given condition
	//void filter(Condition cond);
	//
	//where condition is a function which takes as parameter a TComp and returns true or false
	//depending on wether the element respects the condition.
	//Obs. add the following typedef to the beginning of SortedList.h
	//
	//typedef bool (*Condition)(TComp);

};
