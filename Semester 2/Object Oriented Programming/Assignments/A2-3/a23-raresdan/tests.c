#include "tests.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void testDomain()
{
    Country country1 = createNewCountry("Romania", "Europe", 100);
    assert(strcmp(country1.name, "Romania") == 0);
    assert(strcmp(country1.continent, "Europe") == 0);
    assert(country1.population == 100);

    Country country2 = createNewCountry("Moldova", "Europe", 100);
    assert(strcmp(country1.name, country2.name) != 0);
    assert(strcmp(country2.continent, "Africa") != 0);
    assert(country2.population != 200);

    assert(strcmp(getCountryName(&country1), "Romania") == 0);
    assert(strcmp(getCountryContinent(&country1), "Europe") == 0);
    assert(getCountryPopulation(&country1) == 100);

    destroyCountry(country1);
    destroyCountry(country2);
}

void testRepository()
{
    Repository testRepository = createRepository();
    assert(testRepository.allCountries.size == 10);
    assert(testRepository.allCountries.capacity == 10);
    
    Country country1 = createNewCountry("Bulgaria", "Europe", 100);
    addCountryToRepository(&testRepository, country1);
    assert(testRepository.allCountries.size == 11);
    assert(testRepository.allCountries.capacity == 20);
    
    int indexOfSearchedCountry = findCountryByItsName(&testRepository, country1.name);
    assert(indexOfSearchedCountry == 10);
    
    Country countryToTestUpdate = createNewCountry("Belgium", "Europe", 200);
    updateCountryFromRepository(&testRepository, indexOfSearchedCountry, countryToTestUpdate);
    assert(strcmp(testRepository.allCountries.elements[indexOfSearchedCountry].name, "Belgium") == 0);
    assert(strcmp(testRepository.allCountries.elements[indexOfSearchedCountry].continent, "Europe") == 0);
    assert(testRepository.allCountries.elements[indexOfSearchedCountry].population == 200);
    
    Country country2 = createNewCountry("Moldova", "Europe", 100);
    addCountryToRepository(&testRepository, country2);
    assert(testRepository.allCountries.size == 12);
    updateInCaseOfMigration(&testRepository, 11, 10, 100);
    assert(testRepository.allCountries.elements[11].population == 0);
    assert(testRepository.allCountries.elements[10].population == 300);
    deleteCountryFromRepository(&testRepository, findCountryByItsName(&testRepository, "Moldova"));
    assert(testRepository.allCountries.size == 11);

    destroyDynamicArray(&testRepository.allCountries);
    destroyCountry(country1);
    destroyCountry(country2);
    destroyCountry(countryToTestUpdate);
}

void testUndoRedoRepository()
{
    UndoRedoRepository testUndoRedoRepository = createUndoRedoRepository(1);
    assert(testUndoRedoRepository.undoSize == 0);
    assert(testUndoRedoRepository.redoSize == 0);
    assert(testUndoRedoRepository.undoCapacity == 1);
    assert(testUndoRedoRepository.redoCapacity == 1);
    
    Repository conutriesRepository = createRepository();
    addUndoElement(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.undoSize == 1);
    Country country1 = createNewCountry("Romania", "Europe", 100);
    addCountryToRepository(&conutriesRepository, country1);

    addRedoElement(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.redoSize == 1);

    addUndoElement(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.undoSize == 2);
    assert(testUndoRedoRepository.undoCapacity == 2);

    addRedoElement(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.redoSize == 2);
    assert(testUndoRedoRepository.redoCapacity == 2);

    popLastUndo(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.undoSize == 1);

    popLastRedo(&testUndoRedoRepository, &conutriesRepository);
    assert(testUndoRedoRepository.redoSize == 1);

    destroyDynamicArray(&conutriesRepository.allCountries);
    free(testUndoRedoRepository.undo);
    free(testUndoRedoRepository.redo);
    destroyCountry(country1);
}

