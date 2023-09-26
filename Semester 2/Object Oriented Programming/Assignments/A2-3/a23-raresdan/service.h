#pragma once
#include "repository.h"
#include "undoRedo.h"
#include <stdbool.h>

bool checkIfContinentIsValid(char continentToBeChecked[]);
int addCountryToService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeAdded[], char continentOfTheCountryToBeAdded[], int populationOfTheCountryToBeAdded);
bool deleteCountryFromService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeDeleted[]);
int updateCountryFromService(Repository *countriesRepository, UndoRedoRepository* undoRedoRepository, char nameOfTheCountryToBeUpdated[], char newNameOfTheCountryToBeUpdated[], char newContinentOfTheCountryToBeUpdated[], int newPopulationOfTheCountryToBeUpdated);
int filterByTheNameOfTheCountry(Repository* countriesRepository, const char stringByWhichToFilter[], Country* validCountriesAfterFiltering[]);
int doMigrationActivity(Repository* countriesRepository, char nameOfCountryFromWhereMigrate[], char nameOfCountryToWhereMigrate[], long int numberOfMigrators);
int filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(Repository* countriesRepository, Country validCountriesAfterFiltering[], char continentByWhichToFilter[], long int valueThatPopulationShouldBeHigherThan);
int ServiceUndo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
int ServiceRedo(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
