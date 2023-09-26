#pragma once
#include "List.h"

template <typename T>
class Node
{
private:
	T data;
	Node<T>* next;

public:
	Node(T d, Node<T>* n) : data{ d }, next{ n } {}
	
	T& getData() { return this->data; }
	Node<T>* getNext() const { return this->next; }
	void setNext(Node<T>* n) { this->next = n; }
	void setData(T d) { this->data = d; }
};

template <typename T>
class LinkedList: public List<T>
{
private:
	Node<T>* first;
	int size;

public:
	LinkedList(Node<T>* f = nullptr);
	LinkedList(const LinkedList& l);
	~LinkedList();
		
	// assignment operator for a DynamicVector
	LinkedList& operator=(const LinkedList& l);

	T& operator[](int pos);

	// Adds an element to the current LinkedList.
	void add(const T& e);

	int getSize() const { return this->size; }
};

template<typename T>
inline LinkedList<T>::LinkedList(Node<T>* f) : first{ f }, size{ 0 }
{
}

template<typename T>
inline LinkedList<T>::LinkedList(const LinkedList & l): first{ nullptr }, size{ 0 }
{
	auto aux = l.first;
	while (aux != nullptr)
	{
		this->add(aux->getData());
		aux = aux->getNext();
	}
}

template<typename T>
inline LinkedList<T>::~LinkedList()
{
	while (this->first != nullptr)
	{
		auto aux = this->first;
		this->first = this->first->getNext();
		delete aux;
		aux = nullptr;
	}
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList & l)
{
	// TO DO
	return LinkedList{};
}

template<typename T>
T& LinkedList<T>::operator[](int pos)
{
	int i = 0;
	auto aux = this->first;
	while (aux != nullptr)
	{
		if (i == pos)
			return aux->getData();
		i++;
		aux = aux->getNext();
	}

	// TODO throw exception if pos is out of bounds
}

template<typename T>
void LinkedList<T>::add(const T & e)
{
	auto node = new Node<T>{ e, nullptr };

	if (this->first == nullptr)
	{
		this->first = node;
	}
	else
	{
		auto aux = this->first;
		if (aux == nullptr)
			return;
		while (aux->getNext() != nullptr)
		{
			aux = aux->getNext();
		}
		aux->setNext(node);
	}

	this->size++;
}
