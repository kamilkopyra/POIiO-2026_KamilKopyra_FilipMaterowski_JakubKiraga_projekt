#pragma once
#include <iostream>
#include <string>
#include <vector>

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
	
	Tdrinks(std::string name, float volume, float volumeofMilk, int power);
	std::string getName();
	int getDrinkId(std::string name);
	int getPowerOfCoffe();
	bool hasMilk();
	float getVolume();
	float getVolumeOfMilk();
	float Tdrinks::getVolumeOfWater();
	void show();
	double getAmountOfCoffee();

	void editVolume(float newVolume);
	void editVolumeOfMilk(float newVolumeOfMilk);
	void editPower(int newPower);

	static void addDrink(Tdrinks drink);
	static void removeDrink(std::string name);

};

extern std::vector<Tdrinks> drinks;
