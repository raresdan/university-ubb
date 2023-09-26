#include "Tests.h"
#include "DynamicVector.h"
#include "LinkedList.h"
#include <assert.h>

void Tests::testDynamicVector()
{
	DynamicVector<int> v1{};
	v1.add(10);
	v1.add(20);
	assert(v1.getSize() == 2);
	assert(v1[1] == 20);
	v1[1] = 40;
	assert(v1[1] == 40);
	v1.add(30);
	assert(v1.getSize() == 3);

	DynamicVector<int> v2{ v1 };
	assert(v2.getSize() == 3);

	DynamicVector<int> v3;
	v3 = v1;
	assert(v3[0] == 10);

	// test iterator
	DynamicVector<int>::iterator it = v1.begin();
	assert(*it == 10);
	assert(it != v1.end());
	++it;
	assert(*it == 40);
}

void Tests::testLinkedList()
{
	LinkedList<int> l1{};
	l1.add(10);
	l1.add(20);
	assert(l1.getSize() == 2);
	assert(l1[1] == 20);
	l1[1] = 40;
	assert(l1[1] == 40);
	l1.add(30);
	assert(l1.getSize() == 3);

	LinkedList<int> l2{ l1 };
	assert(l2.getSize() == 3);

	LinkedList<int> l3;
	l3 = l1;
	assert(l3[0] == 10);
}
