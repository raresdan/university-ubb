#define _CRT_SECURE_NO_WARNINGS
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void displayAllCountries(Repository* countriesRepository)
{
    int index;
    for (index = 0; index < getDynamicArraySize(&countriesRepository->allCountries); index++) 
        printf("#%d Country: %s, Continent: %s, Population: %ld \n", index + 1, countriesRepository->allCountries.elements[index].name, countriesRepository->allCountries.elements[index].continent, countriesRepository->allCountries.elements[index].population);
    
}

void addNewCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char nameOfTheCountryToBeAdded[50];
    char continentOfTheCountryToBeAdded[50];
    char populationOfTheCountryToBeAdded[50] = "";
    printf("Name of the country: ");
    scanf(" %s", &nameOfTheCountryToBeAdded);
    printf("Name of the continent: ");
    scanf("%s", &continentOfTheCountryToBeAdded);
    printf("Population: ");
    scanf("%s", &populationOfTheCountryToBeAdded);
    long int populationOfTheCountryToBeAddedIntegerValue = strtol(populationOfTheCountryToBeAdded, NULL, 10);
    int addedStatus = addCountryToService(countriesRepository, undoRedoRepository, nameOfTheCountryToBeAdded, continentOfTheCountryToBeAdded, populationOfTheCountryToBeAddedIntegerValue);
    if (addedStatus == 2)
        printf("Country %s already exists in the list.\n", nameOfTheCountryToBeAdded);
    else if (addedStatus == 1)
        printf("The continent %s is not a valid one.\n", continentOfTheCountryToBeAdded);
    else
        printf("Country %s successfully added.\n", nameOfTheCountryToBeAdded);
}

void deleteCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char nameOfTheCountryToBeDeleted[50];
    printf("Enter the name of the country you want to delete: ");
    scanf(" %s", &nameOfTheCountryToBeDeleted);
    bool deletedStatus = deleteCountryFromService(countriesRepository, undoRedoRepository, nameOfTheCountryToBeDeleted);
    if (deletedStatus == false)
        printf("The country you wanted to delete is not in the list.\n");
    else
        printf("Entry %s successfully deleted.\n", nameOfTheCountryToBeDeleted);
}

void updateCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    char updateOption[5] = "\0";
    printf("Choose a type of update: \n"
        "1. Update name, continent and/or population.\n"
        "2. Migration. \n");
    scanf("%s", &updateOption);
    int updateOptionIntegerValue = strtol(updateOption, NULL, 10);
    if (updateOptionIntegerValue == 1) {
        char nameOfTheOldCountry[50];
        char nameOfTheNewCountry[50];
        char continentOfTheNewCountry[50];
        char populationOfTheNewCountry[50] = "";
        long int populationOfTheNewCountryIntegerValue;
        printf("Old name of the country: ");
        scanf("%s", &nameOfTheOldCountry);
        printf("New name of the country: ");
        scanf("%s", &nameOfTheNewCountry);
        printf("Continent of the country: ");
        scanf("%s", &continentOfTheNewCountry);
        printf("Population of the country: ");
        scanf("%s", &populationOfTheNewCountry);
        populationOfTheNewCountryIntegerValue = strtol(populationOfTheNewCountry, NULL, 10);
        int updatedStatus = updateCountryFromService(countriesRepository, undoRedoRepository, nameOfTheOldCountry, nameOfTheNewCountry, continentOfTheNewCountry, populationOfTheNewCountryIntegerValue);
        if (updatedStatus == 2)
            printf("Country %s does not exist.\n", nameOfTheNewCountry);
        else if (updatedStatus == 1)
            printf("Invalid input for the continent.\n");
        else
            printf("Country %s successfully updated.\n", nameOfTheOldCountry);
    }
    
    else if (updateOptionIntegerValue == 2) {
        char nameOfTheOldCountry[50];
        char nameOfTheNewCountry[50];
        char numberOfMigrators[50] = "";
        printf("Name of the country from where to migrate: ");
        scanf("%s", &nameOfTheOldCountry);
        printf("Name of the country to where to migrate: ");
        scanf("%s", &nameOfTheNewCountry);
        printf("Number of migrators: ");
        scanf("%s", &numberOfMigrators);
        long int numberOfMigratorsIntegerValue = strtol(numberOfMigrators, NULL, 10);
        int updatedStatus = doMigrationActivity(countriesRepository, nameOfTheOldCountry, nameOfTheNewCountry, numberOfMigratorsIntegerValue);
        if (updatedStatus == 1)
            printf("Country %s does not exist.\n", nameOfTheOldCountry);
        else if (updatedStatus == 2)
            printf("Country %s does not exist. \n", nameOfTheNewCountry);
        else
            printf("%ld people migrated from %s to %s.\n", numberOfMigratorsIntegerValue, nameOfTheOldCountry, nameOfTheNewCountry);

    }
}