void testService()
{
    UndoRedoRepository testUndoRedoRepository = createUndoRedoRepository(10);
    Repository testRepository = createRepository();

    bool validityChecker = checkIfContinentIsValid("Europe");
    assert(validityChecker == true);
    validityChecker = checkIfContinentIsValid("Eu");
    assert(validityChecker == false);

    int undoChecker = ServiceUndo(&testRepository, &testUndoRedoRepository);
    int redoChecker = ServiceRedo(&testRepository, &testUndoRedoRepository);
    assert(undoChecker == 1);
    assert(redoChecker == 1);

    int addChecker = addCountryToService(&testRepository, &testUndoRedoRepository, "Bulgaria", "Eu", 100);
    assert(addChecker == 1);
    addChecker = addCountryToService(&testRepository, &testUndoRedoRepository, "Romania", "Europe", 100);
    assert(addChecker == 2);
    addChecker = addCountryToService(&testRepository, &testUndoRedoRepository, "Latvia", "Europe", 100);
    assert(addChecker == 0);

    bool deleteChecker = deleteCountryFromService(&testRepository, &testUndoRedoRepository, "Moldova");
    assert(deleteChecker == false);
    deleteChecker = deleteCountryFromService(&testRepository, &testUndoRedoRepository, "Romania");
    assert(deleteChecker == true);

    undoChecker = ServiceUndo(&testRepository, &testUndoRedoRepository);
    assert(undoChecker == 0);
    redoChecker = ServiceRedo(&testRepository, &testUndoRedoRepository);
    assert(redoChecker == 0);
    ServiceUndo(&testRepository, &testUndoRedoRepository);
 
    int updateChecker = updateCountryFromService(&testRepository, &testUndoRedoRepository, "Romania", "SUA", "A", 100);
    assert(updateChecker == 1);
    updateChecker = updateCountryFromService(&testRepository, &testUndoRedoRepository, "USA", "Romania", "Europe", 100);
    assert(updateChecker == 2);
    updateChecker = updateCountryFromService(&testRepository, &testUndoRedoRepository, "Romania", "Roma", "Europe", 100);
    assert(updateChecker == 0);
    updateChecker = updateCountryFromService(&testRepository, &testUndoRedoRepository, "Roma", "Romania", "Europe", 1000);
    assert(updateChecker == 0);
    addChecker = addCountryToService(&testRepository, &testUndoRedoRepository, "Moldova", "Europe", 100);
    assert(addChecker == 0);

    int migrationChecker = doMigrationActivity(&testRepository,  "Belgium", "Latvia", 100);
    assert(migrationChecker == 0);
    migrationChecker = doMigrationActivity(&testRepository, "Belgium", "X", 100);
    assert(migrationChecker == 2);
    migrationChecker = doMigrationActivity(&testRepository, "X", "Belgium", 100);
    assert(migrationChecker == 1);

    char filterStringTester[] = "\0";
    Country* validCountriesArray = (Country*)malloc(testRepository.allCountries.capacity * sizeof(Country));
    int filterChecker = filterByTheNameOfTheCountry(&testRepository, filterStringTester, validCountriesArray);
    assert(filterChecker == testRepository.allCountries.size);
    free(validCountriesArray);
    validCountriesArray = (Country*)malloc(testRepository.allCountries.capacity * sizeof(Country));
    filterChecker = filterByTheNameOfTheCountry(&testRepository, "z", validCountriesArray);
    assert(filterChecker == 0);
    free(validCountriesArray);
    validCountriesArray = (Country*)malloc(testRepository.allCountries.capacity * sizeof(Country));
    filterChecker = filterByTheNameOfTheCountry(&testRepository, "Ro", validCountriesArray);
    assert(filterChecker == 1);
    free(validCountriesArray);
}

void testAll()
{
    testDomain();
    testRepository();
    testUndoRedoRepository();
    testService();
    printf("Tests run succesfully!\n\n");
}
