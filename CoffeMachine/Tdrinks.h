#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

// Czym jest kawa?
/* 
Historia kawy rozpoczęła się w Etiopii (rejon Kaffa), gdzie według legendy pobudzające właściwości owoców kawowca odkrył pasterz,
obserwując ożywione kozy. Stamtąd trafiła do Jemenu (XV/XVI w.), zyskując popularność w świecie arabskim, a w XVII w. dotarła do Europy.
Od tego czasu nasze życie nie wyglądało już tak samo...
*/

class Tdrinks
{
	
	std::string name;
	float volume;
	float volumeOfMilk;
	int power;  // Power = (1,2,3,4,5) default = 3

	
public:
	
	static std::vector<Tdrinks> drinks;
	Tdrinks(std::string name, float volume, float volumeofMilk, int power);
	std::string getName();
	int Tdrinks::getDrinkId(std::string name);
	int getPowerOfCoffe();
	bool hasMilk();
	float getVolume();
	float getVolumeOfMilk();
	void show();
	int getAmountOfCoffee();
	float Tdrinks::getVolumeOfWater();

	void editVolume(float newVolume);
	void editVolumeOfMilk(float newVolumeOfMilk);
	void editPower(int newPower);

	static void addDrink(std::string name, float volume, float volumeOfMilk, int power);
	static void removeDrink(std::string name);

	static Tdrinks* getDrinkByName(std::string name);

};
