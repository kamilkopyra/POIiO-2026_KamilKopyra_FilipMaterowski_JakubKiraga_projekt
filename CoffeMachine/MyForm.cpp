#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    //Application::EnableVisualStyles();
    //Application::SetCompatibleTextRenderingDefault(false);
    //MyForm form;
    //Application::Run(% form);
    CoffeMachine kawiarka2;
    kawiarka2.initializeMachine();
    kawiarka2.makeCoffee(drinks[0]);
    //kawiarka2.makeCoffee(drinks[1]);
    //kawiarka2.makeCoffee(drinks[3]);
    std::cin.get();
    return 0;
}