#ifndef ADDINGREDIENTSMENU_H
#define ADDINGREDIENTSMENU_H

#include <QFrame>

namespace Ui {
class AddIngredientsMenu;
}

class AddIngredientsMenu : public QFrame
{
    Q_OBJECT

public:
    explicit AddIngredientsMenu(QWidget *parent = nullptr);
    ~AddIngredientsMenu();

private slots:
    void on_addButton_clicked();

private:
    Ui::AddIngredientsMenu *ui;

signals:
    void Water_added();
    void Milk_added();
    void Beans_added();
};

#endif // ADDINGREDIENTSMENU_H
