#include "mainwindow.h"
#include "menuwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!menuWindow) {
        menuWindow = new MenuWindow(nullptr);        // tworzymy tylko raz

        connect(menuWindow, &MenuWindow::destroyed,
                this,       &MainWindow::show);
    }
    this->hide();           // chowamy okno startowe
    menuWindow->show();     // pokazujemy menu
}

