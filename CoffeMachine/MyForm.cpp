#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    //Application::EnableVisualStyles();
    //Application::SetCompatibleTextRenderingDefault(false);
    //MyForm form;
    //Application::Run(% form);

	std::cout << "Terminalowa wersja testowa\n\n";

	CoffeMachine machine;
	machine.initializeMachine();
	machine.printStatus();

	//machine.makeCoffee(Tdrinks::drinks[2]);  mo¿na tak ale trochê s³abe dlatego doda³em szukanie po nazwie



	machine.makeCoffee("Espresso");
	machine.printStatus();

	machine.makeCoffee("Latte");
	machine.printStatus();


	// przyk³ad obs³ugi wyj¹tku
	machine.makeCoffee("CocaCola");


	// Dodawanie w³asnego napoju
	Tdrinks::addDrink("Flat White", 150, 50, 3);
	machine.makeCoffee("Flat White");
	machine.printStatus();

	for (int i = 0; i < 3; i++) {
		machine.makeCoffee("Latte");
		machine.printStatus();
	}

	// uzupe³nianie sk³adników
	machine.addWater(500);
	machine.addBeans(200);
	machine.addMilk(300);
	machine.printStatus();

	// Obsluga wyjatku -> dodanie zbyt duzej ilosci wody
	machine.addWater(3000); // poziom wody jest uzupe³niany do maksymalnej pojemnoœci
	machine.printStatus();


	// czyszczenie maszyny
	machine.cleanMachine();
	machine.printStatus();



	machine.printHistory();





	std::cout << "\n\n\n";
	// Prezentacja logiki klasy Tdrinks
	Tdrinks drink("ekspresso", 30, 0, 3);

	std::cout << "Funkcja Tdrinks::show()" << std::endl;
	drink.show();
	drink.editPower(5);
	drink.editVolume(50);
	drink.editVolumeOfMilk(10);
	std::cout << "Po edycji:" << std::endl;
	drink.show();

	std::cout << "==== Wszystkie napoje ====" << std::endl;
	Tdrinks::showAll();
	std::cout << "==== Usuniêcie napoju \"ekspresso\" ====" << std::endl;
	Tdrinks::removeDrink("ekspresso"); // usuniêcie napoju z listy
	std::cout << "==== Wszystkie napoje ====" << std::endl;
	Tdrinks::showAll();

	

	std::cin.get();
    return 0;
}