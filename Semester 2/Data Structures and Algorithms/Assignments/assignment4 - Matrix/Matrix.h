#pragma once

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

struct Triple {
	int line;
	int column;
	TElem value;
};


class Matrix {

private:
	int lines;  // Number of lines
	int columns;  // Number of columns
	Triple* elements;  // Array to store the <line, column, value> triples
	int capacity;  // Capacity of the hashtable
	int size;  // Number of elements stored in the hashtable
	int* next;  // Next pointers for coalesced chaining
	int* head;  // Head pointers for coalesced chaining

	// Hash function for the hashtable
	int hashFunction(int line, int column) const;

	// Resize and rehash the hashtable
	void resizeAndRehash();
public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	void setMainDiagonal(TElem elem);
};
