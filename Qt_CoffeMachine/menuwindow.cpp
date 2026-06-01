#include <QTimer>

#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "CoffeMachine.h"
#include "makingwindow.h"

int currentCoffeId=0;
int checkBoxId=0;

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWindow)
{
    machine.initializeMachine();
    ui->setupUi(this);
    this->installEventFilter(this);
    ui->previous_button->setEnabled(false);
    ui->next_button->setEnabled(true);
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
    if (currentCoffeId == 0) {
        ui->previous_button->setEnabled(true);
    }

    currentCoffeId++;
    updateCoffeName();
    updateCoffeValues();

    if (currentCoffeId >= drinks.size() - 1) {
        ui->next_button->setEnabled(false);
    }

    ui->add_button->hide();
    ui->subtract_button->hide();
    ui->Power_checkbox->setChecked(false);
    ui->Milk_checkbox->setChecked(false);
    ui->Water_checkbox->setChecked(false);
}


void MenuWindow::on_previous_button_clicked()
{
    if (currentCoffeId == drinks.size() - 1) {
        ui->next_button->setEnabled(true);
    }

    currentCoffeId--;
    updateCoffeName();
    updateCoffeValues();
    if(currentCoffeId==0){
       ui->previous_button->setEnabled(false);
    }

    ui->add_button->hide();
    ui->subtract_button->hide();
    ui->Power_checkbox->setChecked(false);
    ui->Milk_checkbox->setChecked(false);
    ui->Water_checkbox->setChecked(false);

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

void MenuWindow::updateEditButtonsVisibility()
{
    bool anyChecked =
        ui->Water_checkbox->isChecked() ||
        ui->Milk_checkbox->isChecked() ||
        ui->Power_checkbox->isChecked();

    ui->add_button->setVisible(anyChecked);
    ui->subtract_button->setVisible(anyChecked);

    if (!anyChecked) {
        checkBoxId = 0;
    }
    qDebug() << "CheckboxID: "<< checkBoxId;
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
    updateEditButtonsVisibility();
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
    updateEditButtonsVisibility();
}



void MenuWindow::on_Power_checkbox_checkStateChanged(const Qt::CheckState &arg1)
{
    if(arg1==Qt::Checked){
        Tdrinks* drink = drinks[currentCoffeId];
        ui->add_button->show();
        ui->subtract_button->show();
        if(drink->getPowerOfCoffe() >= 5){
            ui->add_button->hide();
        }
        else if(drink->getPowerOfCoffe() <= 0){
            ui->subtract_button->hide();
        }
        ui->Milk_checkbox->setChecked(false);
        ui->Water_checkbox->setChecked(false);
        checkBoxId=3;
    }
    updateEditButtonsVisibility();
}


void MenuWindow::on_add_button_pressed()
{
    QTimer timer;
    timer.start(500);
    Tdrinks* drink = drinks[currentCoffeId];
    switch(checkBoxId){
    case 1:
        drink->editVolume(drink->getVolumeOfWater()+5);
        break;
    case 2:
        drink->editVolumeOfMilk(drink->getVolumeOfMilk()+5);
        break;
    case 3:
        if(drink->getPowerOfCoffe()==0){
            ui->subtract_button->show();
        }
        drink->editPower(drink->getPowerOfCoffe()+1);
        if(drink->getPowerOfCoffe()>=5){
            ui->next_button->setEnabled(true);
            if(drink->getPowerOfCoffe() >= 5){
                ui->add_button->hide();
            }
        }
        break;
    default:
        qDebug() << "Nie zaznaczono checkboxa";
    }

    updateCoffeValues();
}


void MenuWindow::on_subtract_button_pressed()
{
    QTimer timer;
    timer.start(500);
    Tdrinks* drink = drinks[currentCoffeId];
    switch(checkBoxId){
    case 1:
        drink->editVolume(drink->getVolumeOfWater()-5);
        qDebug() << drinks[currentCoffeId]->getVolumeOfWater();
        break;
    case 2:
        drink->editVolumeOfMilk(drink->getVolumeOfMilk()-5);
        break;
    case 3:
        if(drink->getPowerOfCoffe() == 5){
            ui->add_button->show();
        }
        drink->editPower(drink->getPowerOfCoffe()-1);
        if(drink->getPowerOfCoffe() <= 0){
            ui->subtract_button->hide();
        }
        break;
    default:
        qDebug() << "Nie zaznaczono checkboxa";
    }

    updateCoffeValues();
}


void MenuWindow::on_make_coffe_button_clicked()
{
    Tdrinks* drink = drinks[currentCoffeId];
    if(machine.makeCoffee(drink->getName())){
        if (!makingWindow) {
           makingWindow = new makingwindow(nullptr);

            connect(makingWindow, &makingwindow::destroyed,
                    this,       &MenuWindow::show);
        }
        this->hide();
        makingWindow->show();
    }
    else{
        qDebug() << "Brak składników";
    }
}
