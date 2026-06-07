#include "servicewindow.h"
#include "ui_servicewindow.h"
#include "CoffeMachine.h"
#include <QMessageBox>
#include <QInputDialog>


serviceWindow::serviceWindow(QWidget *parent)
    : QFrame(parent)
    , ui(new Ui::serviceWindow)
{
    ui->setupUi(this);
    ui->fixButton->setVisible(false);

}
serviceWindow::~serviceWindow()
{
    delete ui;
}

void serviceWindow::on_loginButton_clicked()
{
    bool ok;
    QString password = QInputDialog::getText(this, "Logowanie serwisanta",
                                             "Podaj hasło:", QLineEdit::Password, "", &ok);

    if (ok && password == "1234") {
        ui->fixButton->setVisible(true);
        QMessageBox::information(this, "Sukces", "Zalogowano jako serwisant.");
    } else if (ok) {
        QMessageBox::warning(this, "Błąd", "Nieprawidłowe hasło.");
    }
}

void serviceWindow::on_cleanButton_clicked()
{
    machine.cleanMachine();
    QMessageBox::information(this, "Sukces", "Maszyna została wyczyszczona.");
}

void serviceWindow::on_fixButton_clicked()
{
    machine.descaling();
    QMessageBox::information(this, "Sukces", "Maszyna została naprawiona.");
    ui->fixButton->setVisible(false);
}