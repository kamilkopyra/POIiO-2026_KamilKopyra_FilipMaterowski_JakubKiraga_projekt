#ifndef STATUSMENU_H
#define STATUSMENU_H

#include <QFrame>

namespace Ui {
class statusMenu;
}

class statusMenu : public QFrame
{
    Q_OBJECT

public:
    explicit statusMenu(QWidget *parent = nullptr);
    ~statusMenu();

private:
    Ui::statusMenu *ui;
};

#endif // STATUSMENU_H