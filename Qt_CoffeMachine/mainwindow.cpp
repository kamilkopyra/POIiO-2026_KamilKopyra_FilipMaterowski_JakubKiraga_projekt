#include "mainwindow.h"
#include "menuwindow.h"
#include "./ui_mainwindow.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (!menuWindow) {
        menuWindow = new MenuWindow(nullptr);        // tworzymy tylko raz

        connect(menuWindow, &MenuWindow::destroyed,
                this,       &MainWindow::show);
    }
    this->hide();           // chowamy okno startowe
    menuWindow->show();     // pokazujemy menu
}


void MainWindow::on_Settings_button_clicked()
{
    QMenu *menu = new QMenu(this);

    menu->addAction("Motyw");
    menu->addAction("Język");
    menu->addSeparator();
    menu->addAction("Statystyka");

    connect(menu, &QMenu::triggered, this, [](QAction *action) {
        qDebug() << "Wybrano: " << action -> text();
    });

    menu->exec(ui->Settings_button->mapToGlobal(
        ui->Settings_button->rect().bottomLeft()));
}

