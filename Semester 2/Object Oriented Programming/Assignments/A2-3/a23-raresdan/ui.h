#pragma once

#include "service.h"

void displayAllCountries(Repository* countriesRepository);
void addNewCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
void deleteCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
void updateCountryUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
void searchCountryByNameUi(Repository* countriesRepository);
void filterCountryByContinentAndSortByPopulationGreaterThanValueUi(Repository* countriesRepository);
void undoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
void redoUi(Repository* countriesRepository, UndoRedoRepository* undoRedoRepository);
void printMenu();
void startApplication();