#include <QTimer>

#include "menuwindow.h"
#include "ui_menuwindow.h"
#include "CoffeMachine.h"
#include "makingwindow.h"
#include "addingredientsmenu.h"
#include "editdrinksmenu.h"
#include "statusmenu.h"
#include <QMenu>

int currentCoffeId=0;
int checkBoxId=0;
Tdrinks drink_copy = Tdrinks();

MenuWindow::MenuWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MenuWindow)
{
    machine.initializeMachine();
    drink_copy = Tdrinks(*drinks[currentCoffeId]);
    ui->setupUi(this);
    setFixedSize(800, 550);
    this->installEventFilter(this);
    ui->previous_button->show();
    ui->next_button->show();
    MenuWindow::updateCoffeName();
    MenuWindow::updateCoffeValues();

    //ui->add_button->hide();
    //ui->subtract_button->hide();

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

    ui->Coffe_water->setText(QString::number(drink_copy.getVolumeOfWater(),'f',1) + "ml");
    ui->Coffe_milk->setText(QString::number(drink_copy.getVolumeOfMilk(),'f',1) + "ml");
    ui->Coffe_power->setText(QString::number(drink_copy.getPowerOfCoffe()));

}

void MenuWindow::on_next_button_clicked()
{
    if (currentCoffeId == 0) {
        ui->previous_button->show();
    }

    currentCoffeId++;
    drink_copy = Tdrinks(*drinks[currentCoffeId]);
    updateCoffeName();
    updateCoffeValues();

    if (currentCoffeId >= drinks.size() - 1) {
        ui->next_button->hide();
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
        ui->next_button->show();
    }

    currentCoffeId--;
    drink_copy = Tdrinks(*drinks[currentCoffeId]);
    updateCoffeName();
    updateCoffeValues();

    if(currentCoffeId==0){
        ui->previous_button->hide();
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
    if(anyChecked){
        switch(checkBoxId){
        case 1:
        if(drink_copy.getVolumeOfWater() > 20) ui->subtract_button->show();
        else ui->subtract_button->hide();

        if(drink_copy.getVolumeOfWater() < 500) ui->add_button->show();
        else ui->add_button->hide();
        break;
        case 2:
        if(drink_copy.getVolumeOfMilk() > 0) ui->subtract_button->show();
        else ui->subtract_button->hide();

        if(drink_copy.getVolumeOfMilk() < 500) ui->add_button->show();
        else ui->add_button->hide();
        break;
        case 3:
        if(drink_copy.getPowerOfCoffe() > 1) ui->subtract_button->show();
        else ui->subtract_button->hide();

        if(drink_copy.getPowerOfCoffe() < 5) ui->add_button->show();
        else ui->add_button->hide();
        break;
        default:
            qDebug() << "Nie zaznaczono CheckboxID";
        }
    }
    else{
        ui->add_button->hide();
        ui->subtract_button->hide();
    }
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
        ui->add_button->show();
        ui->subtract_button->show();
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
    switch(checkBoxId){
    case 1:
        drink_copy.editVolume(drink_copy.getVolumeOfWater()+5);
        break;
    case 2:
        drink_copy.editVolumeOfMilk(drink_copy.getVolumeOfMilk()+5);
        break;
    case 3:
        drink_copy.editPower(drink_copy.getPowerOfCoffe()+1);
        break;
    default:
        qDebug() << "Nie zaznaczono checkboxa";
    }
    updateEditButtonsVisibility();
    updateCoffeValues();
}


void MenuWindow::on_subtract_button_pressed()
{
    QTimer timer;
    timer.start(500);
    switch(checkBoxId){
    case 1:
        drink_copy.editVolume(drink_copy.getVolumeOfWater()-5);
        break;
    case 2:
        drink_copy.editVolumeOfMilk(drink_copy.getVolumeOfMilk()-5);
        break;
    case 3:
        drink_copy.editPower(drink_copy.getPowerOfCoffe()-1);
        break;
    default:
        qDebug() << "Nie zaznaczono checkboxa";
    }
    updateEditButtonsVisibility();
    updateCoffeValues();
}


void MenuWindow::on_make_coffe_button_clicked()
{
    if(machine.makeCoffee(drink_copy)){

            makingWindow = new makingwindow(drink_copy, nullptr);
            connect(makingWindow, &makingwindow::destroyed,
                    this, &MenuWindow::show);
            this->hide();
            makingWindow->show();
    }
    else{
        qDebug() << "Brak składników ";
    }
}


void MenuWindow::on_settings_button_clicked()
{
    QMenu *menu = new QMenu(this);
    menu->addAction("Status");
    menu->addAction("Dodaj składniki");
    menu->addAction("Edytuj menu napojów");
    menu->addSeparator();
    menu->addAction("Serwis");

    connect(menu, &QMenu::triggered, this, [this](QAction *action) {
        if (action->text() == "Dodaj składniki") {
            AddIngredientsMenu *dialog = new AddIngredientsMenu(this);
            dialog->setWindowFlags(Qt::Window);
            dialog->show();
        }
        if (action->text() == "Edytuj menu napojów") {
            EditDrinksMenu *dialog = new EditDrinksMenu(this);
            dialog->setWindowFlags(Qt::Window);
            dialog->show();
        }
        if (action->text() == "Status") {
            statusMenu *dialog = new statusMenu(this);
            dialog->setWindowFlags(Qt::Window);
            dialog->show();
        }
    });

    menu->exec(ui->settings_button->mapToGlobal(
        ui->settings_button->rect().bottomLeft()));
}
