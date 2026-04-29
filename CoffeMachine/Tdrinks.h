#pragma once
#include <iostream>
#include <string>

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
	Tdrinks(std::string name, int volume, int volumeofMilk, int power);
	std::string getName();
	int getPowerOfCoffe();
	bool hasMilk();
	int getVolume();
	int getVolumeOfMilk();
};
