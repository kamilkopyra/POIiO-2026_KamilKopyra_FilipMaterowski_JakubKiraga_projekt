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
}

void MainWindow::onSubtractClicked() {
}