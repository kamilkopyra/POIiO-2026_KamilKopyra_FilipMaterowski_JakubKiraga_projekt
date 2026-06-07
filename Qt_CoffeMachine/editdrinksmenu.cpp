#include "editdrinksmenu.h"
#include "ui_editdrinksmenu.h"
#include "CoffeMachine.h"
#include "Tdrinks.h"
#include <QSqlQuery>
#include <QSqlError>

EditDrinksMenu::EditDrinksMenu(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::EditDrinksMenu)
{
    ui->setupUi(this);

    ui->waterSlider->setRange(0, 500);
    ui->milkSlider->setRange(0, 500);
    ui->powerSlider->setRange(1, 5);

    // Załaduj napoje do listy
    for (Tdrinks* drink : drinks) {
        ui->drinksList->addItem(QString::fromStdString(drink->getName()));
    }

    connect(ui->waterSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->waterValueLabel->setText(QString::number(value) + " ml");
    });
    connect(ui->milkSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->milkValueLabel->setText(QString::number(value) + " ml");
    });
    connect(ui->powerSlider, &QSlider::valueChanged, this, [=](int value) {
        ui->powerValueLabel->setText(QString::number(value));
    });
}

EditDrinksMenu::~EditDrinksMenu()
{
    delete ui;
}

void EditDrinksMenu::on_addDrinkButton_clicked()
{
    QString name = ui->nameInput->text();
    if (name.isEmpty()) return;

    float water = ui->waterSlider->value();
    float milk  = ui->milkSlider->value();
    int power   = ui->powerSlider->value();

    Tdrinks::addDrink(name.toStdString(), water, milk, power);
    ui->drinksList->addItem(name);

    ui->nameInput->clear();
    ui->waterSlider->setValue(0);
    ui->milkSlider->setValue(0);
    ui->powerSlider->setValue(1);
}

void EditDrinksMenu::on_removeDrinkButton_clicked()
{
    int index = ui->drinksList->currentIndex();
    if (index < 0) return;

    QString name = ui->drinksList->currentText();
    Tdrinks::removeDrink(name.toStdString());
    ui->drinksList->removeItem(index);
}

void EditDrinksMenu::on_modifyDrinkButton_clicked()
{
    QString name = ui->drinksList->currentText();
    qDebug() << "Modyfikuję:" << name;

    Tdrinks* drink = Tdrinks::getDrinkByName(name.toStdString());
    qDebug() << "Drink found:" << (drink != nullptr);

    if (!drink) return;

    drink->editVolume(ui->waterSlider->value());
    drink->editVolumeOfMilk(ui->milkSlider->value());
    drink->editPower(ui->powerSlider->value());
    QSqlQuery query;
    query.prepare("UPDATE drinks SET volume = :volume, volumeofMilk = :milk, power = :power WHERE name = :name");
    query.bindValue(":volume", ui->waterSlider->value());
    query.bindValue(":milk", ui->milkSlider->value());
    query.bindValue(":power", ui->powerSlider->value());
    query.bindValue(":name", name);
    qDebug() << "Query result:" << query.exec();
    qDebug() << "Query error:" << query.lastError().text();

    emit drinksModified();

    // Dopóki nie kliknie się czegoś w oknie menuWindow to zmiany są niewidoczne jeśli chodzi o modyfikacje istniejącego napoju
    // Za dużo roboty, jeśli komuś się chce to może tu wrócić, zapraszam
}