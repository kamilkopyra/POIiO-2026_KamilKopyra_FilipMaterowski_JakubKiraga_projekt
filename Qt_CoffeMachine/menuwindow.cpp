#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "Tdrinks.h"

int currentCoffeId=0;

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    MenuWindow::updateCoffeName();
    MenuWindow::updateCoffeValues();
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::updateCoffeName(){
    //int menuSize=drinks.size();
    Tdrinks* drink = drinks[currentCoffeId];

    if (drink == nullptr || currentCoffeId==-1){
        currentCoffeId=0;
        drink = drinks[currentCoffeId];
    }
    ui->Coffe_name->setText(QString::fromStdString(drink->getName()));
}

void MenuWindow::updateCoffeValues(){
    //MenuWindow::updateCoffeName();
    Tdrinks* drink = drinks[currentCoffeId];

    ui->Coffe_water->setText(QString::number(drink->getVolumeOfWater(),'f',1) + "ml");
    ui->Coffe_milk->setText(QString::number(drink->getVolumeOfMilk(),'f',1) + "ml");
    ui->Coffe_power->setText(QString::number(drink->getPowerOfCoffe()));

}

void MenuWindow::on_next_button_clicked()
{
    currentCoffeId++;
    updateCoffeName();
}


void MenuWindow::on_previous_button_clicked()
{
    currentCoffeId--;
    updateCoffeName();
}

