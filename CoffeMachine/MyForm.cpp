#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    CoffeMachine machine;
    machine.initializeMachine();
    machine.printStatus();


	//machine.makeCoffee("Espresso");
	//machine.makeCoffee("Cappuccino");
	//machine.makeCoffee("Latte");
    machine.printStatus();

    machine.resetMachine();
    machine.printStatus();
    std::cin.get();
    return 0;
}