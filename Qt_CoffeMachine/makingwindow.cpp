#include "makingwindow.h"
#include "ui_makingwindow.h"
#include "mainwindow.h"
#include "cupwidget.h"

makingwindow::makingwindow(Tdrinks drink, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::makingwindow)
    , currentDrink(drink)
{
    ui->setupUi(this);
    ui->Satus_label->setText("Przygotowuje twój napój...");

    CupWidget *cup = new CupWidget(this);
    cup->setGeometry(width()/2 - 100, height()/2 - 100, 200, 200);

    float milkRatio = currentDrink.getVolumeOfMilk() / currentDrink.getVolume();
    qDebug() << "milkRatio:" << milkRatio;
    cup->setDrinkColor(milkRatio);
    cup->startFilling();

    QTimer::singleShot(5000, this, [=]() {
        ui->Satus_label->setText("Twój napój jest gotowy!");
    });
    QTimer::singleShot(10000, this, [=]() {
        if (!mainWindow) {
            mainWindow = new MainWindow(nullptr);
            connect(mainWindow, &MainWindow::destroyed,
                    this, &makingwindow::show);
        }
        this->hide();
        mainWindow->show();
    });
}

makingwindow::~makingwindow()
{
    delete ui;
}