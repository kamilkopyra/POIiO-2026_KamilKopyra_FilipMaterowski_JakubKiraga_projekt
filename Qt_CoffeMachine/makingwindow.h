#ifndef MAKINGWINDOW_H
#define MAKINGWINDOW_H


#include <QWidget>
#include <QTimer>
#include "cupwidget.h"
#include "Tdrinks.h"

class MainWindow;

namespace Ui {
class makingwindow;
}

class makingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit makingwindow(Tdrinks drink, QWidget *parent = nullptr);
    ~makingwindow();

private:
    Ui::makingwindow *ui;
    MainWindow *mainWindow = nullptr;
    Tdrinks currentDrink;

};

#endif // MAKINGWINDOW_H
