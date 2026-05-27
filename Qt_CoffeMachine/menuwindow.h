#ifndef MENUWINDOW_H
#define MENUWINDOW_H

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

private slots:
    void on_label_linkActivated(const QString &link);

    void on_next_button_clicked();

    void on_previous_button_clicked();

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
