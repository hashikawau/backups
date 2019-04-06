//========================================
// IconEditor.h
//
//  Created on: 2013/11/14
//      Author: you
//========================================

#ifndef qtsample_02_ICONEDITOR_H_
#define qtsample_02_ICONEDITOR_H_

#include <QtWidgets/qwidget.h>
#include <QtGui/qcolor.h>
#include <QtGui/qimage.h>

class IconEditor: public QWidget {
Q_OBJECT //
Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor) //
Q_PROPERTY(QImage iconImage READ iconImage WRITE setIconImage)//
Q_PROPERTY(int zoomFactor READ zoomFactor WRITE setZoomFactor)//

public:
    IconEditor(QWidget* parent = 0);
    virtual ~IconEditor();

    void setPenColor(const QColor& newColor) {
        curColor = newColor;
    }
    QColor penColor() const {
        return curColor;
    }

    void setZoomFactor(int newZoom) {
        if (newZoom < 1) newZoom = 1;
        if (newZoom != zoom) {
            zoom = newZoom;
            update();
            updateGeometry();
        }
    }
    int zoomFactor() const {
        return zoom;
    }

    void setIconImage(const QImage& newImage) {
        if (newImage != image) {
            image = newImage.convertToFormat(QImage::Format_ARGB32);
            update();
            updateGeometry();
        }
    }
    QImage iconImage() const {
        return image;
    }

    QSize sizeHint() const {
        QSize size = zoom * image.size();
        if (zoom >= 3) size += QSize(1, 1);
        return size;
    }

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);
    virtual void paintEvent(QPaintEvent* event);

private:
    void setImagePixel(const QPoint& pos, bool opaque);
    QRect pixelRect(int i, int j) const;

    QColor curColor;
    QImage image;
    int zoom;

};

#endif /* qtsample_02_ICONEDITOR_H_ */
