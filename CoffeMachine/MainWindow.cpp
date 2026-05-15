#include "MainWindow.h"
#include "ui_MainWindow.h"  // ← generowany automatycznie przez AUTOUIC
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); // ← tworzy wszystkie widgety z pliku .ui

    // Połączenie sygnałów (kliknięcie) ze slotami (Twoje metody)
    connect(ui->btnAdd, &QPushButton::clicked,
        this, &MainWindow::onAddClicked);

    connect(ui->btnSub, &QPushButton::clicked,
        this, &MainWindow::onSubtractClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

// -------------------------------------------------------
// Jak czytać dane z GUI, wywołać logikę, pokazać wynik
// -------------------------------------------------------

void MainWindow::onAddClicked() {
    // 1. Pobierz dane z pól tekstowych
    bool okA, okB;
    double a = ui->inputA->text().toDouble(&okA);
    double b = ui->inputB->text().toDouble(&okB);

    // 2. Walidacja wejścia
    if (!okA || !okB) {
        QMessageBox::warning(this, "Błąd", "Podaj liczby w obu polach.");
        return;
    }

    // 3. Wywołaj swoją logikę — bez żadnych zmian w Calculator
    double result = calculator.add(a, b);

    // 4. Wyświetl wynik w GUI
    ui->labelResult->setText(
        QString("Wynik: %1  (%2)")
        .arg(result)
        .arg(QString::fromStdString(calculator.getLastOperationDescription()))
    );
}

void MainWindow::onSubtractClicked() {
    bool okA, okB;
    double a = ui->inputA->text().toDouble(&okA);
    double b = ui->inputB->text().toDouble(&okB);

    if (!okA || !okB) {
        QMessageBox::warning(this, "Błąd", "Podaj liczby w obu polach.");
        return;
    }

    double result = calculator.subtract(a, b);

    ui->labelResult->setText(
        QString("Wynik: %1  (%2)")
        .arg(result)
        .arg(QString::fromStdString(calculator.getLastOperationDescription()))
    );
}