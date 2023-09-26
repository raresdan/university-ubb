#include "Song.h"
#include "DynamicVector.h"
#include <iostream>
#include <crtdbg.h>

using namespace std;

void testDynamicVector()
{
	DynamicVector<int> vect1{};

	/*
	* Executing this tries to free again the elems of vect1, after they were already destoried, 
	so it is going to crash as it creates a shallow copy (default copy constructor) of vect1, both elems point to the same adress

	DynamicVector<int> vect2{vect1};
	DynamicVector<int> vect2 = vect1
	;
	*/
}

int main()
{
	{
		Song s{ "Pink Floyd", "Comforatbly numb", 320 };
		cout << s.getTitle();
	}

	/*Song* s1 = new Song{ "A", "B", 100 };
	delete s1;*/

	testDynamicVector();
	_CrtDumpMemoryLeaks();

	return 0;
}