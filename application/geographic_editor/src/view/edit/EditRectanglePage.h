//========================================
// EditRectanglePage.h
//
//  Created on: 2013/12/23
//      Author: you
//========================================

#ifndef EDITRECTANGLEPAGE_H_
#define EDITRECTANGLEPAGE_H_

#include <QtWidgets/qwidget.h>

class QLineEdit;

namespace geoedit {

class Rectangle;

/*
 *
 */
class EditRectanglePage: public QWidget {
Q_OBJECT

public:
    EditRectanglePage(QWidget* parent = 0);
    virtual ~EditRectanglePage();

    void setModel(Rectangle* shape);

private slots:
    void setValue(const QString& text);

private:
    Rectangle* m_shape;
    QLineEdit* m_left;
    QLineEdit* m_right;
    QLineEdit* m_bottom;
    QLineEdit* m_top;

};

} /* namespace geoedit */

#endif /* EDITRECTANGLEPAGE_H_ */
