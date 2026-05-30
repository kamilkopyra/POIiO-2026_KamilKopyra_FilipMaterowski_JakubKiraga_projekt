#ifndef MAKINGWINDOW_H
#define MAKINGWINDOW_H

#include <QWidget>
#include <QTimer>

class MainWindow;

namespace Ui {
class makingwindow;
}

class makingwindow : public QWidget
{
    Q_OBJECT

public:
    explicit makingwindow(QWidget *parent = nullptr);
    ~makingwindow();

private:
    Ui::makingwindow *ui;
    MainWindow *mainWindow = nullptr;

};

#endif // MAKINGWINDOW_H
