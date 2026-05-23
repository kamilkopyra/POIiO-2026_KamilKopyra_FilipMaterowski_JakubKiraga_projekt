#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    CoffeMachine machine;
    machine.initializeMachine();
    machine.printStatus();

    //machine.makeCoffee(Tdrinks::drinks[2]);  //mo¿na tak ale trochê s³abe dlatego doda³em szukanie po nazwie

    machine.makeCoffee("Espresso");
    machine.printStatus();

    machine.makeCoffee("Latte");
    machine.printStatus();
 
    Tdrinks::addDrink("kawa_test", 250, 0, 5);
    std::cin.get();
    return 0;
}