#ifndef CUPWIDGET_H
#define CUPWIDGET_H

#include <QWidget>
#include <QTimer>

class CupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CupWidget(QWidget *parent = nullptr);
    void setDrinkColor(float milkRatio);
    void startFilling();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int fillLevel = 0; // 0-100
    QTimer *timer;
    QColor coffeeColor = QColor("#6f3a1f");
};

#endif