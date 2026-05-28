#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    CoffeMachine machine;
    machine.initializeMachine();
    machine.resetMachine();
    machine.printStatus();
    machine.printHistory();
    std::cin.get();
    return 0;
}