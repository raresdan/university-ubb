#include "Tests.h"
#include <assert.h>

void Tests::testAddRepository()
{
	std::vector<Car> initialCars = {};
	Repository repository{ initialCars };
	assert(repository.getAllCars().size() == 0);
	Car validCar{ "Volvo", "V40", 2012, "blue" };
	assert(repository.addCar(validCar) == true);
	assert(repository.addCar(validCar) == false);
	assert(repository.getAllCars().size() == 1);
}

void Tests::testAddService()
{
	std::vector<Car> initialCars = {};
	Repository repository{ initialCars };
	Service service{ repository };
	assert(service.getAllCars().size() == 0);
	service.addCar("Volvo", "V40", 2012, "blue");
	assert(service.getAllCars().size() == 1);
}

void Tests::testVintageCars()
{
	std::vector<Car> initialCars = {};
	Repository repository{ initialCars };
	Service service{ repository };
	std::vector<Car> vintageCars = service.getVintageCars();
	assert(vintageCars.size() == 0);
	service.addCar("Volvo", "V40", 1912, "blue");
	vintageCars = service.getVintageCars();
	assert(vintageCars.size() == 1);
}

void Tests::testAll()
{
	testAddRepository();
	testAddService();
	testVintageCars();
}
