#include "CoffeMachine.h"

CoffeMachine::CoffeMachine() {
}
void CoffeMachine::updateMachineStatus() {
	// Implementation to return the current status of the machine


	hasMilk = milk.isEnough();
	hasWater = water.isEnough();
	hasBeans = beans.isEnough();

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

void CoffeMachine::cleanMachine() {
	isClean = true;
	history.push_back("Machine cleaned");
}