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
	return water.getAmount() >= drink.getVolumeOfWater() && milk.getCapacity() >= drink.getVolumeOfMilk() && beans.getCapacity() >= drink.getAmountOfCoffee();
}

void CoffeMachine::checkIngredientsForFeedback(Tdrinks drink)
{
	if (water.getAmount() < drink.getVolumeOfWater())
	{
		std::cout << "Add water\n";
	}
	else if (milk.getAmount() < drink.getVolumeOfMilk())
	{
		std::cout << "Add milk\n";
	}
	else if(beans.getAmount() < drink.getAmountOfCoffee())
	{
		std::cout << "Add beans\n";
	}
	else
	{
		std::cout << "Error: ckeckIngredientsForFeedback()";
	}
}

void CoffeMachine::makeCoffee(Tdrinks drink)
{
	bool enoughIngredients = checkIngredientsFor(drink);

	if (enoughIngredients)
	{
		water.consume(drink.getVolumeOfWater());
		milk.consume(drink.getVolumeOfMilk());
		beans.consume(drink.getAmountOfCoffee());

		std::cout << drink.getName() <<" was made\n";
		std::cout << "Used " << drink.getVolumeOfWater() << "ml of water, " << drink.getVolumeOfMilk() << "ml of milk, and " << drink.getAmountOfCoffee() << "g of coffee\n";
		std::cout << "Remaining: " << water.getAmount() << "ml of water, " << milk.getAmount() << "ml of milk, and " << beans.getAmount() << "g of coffee\n";
	}
	else
	{
		checkIngredientsForFeedback(drink);
	}


}
