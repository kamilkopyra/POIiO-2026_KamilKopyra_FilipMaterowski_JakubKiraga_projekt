#pragma once
#include <string>
#include "Ingredient.h"
#include "Tdrinks.h"
#include <vector>

class CoffeMachine 
{
public:
	CoffeMachine();
	~CoffeMachine() = default;

	void updateMachineStatus();

	int getMachineStatistics();
	int diagnoseMachine();
	int repairMachine();
	
	bool makeCoffee(std::string drinkName);
	void initializeMachine();
	void addWater(int amount);
	void addBeans(int amount);
	void addMilk(int amount);
	
	void descaling();
	void cleanMachine();
	std::vector<std::string> getHistory();


	void printStatus();
	void printHistory();
private:
	Ingredient water;
	Ingredient beans;
	Ingredient milk;

	int cupsServed;
	int cupsSinceLastCleaning;
	bool isOperational;
	bool isClean;
	bool hasWater = false;
	bool hasBeans = false;
	bool hasMilk = false;


	int maxWaterCapacity = 2000; // in milliliters
	int maxBeansCapacity = 500; // in grams
	int maxMilkCapacity = 1000; // in milliliters

	int waterMinThreshold = 200; // in milliliters
	int beansMinThreshold = 50; // in grams
	int milkMinThreshold = 100; // in milliliters

	bool checkIngredientsFor(Tdrinks drink);
	std::vector<std::string> history;

};