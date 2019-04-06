//========================================
// EditEllipsePage.h
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#ifndef EDITELLIPSEPAGE_H_
#define EDITELLIPSEPAGE_H_

#include <QtWidgets/qwidget.h>

class QLineEdit;

namespace geoedit {

class Ellipse;

/*
 *
 */
class EditEllipsePage: public QWidget {
Q_OBJECT

public:
    EditEllipsePage(QWidget* parent = 0);
    virtual ~EditEllipsePage();

    void setModel(Ellipse* shape);

private slots:
    void setValue(const QString& text);

private:
    Ellipse* m_shape;
    QLineEdit* m_centerX;
    QLineEdit* m_centerY;
    QLineEdit* m_radiusX;
    QLineEdit* m_radiusY;

};

} /* namespace geoedit */

#endif /* EDITELLIPSEPAGE_H_ */
