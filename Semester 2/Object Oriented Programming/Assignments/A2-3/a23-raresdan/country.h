#pragma once

typedef struct
{
	char* name;
	char* continent;
	long int population;
}Country;

Country createNewCountry(char nameOfTheCountry[], char continentOfTheCountry[], long int populationOfTheCountry);
char* getCountryName(Country* country);
char* getCountryContinent(Country* country);
long int getCountryPopulation(Country* country);
void turnCountryToString(Country country, char* countryString[]);
void destroyCountry(Country countryToDestroy);