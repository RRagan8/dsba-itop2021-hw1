#include "renderarea.h"
#include <QPainter>

RenderArea::RenderArea(QWidget *parent) : QWidget(parent)
{}

void RenderArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    QColor colour2(255, 255, 255);

    painter.setBrush(colour2);
    painter.drawRect(0, 0, width() - 1, height() - 1);

    QColor colour1(213, 0, 0);

    painter.setBrush(colour1);
    painter.drawRoundedRect(0, 0, width() - 1, height() - 1, 15, 15);

    static const QPointF points[3] = {
        QPointF(3*width()/8, height()/3),
        QPointF(6*width()/8, height()/2),
        QPointF(3*width()/8, 2*height()/3),
    };

    painter.setBrush(colour2);

    painter.drawConvexPolygon(points, 3);
}
