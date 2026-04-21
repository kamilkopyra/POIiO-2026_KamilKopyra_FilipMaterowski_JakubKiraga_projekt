#pragma once
#include <iostream>
#include <string>

class Tdrinks
{
	std::string name;
	int volume;
	int volumeOfMilk;
public:
	Tdrinks(std::string name, int volume, int volumeofMilk);
	std::string getName();
	int getVolume();
	bool hasMilk();
	int getVolumeOfMilk();
};
