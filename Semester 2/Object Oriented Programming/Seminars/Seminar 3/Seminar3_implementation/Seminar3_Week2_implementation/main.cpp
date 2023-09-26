#include "DynamicVector.h"
#include "LinkedList.h"
#include "List.h"
#include <assert.h>

void testList(List<int>& list)
{
	list.add(10);
	list.add(20);
	assert(list.getSize() == 2);
	assert(list[1] == 20);
	list[1] = 40;
	assert(list[1] == 40);
	list.add(30);
	assert(list.getSize() == 3);
}

int main()
{
	DynamicVector<int> v{};
	testList(v);
	LinkedList<int> l{};
	testList(l);

	return 0;
}