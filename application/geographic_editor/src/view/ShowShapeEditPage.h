//========================================
// ShowShapeEditPage.h
//
//  Created on: 2013/12/22
//      Author: you
//========================================

#ifndef SHOWSHAPEEDITPAGE_H_
#define SHOWSHAPEEDITPAGE_H_

#include "model/IShape.h"

#include <QtWidgets/qwidget.h>

class QStackedLayout;

namespace geoedit {

/*
 *
 */
class ShowShapeEditPage
: public QWidget,
        public IShape::IOperation
{
private:
    enum class SHAPES
        : int {
            RECTANGLE = 0,
        ELLIPSE,
        SIZE
    };
    //    class EditRectanglePage;

public:
    ShowShapeEditPage(QWidget* parent = 0);
    virtual ~ShowShapeEditPage();

    void changeEditPage(IShape* shape) {
        visit(shape);
    }

    virtual void operate(Rectangle* shape) override;
    virtual void operate(Ellipse* shape) override;

private:
    QStackedLayout* m_layout;
    QWidget* m_pages[static_cast<int>(SHAPES::SIZE)];

};

} /* namespace geoedit */

#endif /* SHOWSHAPEEDITPAGE_H_ */
