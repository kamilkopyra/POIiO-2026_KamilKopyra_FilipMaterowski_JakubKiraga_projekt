#include "CoffeMachine.h"

int CoffeMachine::getMachineStatus() {
	// Implementation to return the current status of the machine
	
	
	bool milkStatus = checkIngredients("Milk");
	bool waterStatus = checkIngredients("Water");
	bool beansStatus = checkIngredients("Beans");
	
	if(milkStatus && waterStatus && beansStatus) {
		return 1; // wszystkie składniki są dostępne
	}
	else if (!waterStatus) {return 2;} // brak wody
	else if (!beansStatus) {return 3;} // brak ziaren kawy
	else if (!milkStatus) {return 4;} // brak mleka
}


bool CoffeMachine::checkIngredients(std::string type)
{
	return true;
}