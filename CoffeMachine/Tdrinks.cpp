#include <iostream>
#include <string>
#include <vector>
#include "Tdrinks.h"

// Constructor to initialize the name and volume of the drink
Tdrinks::Tdrinks(std::string name, float volume, float volumeofMilk, int power)
{
	this->name = name;
	this->volume = volume;
	this->volumeOfMilk = volumeofMilk;
	this->power = power;
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
	std::cout << "Nazwa: " << getName() << "\n";
	std::cout << "Ilosc kawy i mleka:  " << getVolume() << " ml\n";
	std::cout << "Ilosc mleka:  " << getVolumeOfMilk() << " ml\n";
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
int Tdrinks::getAmountOfCoffee() {
	int AmountPerVolume;
	switch (power) {
	case 1:
		AmountPerVolume = 8/250;
		break;
	case 2:
		AmountPerVolume = 10/250;
		break;
	case 3:
		AmountPerVolume = 14/250;
		break;
	case 4:
		AmountPerVolume = 16/250;
		break;
	case 5:
		AmountPerVolume = 18/250;
		break;
	default:
		std::cout << "Invalid power level. Setting to default (3).\n";
		power = 3;
		AmountPerVolume = 14 / 250;
		break;

		return AmountPerVolume * volume;
	}
}

// List of drinks with their names and volumes
std::vector<Tdrinks> Tdrinks::drinks = {
	Tdrinks("Black Coffee", 250, 0, 4),
	Tdrinks("Latte", 200, 100, 2),
	Tdrinks("Cappuccino", 100, 250, 3),
	Tdrinks("Espresso", 100, 0, 5)
};