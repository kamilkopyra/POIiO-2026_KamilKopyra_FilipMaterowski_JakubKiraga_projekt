#include "MainWindow.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]

int main(array<String^>^ args) {
    std::vector<std::string> listaWszystkichNapojow;

    LoadDrinksToVector(listaWszystkichNapojow);


    int iloscNapojow = listaWszystkichNapojow.size();

    if (iloscNapojow > 0)
    {
        std::string pierwszy = listaWszystkichNapojow[0];
        Console::WriteLine("Pierwszy napoj w bazie: " + gcnew String(pierwszy.c_str()));
    }
    std::cin.get();
    return 0;
}