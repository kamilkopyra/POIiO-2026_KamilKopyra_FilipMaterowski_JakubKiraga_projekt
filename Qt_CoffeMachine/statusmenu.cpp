#include "statusmenu.h"
#include "ui_statusmenu.h"
#include "CoffeMachine.h"

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
}

statusMenu::~statusMenu()
{
    delete ui;
}