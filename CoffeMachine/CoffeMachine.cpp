#include "CoffeMachine.h"

CoffeMachine::CoffeMachine() {
}
void CoffeMachine::updateMachineStatus() {
	// Implementation to return the current status of the machine


	hasMilk = milk.isEnough();
	hasWater = water.isEnough();
	hasBeans = beans.isEnough();
	
	if (!hasMilk) std::cout << "Dolej mleka\n";
	else if (!hasWater) std::cout << "Dolej wode\n";
	else if (!hasBeans) std::cout << "Dosyp ziarna\n";
	else std::cout << "Wystarczające składniki\n";
}


void CoffeMachine::initializeMachine() 
{
	water = Ingredient("Water", maxWaterCapacity/2, maxWaterCapacity, waterMinThreshold);
	beans = Ingredient("Beans", maxBeansCapacity/2, maxBeansCapacity, beansMinThreshold);
	milk = Ingredient("Milk", maxMilkCapacity/2, maxMilkCapacity, milkMinThreshold);

	isOperational = true;
	isClean = true;
	cupsServed = 0;
}

void CoffeMachine::cleanMachine() 
{
	isClean = true;
	history.push_back("Machine cleaned");
}

void CoffeMachine::addWater(int amount) 
{
	water.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "ml of water");
}

void CoffeMachine::addBeans(int amount) 
{
	beans.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "g of beans");
}

void CoffeMachine::addMilk(int amount) 
{
	milk.refill(amount);
	updateMachineStatus();
	history.push_back("Added " + std::to_string(amount) + "ml of milk");
}

void CoffeMachine::descaling() 
{
	isOperational = true;
	history.push_back("Machine descaled");
}

bool CoffeMachine::checkIngredientsFor(Tdrinks drink) 
{
	return water.getCapacity() >= drink.getVolume() && milk.getCapacity() >= drink.getVolumeOfMilk() && beans.getCapacity() >= drink.getAmountOfCoffee();
}

