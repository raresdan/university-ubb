#pragma once
#include "Controller.h"

class Ui
{
private:
	Controller controller;
public:
	Ui(Controller controller) : controller{ controller } {};
	void addDepartment();
	void showAllDepartments();
	void showAllEfficientDepartments();
	void writeToFile();
	void printMenu();
	void startApplication();
};

