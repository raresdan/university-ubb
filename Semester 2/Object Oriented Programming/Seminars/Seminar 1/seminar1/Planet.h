#pragma once

typedef struct
{
	//char name[100];
	char* name;
	char* type;
	double distanceFromEarth;
}Planet;

Planet createPlanet(char* name, char* type, double dist);
void destroyPlanet(Planet);
char* getName(Planet p);
