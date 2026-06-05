#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "makingwindow.h"
#include <QWidget>

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

    void updateCoffeName();

    void updateCoffeValues();

    void updateEditButtonsVisibility();


private slots:

    void on_next_button_clicked();

    void on_previous_button_clicked();

    void on_Water_checkbox_checkStateChanged(const Qt::CheckState &arg1);

    void on_Milk_checkbox_checkStateChanged(const Qt::CheckState &arg1);

    void on_Power_checkbox_checkStateChanged(const Qt::CheckState &arg1);

    void on_add_button_pressed();

    void on_subtract_button_pressed();

    void on_make_coffe_button_clicked();

    void on_settings_button_clicked();


private:
    Ui::MenuWindow *ui;
    makingwindow *makingWindow = nullptr;
    void clearSelection();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

};

#endif // MENUWINDOW_H
