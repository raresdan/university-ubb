#pragma once

template <typename T>
class Node
{
private:
	T data;
	Node<t> next;
public:
	Node(const T& d, Node<T>* next = nullptr);
	void setNext(Node<T> next);
	Node<T>* getNext(Node<T> next);
	T& getData();
};

template <typename T>
class LinkedList
{
private:
	Node<T>* first;
public:
	LinkedList(Node<T>* f = nullptr);
	LinkedList(const LinkedList& l);
	~LinkedList();
		
	// assignment operator for a LinkedList
	LinkedList& operator=(const LinkedList& l);

	T& operator[](int pos);

	// Adds an element to the current LinkedList.
	void add(const T& e);

	int getSize() const;
};

template<typename T>
inline T& LinkedList<T>::operator[](int pos)
{
	Node<T>* aux = this->first;
	int i = 0;
	while (aux->getNext() != nullptr)
	{
		if (i == pos)
			return aux->getData();
		i++;
		aux = aux->getNext();
	}
}

template<typename T>
inline Node<T>::Node(const T& d, Node<T>* next): data{d}
{
}

template<typename T>
inline Node<T>* Node<T>::getNext(Node<T> next)
{
	return this->next;
}

template<typename T>
inline T& Node<T>::getData()
{
	return this->data;
}
