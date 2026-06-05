#include "cupwidget.h"
#include <QPainter>
#include <QPainterPath>

CupWidget::CupWidget(QWidget *parent) : QWidget(parent)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=]() {
        if (fillLevel < 100) {
            fillLevel += 2;
            update();
        } else {
            timer->stop();
        }
    });
}

void CupWidget::startFilling()
{
    fillLevel = 0;
    timer->start(100);
}

void CupWidget::setDrinkColor(float milkRatio)
{
    // sama kawa = ciemny brąz, samo mleko = jasny beż
    int r = 80  + (200 - 80)  * milkRatio;
    int g = 40  + (170 - 40)  * milkRatio;
    int b = 20  + (130 - 20)  * milkRatio;
    coffeeColor = QColor(r, g, b);
}

void CupWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int w = width();
    int h = height();

    // Wymiary kubka
    int cupLeft   = w / 4;
    int cupTop    = h / 6;
    int cupWidth  = w / 2;
    int cupHeight = h * 2 / 3;

    // Tło kubka
    painter.setBrush(QColor("#3d2b1f"));
    painter.setPen(QPen(QColor("#1a0f0a"), 3));

    QPainterPath cupShape;
    cupShape.moveTo(cupLeft, cupTop);
    cupShape.lineTo(cupLeft + cupWidth * 0.1, cupTop + cupHeight);
    cupShape.lineTo(cupLeft + cupWidth * 0.9, cupTop + cupHeight);
    cupShape.lineTo(cupLeft + cupWidth, cupTop);
    cupShape.closeSubpath();
    painter.drawPath(cupShape);

    // Kawa
    int coffeeHeight = (cupHeight - 10) * fillLevel / 100;
    int coffeeTop    = cupTop + cupHeight - coffeeHeight;

    QPainterPath coffeeShape;
    coffeeShape.moveTo(cupLeft + cupWidth * 0.1 * (1 - (float)fillLevel/100),
                       coffeeTop);
    coffeeShape.lineTo(cupLeft + cupWidth * 0.1, cupTop + cupHeight - 5);
    coffeeShape.lineTo(cupLeft + cupWidth * 0.9, cupTop + cupHeight - 5);
    coffeeShape.lineTo(cupLeft + cupWidth * (1 - 0.1 * (1 - (float)fillLevel/100)),
                       coffeeTop);
    coffeeShape.closeSubpath();

    // kolor kawy - kolor jest obliczany na podstawie stusunku mleka to całości objętości
    painter.setBrush(coffeeColor);
    painter.setPen(Qt::NoPen);
    painter.drawPath(coffeeShape);

    // Uchwyt kubka
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(QColor("#3d2b1f"), 4));
    painter.drawArc(cupLeft + cupWidth - 5, cupTop + cupHeight/4,
                    cupWidth/4, cupHeight/2, -90*16, 180*16);

    // Spodek
    painter.setBrush(QColor("#3d2b1f"));
    painter.setPen(QPen(QColor("#1a0f0a"), 2));
    painter.drawEllipse(cupLeft - 10, cupTop + cupHeight,
                        cupWidth + 20, 15);
}