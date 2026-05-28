#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    CoffeMachine machine;
    machine.initializeMachine();
    machine.printStatus();
 
    std::cin.get();
    return 0;
}