#include "lsystemview.h"
#include <QPainter>
#include <QPointF>

#include <iostream>

LSystemView::LSystemView(QWidget *parent) : QWidget(parent)
{
    QSizePolicy p = sizePolicy();
    p.setHeightForWidth(true);
    setSizePolicy(p);

    colors[0] = QColor(Qt::black);
    colors[1] = QColor(120, 80, 0);
    colors[2] = QColor(0, 120, 0, 200);
    colors[3] = QColor(0, 180, 0, 200);
    colors[4] = QColor(0, 220, 0, 200);
    colors[5] = QColor(Qt::red);
    colors[6] = QColor(Qt::green);
    colors[7] = QColor(Qt::blue);
}

void LSystemView::setLSystem(LSystem* lsystem)
{
    this->lsystem = lsystem;
    repaint();
}

void LSystemView::paintEvent(QPaintEvent*)
{
    if (!lsystem)
        return;

    QPainter painter(this);
    QPen pen;

    Bounds dims = lsystem->getBounds();
    Vector margins(0 - dims.left, 0 - dims.bottom);
    double sw = dims.right - dims.left;
    double sh = dims.top - dims.bottom;
    double size, zoom;
    if (sw > sh)
    {
        size = sw;
        if (size < 1)
            size = 1;
        zoom = width() / size;
        margins.y += (size - sh) / 2.0;
    }
    else
    {
        size = sh;
        if (size < 1)
            size = 1;
        zoom = width() / size;
        margins.x += (size - sw) / 2.0;
    }

    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(rect(), Qt::white);

    std::vector<Segment>::iterator it;
    for (it = lsystem->getSegments().begin(); it != lsystem->getSegments().end(); ++it)
    {
        Vector p1 = (margins + it->origin) * zoom;
        Vector p2 = (margins + it->origin + it->direction) * zoom;

        if (boldLines)
            pen.setWidth(it->lineWidth);
        if (correctTrunks && it->lineWidth > 1)
            pen.setColor(colors[1]);
        else
            pen.setColor(colors[it->color]);
        painter.setPen(pen);
        painter.drawLine(QPointF(p1.x, height() - p1.y), QPointF(p2.x, height() - p2.y));
    }
}

void LSystemView::resizeEvent(QResizeEvent*)
{
    QSize s = size();
    if (s.width() > s.height())
        resize(s.height(), s.height());
}

