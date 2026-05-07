#include <iostream>
#include <string>
#include <vector>
#include "Tdrinks.h"

// Constructor to initialize the name and volume of the drink
Tdrinks::Tdrinks(std::string name, float volume, float volumeofMilk)
{
	this->name = name;
	this->volume = volume;
	this->volumeOfMilk = volumeofMilk;
}

// Returns the name of the drink
std::string Tdrinks::getName()
{
	return name;
}
// Returns the volume of the drink
float Tdrinks::getVolume()
{
	return volume + volumeOfMilk;
}
float Tdrinks::getVolumeOfMilk()
{
	return volumeOfMilk;
}

void Tdrinks::show() 
{
	std::cout << "Nazwa" << getName() << "\n";
	std::cout << "Ilość kawy i mleka" << getVolume() << "\n";
	std::cout << "Ilość mleka" << getVolumeOfMilk() << "\n";
}

void Tdrinks::editVolume(float newVolume) {
	volume = newVolume;
}
void Tdrinks::editVolumeOfMilk(float newVolumeOfMilk) {
	volumeOfMilk = newVolumeOfMilk;
}
void Tdrinks::editPower(int newPower) {
	power = newPower;
}

void Tdrinks::addDrink(Tdrinks drink) {
	drinks.push_back(drink);
}

void Tdrinks::removeDrink(std::string name) {
	for (int i = 0; i < drinks.size(); i++) {
		if (drinks[i].getName() == name) {
			drinks.erase(drinks.begin() + i);
			return;
		}
	}
}

// List of drinks with their names and volumes
std::vector<Tdrinks> Tdrinks::drinks = {
	Tdrinks("Black Coffee", 250, 0),
	Tdrinks("Latte", 200, 100),
	Tdrinks("Cappuccino", 100, 250),
	Tdrinks("Espresso", 100, 0)
};