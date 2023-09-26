#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "country.h"

Country createNewCountry(char nameOfTheCountry[], char continentOfTheCountry[], long int populationOfTheCountry)
{
	Country newCountry;

	newCountry.name = malloc((strlen(nameOfTheCountry) + 1) * sizeof(char));
	if (newCountry.name == NULL)
		return newCountry;
	strcpy(newCountry.name, nameOfTheCountry);

	newCountry.continent = malloc((strlen(continentOfTheCountry) + 1) * sizeof(char));
	if (newCountry.continent == NULL)
	{
		free(newCountry.name);
		return newCountry;
	}
	strcpy(newCountry.continent, continentOfTheCountry);

	newCountry.population = populationOfTheCountry;

	return newCountry;
}

char* getCountryName(Country* country)
{
	return country->name;
}

char* getCountryContinent(Country* country)
{
	return country->continent;
}

long int getCountryPopulation(Country* country)
{
	return country->population;
}

void turnCountryToString(Country country, char* countryString[])
{
	sprintf(countryString, "The country %s is from %s and has a population of %ld citizens.", country.name, country.continent, country.population);
}

void destroyCountry(Country countryToDestroy)
{
	free(countryToDestroy.name);
	free(countryToDestroy.continent);
}
