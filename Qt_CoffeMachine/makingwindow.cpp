#include "makingwindow.h"
#include "ui_makingwindow.h"
#include "mainwindow.h"

makingwindow::makingwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::makingwindow)
{
    ui->setupUi(this);
    ui->Satus_label->setText("Przygotowuje twój napój...");

    QTimer::singleShot(5000, this, [=]() {
        ui->Satus_label->setText("Twój napój jest gotowy!");
    });

    QTimer::singleShot(10000,this, [=](){
        if (!mainWindow) {
            mainWindow = new MainWindow(nullptr);        // tworzymy tylko raz

            connect(mainWindow, &MainWindow::destroyed,
                    this,       &makingwindow::show);
        }
        this->hide();           // chowamy okno startowe
        mainWindow->show();
    });

}

makingwindow::~makingwindow()
{
    delete ui;
}
