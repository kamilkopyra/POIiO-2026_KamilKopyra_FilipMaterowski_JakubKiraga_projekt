#pragma once
#include <string>
#include "Ingredient.h"
#include "Tdrinks.h"

class CoffeMachine 
{
public:

	int getMachineStatus();
	int getMachineStatistics();
	int diagnoseMachine();
	int repairMachine();
	
	bool makeCoffee(std::string type);
	void initializeMachine();
	void addWater(int amount);
	void addBeans(int amount);
	
	void cleanMachine();

private:
	Ingredient water;
	Ingredient beans;
	Ingredient milk;

	int cupsServed;
	bool isOperational;
	bool isClean;
	bool hasWater;
	bool hasBeans;
	bool hasMilk;


	int maxWaterCapacity = 2000; // in milliliters
	int maxBeansCapacity = 500; // in grams
	int maxMilkCapacity = 1000; // in milliliters

	bool checkIngredients(std::string type);

};