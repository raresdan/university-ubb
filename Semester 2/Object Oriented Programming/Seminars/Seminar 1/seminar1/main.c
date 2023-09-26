#include "Planet.h"
#include <crtdbg.h>
#include "DynamicArray.h"

int main()
{
	Planet p = createPlanet("HD 18733 b", "a blue-ish planet", 10);
	Planet p2 = p;

	//destroyPlanet(p);
	_CrtDumpMemoryLeaks();
	return 0;
}
