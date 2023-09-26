#pragma once
#include "country.h"
#include "dynamicArray.h"

typedef struct
{
	DynamicArray allCountries;
}Repository;

Repository createRepository();
void addCountryToRepository(Repository *countriesRepository, Country countryToBeAdded);
void deleteCountryFromRepository(Repository *countriesRepository, int indexOfTheCountryToBeDeleted);
void updateCountryFromRepository(Repository *countriesRepository, int indexOfTheCountryToBeUpdated, Country countryWithUpdatedData);
void updateInCaseOfMigration(Repository *countriesRepository,int indexOfOldCountry, int indexOfNewCountry, long int numberOfMigrators);
int findCountryByItsName(Repository *countriesRepository, char stringThatIsBeingSearched[]);