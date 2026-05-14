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
	else std::cout << "Wystarczajace skladniki\n";
}


void CoffeMachine::initializeMachine() 
{
	water = Ingredient("Water", maxWaterCapacity/2, maxWaterCapacity, waterMinThreshold);
	beans = Ingredient("Beans", maxBeansCapacity/2, maxBeansCapacity, beansMinThreshold);
	milk = Ingredient("Milk", maxMilkCapacity/2, maxMilkCapacity, milkMinThreshold);

	isOperational = true;
	isClean = true;
	cupsServed = 0;
	cupsSinceLastCleaning = 0;
}

void CoffeMachine::cleanMachine() 
{
	isClean = true;
	cupsSinceLastCleaning = 0;
	std::cout << "Maszyna zostala wyczyszczona\n";
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
	return water.getAmount() >= drink.getVolume()
		&& milk.getAmount() >= drink.getVolumeOfMilk()
		&& beans.getAmount() >= drink.getAmountOfCoffee();
}


void CoffeMachine::printStatus()
{
	std::cout << "Machine Status:\n";
	std::cout << "Water: " << water.getAmount() << "ml\n";
	std::cout << "Beans: " << beans.getAmount() << "g\n";
	std::cout << "Milk: " << milk.getAmount() << "ml\n";
	std::cout << "Cups Served: " << cupsServed << "\n";
	std::cout << "Operational: " << (isOperational ? "Yes" : "No") << "\n";
	std::cout << "Cups Since Last Cleaning: " << cupsSinceLastCleaning << "\n";
	std::cout << "Clean: " << (isClean ? "Yes" : "No") << "\n";
	std::cout << "\n\n\n";
}

bool CoffeMachine::makeCoffee(std::string drinkName) {
	Tdrinks* drink = Tdrinks::getDrinkByName(drinkName);  // wskaźnik
	if (drink == nullptr) {
		std::cout << "Nie ma takiego napoju\n\n";
		return false;
	}

	if (!checkIngredientsFor(*drink)) {  
		updateMachineStatus();
		std::cout << "Kawa nie zostala przygotowana z powodu niewystarczajacych skladnikow\n\n";
		return false;
	}

	if (cupsSinceLastCleaning >= 10) {
		isClean = false;
		std::cout << "Maszyna wymaga czyszczenia po " << cupsSinceLastCleaning << " kawach!\n";
	}

	drink->show();  
	water.consume(drink->getVolumeOfWater());  
	beans.consume(drink->getAmountOfCoffee());  
	milk.consume(drink->getVolumeOfMilk());     

	cupsServed++;
	cupsSinceLastCleaning++;

	history.push_back("Made " + drink->getName() + " (Cup #" + std::to_string(cupsServed) + ")");  

	updateMachineStatus();

	return true;
}

void CoffeMachine::printHistory()
{
	std::cout << "\n=== HISTORIA MASZYNY ===\n";

	if (history.empty()) {
		std::cout << "Brak historii.\n";
		return;
	}

	for (int i = 0; i < history.size(); i++) {
		std::cout << i + 1 << ". " << history[i] << "\n";
	}
	std::cout << "========================\n";
}

