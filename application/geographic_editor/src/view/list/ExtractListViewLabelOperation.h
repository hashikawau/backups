//========================================
// ExtractListViewLabelOperation.h
//
//  Created on: 2013/12/21
//      Author: you
//========================================

#ifndef EXTRACTLISTVIEWLABELOPERATION_H_
#define EXTRACTLISTVIEWLABELOPERATION_H_

#include <QtCore/qstring.h>

#include "model/IShape.h"

namespace geoedit {

/*
 *
 */
class ExtractListViewLabelOperation: public IShape::IOperation {
public:
    ExtractListViewLabelOperation();
    virtual ~ExtractListViewLabelOperation();

    const QString& getString(IShape* shape) {
        visit(shape);
        return m_string;
    }

    virtual void operate(Rectangle* shape) override;
    virtual void operate(Ellipse* shape) override;

private:
    QString m_string;

};

} /* namespace geoedit */

#endif /* EXTRACTLISTVIEWLABELOPERATION_H_ */
