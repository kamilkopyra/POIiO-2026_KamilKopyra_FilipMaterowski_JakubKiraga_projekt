#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "Tdrinks.h"

int currentCoffeId=0;
int checkBoxId=0;

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
    this->installEventFilter(this);
    MenuWindow::updateCoffeName();
    MenuWindow::updateCoffeValues();

    ui->add_button->hide();
    ui->subtract_button->hide();
}

MenuWindow::~MenuWindow()
{
    delete ui;
}
bool MenuWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == this && event->type() == QEvent::MouseButtonPress) {
        clearSelection();
        return true;
    }

    return QWidget::eventFilter(obj, event);
}


void MenuWindow::updateCoffeName(){
    int menuSize=drinks.size();
    Tdrinks* drink = drinks[currentCoffeId];

    if (currentCoffeId>menuSize-1){
        currentCoffeId=0;
        drink = drinks[currentCoffeId];
    }else if(currentCoffeId<0 ){
        currentCoffeId=menuSize-1;
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
    updateCoffeValues();
}


void MenuWindow::on_previous_button_clicked()
{
    currentCoffeId--;
    updateCoffeName();
    updateCoffeValues();
}

void MenuWindow::clearSelection()
{
    QList<QCheckBox*> checkboxes = this->findChildren<QCheckBox*>();

    for (QCheckBox *checkbox : checkboxes) {
        checkbox->setChecked(false);
    }

    ui->add_button->hide();
    ui->subtract_button->hide();
}



void MenuWindow::on_Water_checkbox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==Qt::Checked){
        ui->add_button->show();
        ui->subtract_button->show();
        ui->Power_checkbox->setChecked(false);
        ui->Milk_checkbox->setChecked(false);
        checkBoxId=1;
    }
}


void MenuWindow::on_Milk_checkbox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==Qt::Checked){
        ui->add_button->show();
        ui->subtract_button->show();
        ui->Power_checkbox->setChecked(false);
        ui->Water_checkbox->setChecked(false);
        checkBoxId=2;
    }
}


void MenuWindow::on_Power_checkbox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==Qt::Checked){
        ui->add_button->show();
        ui->subtract_button->show();
        ui->Milk_checkbox->setChecked(false);
        ui->Water_checkbox->setChecked(false);
        checkBoxId=3;
    }
}

