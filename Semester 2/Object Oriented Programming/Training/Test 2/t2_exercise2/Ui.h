#pragma once
#include "Person.h"

class Ui
{
private:
	Person person;
public:
	Ui(Person initialPersona) : person{ initialPersona } {};

	void addAnalysis();
	void displayAllAnalysis();
	void checkIllness();
	void saveToFile();
	void printMenu();
	void startApplication();

};

