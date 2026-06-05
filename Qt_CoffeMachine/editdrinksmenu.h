#ifndef EDITDRINKSMENU_H
#define EDITDRINKSMENU_H

#include <QFrame>

namespace Ui {
class EditDrinksMenu;
}

class EditDrinksMenu : public QFrame
{
    Q_OBJECT
public:
    explicit EditDrinksMenu(QWidget *parent = nullptr);
    ~EditDrinksMenu();


private slots:
    void on_addDrinkButton_clicked();
    void on_removeDrinkButton_clicked();
    void on_modifyDrinkButton_clicked();

private:
    Ui::EditDrinksMenu *ui;
};

#endif