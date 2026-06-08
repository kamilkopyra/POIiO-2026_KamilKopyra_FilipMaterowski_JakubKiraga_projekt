#include "mainwindow.h"
#include "menuwindow.h"
#include "./ui_mainwindow.h"
#include "addingredientsmenu.h"
#include "statusmenu.h"

#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(800, 550);
    QPixmap pixmap("://CoffeCup.png");
    ui->Cup_image->setPixmap(pixmap);
    ui->Cup_image->setScaledContents(true);

    ind_menu = new AddIngredientsMenu(this);
    stat_menu = new statusMenu(this);

    ind_menu->setWindowFlags(Qt::Window);
    stat_menu->setWindowFlags(Qt::Window);

    qDebug() << "ind_menu:" << ind_menu;
    qDebug() << "stat_menu:" << stat_menu;


    QAction *actionDefault = new QAction(" Domyślny", this);
    QAction *actionLight   = new QAction(" Jasny",    this);
    QAction *actionDark    = new QAction(" Ciemny",   this);

    ui->menu->addAction(actionDefault);
    ui->menu->addAction(actionLight);
    ui->menu->addAction(actionDark);


    connect(actionDefault, &QAction::triggered, this, [this]() { setTheme(0); });
    connect(actionLight,   &QAction::triggered, this, [this]() { setTheme(1); });
    connect(actionDark,    &QAction::triggered, this, [this]() { setTheme(2); });

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


    // void MainWindow::on_Settings_button_clicked()
    // {
    //     ui->menu->clear(); // czyścimy żeby nie duplikowały się akcje przy każdym kliknięciu

    //     // Sekcja motywu
    //     QAction *labelMotyw = new QAction("— Motyw —", this);
    //     labelMotyw->setEnabled(false); // tylko label, nie klikalny
    //     ui->menu->addAction(labelMotyw);

    //     QAction *actionDefault = new QAction("🖥️ Domyślny", this);
    //     QAction *actionLight   = new QAction("☀️ Jasny",    this);
    //     QAction *actionDark    = new QAction("🌙 Ciemny",   this);

    //     ui->menu->addAction(actionDefault);
    //     ui->menu->addAction(actionLight);
    //     ui->menu->addAction(actionDark);

    //     ui->menu->addSeparator();
    //     ui->menu->addAction("Język");

    //     connect(actionDefault, &QAction::triggered, this, [this]() { setTheme(0); });
    //     connect(actionLight,   &QAction::triggered, this, [this]() { setTheme(1); });
    //     connect(actionDark,    &QAction::triggered, this, [this]() { setTheme(2); });

    //     // Pokazujemy menu pod przyciskiem
    //     ui->menu->exec(ui->Settings_button->mapToGlobal(
    //         ui->Settings_button->rect().bottomLeft()));
    // }

void MainWindow::setTheme(int theme)
{
    currentTheme = theme;

    switch (theme) {
    case 0: // Domyślny
        qApp->setStyleSheet("");
        break;

    case 1: // Jasny
        qApp->setStyleSheet(R"(
            QWidget {
                background-color: #ffffff;
                color: #000000;
            }
            QPushButton {
                background-color: #e0e0e0;
                color: #000000;
                border: 1px solid #aaa;
                border-radius: 4px;
                padding: 5px 10px;
            }
            QPushButton:hover {
                background-color: #c8c8c8;
            }
            QLineEdit, QTextEdit, QPlainTextEdit {
                background-color: #f5f5f5;
                color: #000000;
                border: 1px solid #aaa;
            }
            QLabel {
                color: #000000;
            }
            QMenuBar {
                background-color: #f0f0f0;
                color: #000000;
            }
            QMenuBar::item:selected {
                background-color: #dcdcdc;
            }
        )");
        break;

    case 2: // Ciemny
        qApp->setStyleSheet(R"(
            QWidget {
                background-color: #2b2b2b;
                color: #f0f0f0;
            }
            QPushButton {
                background-color: #3c3f41;
                color: #f0f0f0;
                border: 1px solid #555;
                border-radius: 4px;
                padding: 5px 10px;
            }
            QPushButton:hover {
                background-color: #4c5052;
            }
            QLineEdit, QTextEdit, QPlainTextEdit {
                background-color: #3c3f41;
                color: #f0f0f0;
                border: 1px solid #555;
            }
            QLabel {
                color: #f0f0f0;
            }
            QMenuBar {
                background-color: #3c3f41;
                color: #f0f0f0;
            }
            QMenuBar::item:selected {
                background-color: #4c5052;
            }
        )");
        break;
    }
}
