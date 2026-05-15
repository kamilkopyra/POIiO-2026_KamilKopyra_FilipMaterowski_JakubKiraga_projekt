#include <QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // ← musi być przed jakimkolwiek widgetem

    MainWindow window;
    window.show();

    return app.exec(); // ← pętla zdarzeń Qt
}