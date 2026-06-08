#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuwindow.h"
#include "addingredientsmenu.h"
#include "statusmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButton_2_clicked();

    void setTheme(int theme);

private:
    Ui::MainWindow *ui;
    MenuWindow *menuWindow = nullptr;

    AddIngredientsMenu *ind_menu = nullptr;
    statusMenu *stat_menu = nullptr;

    int currentTheme = 0;
};
#endif // MAINWINDOW_H
