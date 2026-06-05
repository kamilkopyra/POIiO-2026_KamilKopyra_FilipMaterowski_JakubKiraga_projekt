#include "addingredientsmenu.h"
#include "ui_addingredientsmenu.h"
#include "CoffeMachine.h"

AddIngredientsMenu::AddIngredientsMenu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::AddIngredientsMenu)
{
    ui->setupUi(this);

    ui->waterSlider->setRange(0, 2000);
    ui->milkSlider->setRange(0, machine.getMaxMilk());
    ui->beanSlider->setRange(0, machine.getMaxBeans());

    connect(ui->waterSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->waterValueLabel->setText(QString::number(value) + " ml");
    });
    connect(ui->milkSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->milkValueLabel->setText(QString::number(value) + " ml");
    });
    connect(ui->beanSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->beansValueLabel->setText(QString::number(value) + " g");
    });
}

AddIngredientsMenu::~AddIngredientsMenu()
{
    delete ui;
}

void AddIngredientsMenu::on_addButton_clicked()
{
    machine.addWater(ui->waterSlider->value());
    machine.addMilk(ui->milkSlider->value());
    machine.addBeans(ui->beanSlider->value());

    // ui->waterSlider->setValue(0);
    // ui->milkSlider->setValue(0);
    // ui->beanSlider->setValue(0);
}