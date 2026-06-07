#ifndef SERVICEWINDOW_H
#define SERVICEWINDOW_H
#include <QFrame>
namespace Ui {
class serviceWindow;
}
class serviceWindow : public QFrame
{
    Q_OBJECT
public:
    explicit serviceWindow(QWidget *parent = nullptr);
    ~serviceWindow();

private slots:
    void on_loginButton_clicked();
    void on_cleanButton_clicked();
    void on_fixButton_clicked();

private:
    Ui::serviceWindow *ui;
};
#endif // SERVICEWINDOW_H