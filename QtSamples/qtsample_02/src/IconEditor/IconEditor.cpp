//========================================
// IconEditor.cpp
//
//  Created on: 2013/11/14
//      Author: you
//========================================
#include "IconEditor.h"
#include <QtGui/qpainter.h>
#include <QtGui/qevent.h>

#include <iostream>

IconEditor::IconEditor(QWidget* parent)
        : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    curColor = Qt::black;
    zoom = 8;

    image = QImage(16, 16, QImage::Format_ARGB32);
    image.fill(qRgba(0, 0, 0, 0));
}

IconEditor::~IconEditor() {
}

//protected
void IconEditor::mousePressEvent(QMouseEvent* event) {
    std::cout << "mouse pressed" << std::endl;

    if (event->button() == Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->button() == Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}
void IconEditor::mouseMoveEvent(QMouseEvent* event) {
    std::cout << "mouse move" << std::endl;

    if (event->buttons() & Qt::LeftButton) {
        setImagePixel(event->pos(), true);
    } else if (event->buttons() & Qt::RightButton) {
        setImagePixel(event->pos(), false);
    }
}

void IconEditor::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    if (zoom >= 3) {
        painter.setPen(palette().foreground().color());
        for (int i = 0; i <= image.width(); ++i)
            painter.drawLine(zoom * i, 0, zoom * i, zoom * image.height());
        for (int j = 0; j <= image.height(); ++j)
            painter.drawLine(0, zoom * j, zoom * image.width(), zoom * j);
    }

    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            QRect rect = pixelRect(i, j);
            if (!event->region().intersected(rect).isEmpty()) {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                if (color.alpha() < 255) painter.fillRect(rect, Qt::white);
                painter.fillRect(rect, color);
            }
        }
    }
}

//private
QRect IconEditor::pixelRect(int i, int j) const {
    if (zoom >= 3) {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    } else {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}

void IconEditor::setImagePixel(const QPoint& pos, bool opaque) {
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j)) {
        if (opaque) {
            image.setPixel(i, j, penColor().rgba());
        } else {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }
        update(pixelRect(i, j));
    }
}

