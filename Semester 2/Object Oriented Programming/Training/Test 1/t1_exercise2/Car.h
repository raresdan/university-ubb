#pragma once
#include <string>

class Car
{
private:
	std::string manufacturerName;
	std::string model;
	int yearOfFabrication;
	std::string color;
public:
	Car(): manufacturerName(""), model(""), yearOfFabrication(0), color("") {}
	Car(std::string manufacturerName, std::string model, int yearOfFabrication, std::string color);

	std::string getManufacturerName() const;
	std::string getModel() const;
	int getYearOfFabrication() const;
	std::string getColor() const;

	void setManufacturerName(std::string newName);
	void setModel(std::string newModel);
	void setYearOfFabrication(int newYear);
	void setColor(std::string newColor);

	bool operator==(const Car& carToCompare);
	void operator=(const Car& carToCopy);
};

