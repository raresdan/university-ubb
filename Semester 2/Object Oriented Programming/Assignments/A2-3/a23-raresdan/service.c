#include "service.h"
#include <stdio.h>
#include <string.h>

bool checkIfContinentIsValid(char continentToBeChecked[])
{
	if (strcmp(continentToBeChecked, "Europe") == 0 || strcmp(continentToBeChecked, "Asia") == 0 || strcmp(continentToBeChecked, "America") == 0 || strcmp(continentToBeChecked, "Australia") == 0 || strcmp(continentToBeChecked, "Africa") == 0 )
	{
		return true;
	}
	return false;
}

int addCountryToService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeAdded[], char continentOfTheCountryToBeAdded[], int populationOfTheCountryToBeAdded)
{
	if (!checkIfContinentIsValid(continentOfTheCountryToBeAdded))
	{
		return 1;
	}
	for (int index = 0; index < countriesRepository->allCountries.size; index++) 
		if (strcmp(getCountryName(&countriesRepository->allCountries.elements[index]), nameOfTheCountryToBeAdded) == 0)
			return 2;
	Country newCountry = createNewCountry(nameOfTheCountryToBeAdded, continentOfTheCountryToBeAdded, populationOfTheCountryToBeAdded);
	addUndoElement(undoRedoRepository, countriesRepository); 
	addCountryToRepository(countriesRepository, newCountry);
	return 0;
}

bool deleteCountryFromService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeDeleted[])
{
	int indexOfTheCountryToBeDeleted = findCountryByItsName(countriesRepository, nameOfTheCountryToBeDeleted);
	if (indexOfTheCountryToBeDeleted == -1)
	{
		return false;
	}
	else 
	{
		addUndoElement(undoRedoRepository, countriesRepository);
		deleteCountryFromRepository(countriesRepository, indexOfTheCountryToBeDeleted);
		return true;
	}
}

int updateCountryFromService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeUpdated[], char newNameOfTheCountryToBeUpdated[], char newContinentOfTheCountryToBeUpdated[], int newPopulationOfTheCountryToBeUpdated)
{
	if (!checkIfContinentIsValid(newContinentOfTheCountryToBeUpdated))
	{
		return 1;
	}
	int indexOfTheCountryToBeUpdated = findCountryByItsName(countriesRepository, nameOfTheCountryToBeUpdated);
	if (indexOfTheCountryToBeUpdated == -1)
	{
		return 2;
	}
	Country updatedCountry = createNewCountry(newNameOfTheCountryToBeUpdated, newContinentOfTheCountryToBeUpdated, newPopulationOfTheCountryToBeUpdated);
	addUndoElement(undoRedoRepository, countriesRepository);
	updateCountryFromRepository(countriesRepository, indexOfTheCountryToBeUpdated, updatedCountry);
	return 0;
}

int filterByTheNameOfTheCountry(Repository *countriesRepository, const char stringByWhichToFilter[], Country *validCountriesAfterFiltering[])
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (strstr(countriesRepository->allCountries.elements[i].name, stringByWhichToFilter) != NULL)
		{
			validCountriesAfterFiltering[validCountryCount++] = &countriesRepository->allCountries.elements[i];
		}
	}
	return validCountryCount;
}

int doMigrationActivity(Repository *countriesRepository, char nameOfCountryFromWhereMigrate[], char nameOfCountryToWhereMigrate[], long int numberOfMigrators)
{
	int indexOfOldCountry = findCountryByItsName(countriesRepository, nameOfCountryFromWhereMigrate);
	int indexOfNewCountry = findCountryByItsName(countriesRepository, nameOfCountryToWhereMigrate);
	if (indexOfOldCountry == -1)
		return 1;
	if (indexOfNewCountry == -1)
		return 2;
	updateInCaseOfMigration(countriesRepository, indexOfOldCountry, indexOfNewCountry, numberOfMigrators);
	return 0;
}

int filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(Repository *countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan)
{
	int validCountryCount = 0;
	for (int i = 0; i < countriesRepository->allCountries.size; i++)
	{
		if (strcmp(countriesRepository->allCountries.elements[i].continent, continentByWhichToFilter) == 0 && countriesRepository->allCountries.elements[i].population > valueThatPopulationShouldBeHigherThan)
		{
			validCountriesAfterFiltering[validCountryCount++] = countriesRepository->allCountries.elements[i];
		}
	}

	for (int i = 0; i < validCountryCount - 1; i++)
	{
		for (int j = i + 1; j < validCountryCount; j++)
		{
			if (strcmp(validCountriesAfterFiltering[i].name, validCountriesAfterFiltering[j].name) > 0)
			{
				Country temp = validCountriesAfterFiltering[i];
				validCountriesAfterFiltering[i] = validCountriesAfterFiltering[j];
				validCountriesAfterFiltering[j] = temp;
			}
		}
	}

	return validCountryCount;
}

int ServiceUndo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
	if (undoRedoRepository->undoSize == 0)
		return 1;
	addRedoElement(undoRedoRepository, countriesRepository); // add the current repo for the redo operation
	popLastUndo(undoRedoRepository, countriesRepository);
	return 0;
}

int ServiceRedo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
	if (undoRedoRepository->redoSize == 0)
		return 1;
	addUndoElement(undoRedoRepository, countriesRepository); // add the current repo for the undo operation
	popLastRedo(undoRedoRepository, countriesRepository);
	return 0;
}
