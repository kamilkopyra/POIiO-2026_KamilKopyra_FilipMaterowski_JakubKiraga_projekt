#include "makingwindow.h"
#include "ui_makingwindow.h"

makingwindow::makingwindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::makingwindow)
{
    ui->setupUi(this);
}

makingwindow::~makingwindow()
{
    delete ui;
}
