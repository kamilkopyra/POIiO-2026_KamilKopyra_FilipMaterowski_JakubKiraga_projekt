#include "CoffeMachine.h"
#include "Tdrinks.h"
#include <iostream>
#include <string>
#include <vector>
#include "Ingredient.h"

int main() {
	//CoffeMachine machine;
	Tdrinks drink("Ekspresso", 30, 0);

	std::cout << "Funkcja Tdrinks::show()" << std::endl;
	drink.show();
	drink.editPower(5);
	drink.editVolume(50);
	drink.editVolumeOfMilk(10);
	std::cout << "Po edycji:" << std::endl;
	drink.show();

	return 0;
}