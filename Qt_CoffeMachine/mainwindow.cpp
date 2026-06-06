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
    QPixmap pixmap("://Coffe.png");
    ui->Cup_image->setPixmap(pixmap);
    ui->Cup_image->setScaledContents(true);

    ind_menu = new AddIngredientsMenu(this);
    stat_menu = new statusMenu(this);

    ind_menu->setWindowFlags(Qt::Window);
    stat_menu->setWindowFlags(Qt::Window);

    qDebug() << "ind_menu:" << ind_menu;
    qDebug() << "stat_menu:" << stat_menu;

    connect(ind_menu,
            &AddIngredientsMenu::Water_added,
            stat_menu,
            &statusMenu::Water_val_changed);

    connect(ind_menu,
            &AddIngredientsMenu::Milk_added,
            stat_menu,
            &statusMenu::Milk_val_changed);

    connect(ind_menu,
            &AddIngredientsMenu::Beans_added,
            stat_menu,
            &statusMenu::Beans_val_changed);
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

    menu->addAction("Status");
    menu->addAction("Dodaj składniki");
    menu->addAction("Motyw");
    menu->addAction("Język");
    menu->addSeparator();
    menu->addAction("Statystyka");

    connect(menu, &QMenu::triggered, this, [this](QAction *action) {

        qDebug() << "Wybrano: " << action -> text();

            // if (action->text() == "Dodaj składniki") {
            //     // AddIngredientsMenu *dialog = new AddIngredientsMenu(this);
            //     // dialog->setWindowFlags(Qt::Window);
            //     // dialog->show();
            //     ind_menu->show();
            //     ind_menu->raise();
            //     ind_menu->activateWindow();
            // }
            // if (action->text() == "Status") {
            //     // statusMenu *dialog = new statusMenu(this);
            //     // dialog->setWindowFlags(Qt::Window);
            //     // dialog->show();
            //     stat_menu->show();
            //     stat_menu->raise();
            //     stat_menu->activateWindow();
            // }
        });

    menu->exec(ui->Settings_button->mapToGlobal(
        ui->Settings_button->rect().bottomLeft()));
}

