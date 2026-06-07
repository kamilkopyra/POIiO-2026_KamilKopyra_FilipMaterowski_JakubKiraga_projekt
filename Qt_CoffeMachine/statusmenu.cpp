#include "statusmenu.h"
#include "ui_statusmenu.h"
#include "CoffeMachine.h"
#include "addingredientsmenu.h"
#include <QDebug>
#include <QTimer>

statusMenu::statusMenu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::statusMenu)
{
    ui->setupUi(this);

    ui->waterLabel->setText("Woda: " + QString::number(machine.getWaterAmount()) + " ml");
    ui->milkLabel->setText("Mleko: " + QString::number(machine.getMilkAmount()) + " ml");
    ui->beanLabel->setText("Ziarna: " + QString::number(machine.getBeansAmount()) + " g");
    ui->cleanLabel->setText("Czystość: " + QString(machine.getIsClean() ? "✓ Czysta" : "✗ Wymaga czyszczenia"));
    ui->operationalLabel->setText("Status: " + QString(machine.getIsOperational() ? "✓ Sprawna" : "✗ Niesprawna"));
    ui->numberLabel->setText("Kaw od czyszczenia: " + QString::number(machine.getCupsSinceLastCleaning()));

    QTimer *refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [=]() {
        ui->waterLabel->setText("Woda: " + QString::number(machine.getWaterAmount()) + " ml");
        ui->milkLabel->setText("Mleko: " + QString::number(machine.getMilkAmount()) + " ml");
        ui->beanLabel->setText("Ziarna: " + QString::number(machine.getBeansAmount()) + " g");
        ui->cleanLabel->setText("Czystość: " + QString(machine.getIsClean() ? "✓ Czysta" : "✗ Wymaga czyszczenia"));
        ui->operationalLabel->setText("Status: " + QString(machine.getIsOperational() ? "✓ Sprawna" : "✗ Niesprawna"));
        ui->numberLabel->setText("Kaw od czyszczenia: " + QString::number(machine.getCupsSinceLastCleaning()));
        ui->cupsServedLabel->setText("Podanych kaw łącznie: " + QString::number(machine.getCupsServed()));


    });
    refreshTimer->start(1000);

    // AddIngredientsMenu *ind_menu(nullptr);
    // connect(ind_menu, &AddIngredientsMenu::Water_added, this, &statusMenu::Water_val_changed);
    // connect(ind_menu, &AddIngredientsMenu::Milk_added, this, &statusMenu::Milk_val_changed);
    // connect(ind_menu, &AddIngredientsMenu::Beans_added, this, &statusMenu::Beans_val_changed);
}

statusMenu::~statusMenu()
{
    delete ui;
}

void statusMenu::Water_val_changed()
{
    ui->waterLabel->setText("Woda: " + QString::number(machine.getWaterAmount()) + " ml");
    std::cout << machine.getWaterAmount() << "\n";
}

void statusMenu::Milk_val_changed()
{
    ui->milkLabel->setText("Mleko: " + QString::number(machine.getMilkAmount()) + " ml");
}

void statusMenu::Beans_val_changed()
{
     ui->beanLabel->setText("Ziarna: " + QString::number(machine.getBeansAmount()) + " g");
}