void searchCountryByNameUi(Repository* countriesRepository)
{
    char stringByWhichToFilter[50];
    Country* validCountriesAfterFiltering[50];
    printf("Enter the string by which you want to filter: \n");
    scanf(" %s", &stringByWhichToFilter);
    int validCountriesCounter = filterByTheNameOfTheCountry(countriesRepository, stringByWhichToFilter, validCountriesAfterFiltering);
    if (validCountriesCounter == 0)
        printf("There are no countries that have the given string in their names.\n");
    else 
    {
        for (int index = 0; index < validCountriesCounter; index++)
            printf("#%d Country: %s, continent: %s, population: %ld \n", index+1, validCountriesAfterFiltering[index]->name, validCountriesAfterFiltering[index]->continent, validCountriesAfterFiltering[index]->population);
    }
}

void filterCountryByContinentAndSortByPopulationGreaterThanValueUi(Repository* countriesRepository)
{
    char continent[50];
    char population[50] = "";
    Country filteredCountries[50];
    int filteredCount = 0;

    printf("Enter continent name: ");
    scanf("%s", &continent);
    printf("Enter population value: ");
    scanf("%s", &population);
    long int populationINT = strtol(population, NULL, 10);
    filteredCount = filterByContinentAndGreaterPopulationThanGivenValueSortedAscending(countriesRepository, filteredCountries, continent, populationINT);

    if (filteredCount == 0) {
        printf("No countries found matching the specified criteria.\n");
        return;
    }
    else
    {
        printf("Found %d countries matching the specified criteria:\n", filteredCount);

        for (int index = 0; index < filteredCount; index++)
            printf("#%d Country: %s, continent: %s, population: %ld \n", index + 1, filteredCountries[index].name, filteredCountries[index].continent, filteredCountries[index].population);
    }
}

void undoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    int validityChecker = ServiceUndo(countriesRepository, undoRedoRepository);
    if (validityChecker == 1)
        printf("There are no more operations that can be undone!\n");
    else
        printf("Last operation was undone!\n");
}

void redoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository)
{
    int validityChecker = ServiceRedo(countriesRepository, undoRedoRepository);
    if (validityChecker == 1)
        printf("There are no more operations that can be redone!\n");
    else
        printf("Last operation was redone!\n");
}

void printMenu()
{
    printf("        MENU \n\n"
        "1. Display all countries. \n"
        "2. Add a country. \n"
        "3. Delete a country. \n"
        "4. Update a country. \n"
        "5. Display all countries whose name contains a given string. \n"
        "6. Display all countries on a given continent, whose populations are greater than a given value. \n"
        "7. Undo. \n"
        "8. Redo. \n"
        "0. Exit. \n"
    );
}

void startApplication()
{
    int optionChosenByTheUser = -1;
    Repository countriesRepository = createRepository();
    UndoRedoRepository undoRedoRepository = createUndoRedoRepository(10);
    printMenu();
    while (optionChosenByTheUser != 0) {
        printf("\nEnter your option: ");
        if (scanf("%d", &optionChosenByTheUser) != 1) 
        { optionChosenByTheUser = -1; 
            while (getchar() != '\n') {}
            printf("Invalid input. Please enter a valid option.\n");
            continue; 
        }
        //scanf("%d", &optionChosenByTheUser);
        switch (optionChosenByTheUser) {
        case 1:
            displayAllCountries(&countriesRepository);
            break;
        case 2:
            addNewCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 3:
            deleteCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 4:
            updateCountryUi(&countriesRepository, &undoRedoRepository);
            break;
        case 5:
            searchCountryByNameUi(&countriesRepository);
            break;
        case 6:
            filterCountryByContinentAndSortByPopulationGreaterThanValueUi(&countriesRepository);
            break;
        case 7:
            undoUi(&countriesRepository, &undoRedoRepository);
            break;
        case 8:
            redoUi(&countriesRepository, &undoRedoRepository);
            break;
        case 0:
            destroyDynamicArray(&countriesRepository.allCountries);
            destroyUndoRedoRepository(&undoRedoRepository);
            printf("\nMenu exited successfully.\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    }


}