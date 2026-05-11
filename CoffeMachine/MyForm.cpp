#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

//[STAThreadAttribute]

int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    MyForm form;
    Application::Run(% form);
    Tdrinks drink("ekspresso", 100, 100,5);
    drink.show();
    std::cin.get();
    return 0;
}