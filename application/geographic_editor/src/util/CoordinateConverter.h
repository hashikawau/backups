//========================================
// CoordinateConverter.h
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#ifndef COORDINATECONVERTER_H_
#define COORDINATECONVERTER_H_

#include <cmath>
#include <QtCore/qpoint.h>
#include <QtCore/qsize.h>

namespace geoedit {

/*
 *
 */
class CoordinateConverter {
public:
    struct PointD {
        double x;
        double y;
    };

public:
    CoordinateConverter(
            int width,
            int height,
            double centerX = 0.0,
            double centerY = 0.0,
            double ratio = 1.0);
    ~CoordinateConverter();

    void setSize(const QSize& size) {
        m_halfSize.setWidth(std::max(size.width() / 2, 1));
        m_halfSize.setHeight(std::max(size.height() / 2, 1));
    }
    void setOrigin(const PointD& point) {
        m_origin = point;
    }
    void setRatio(double ratio) {
        m_ratio = ratio;
    }
    const PointD& getOrigin() const {
        return m_origin;
    }
    double getRatio() const {
        return m_ratio;
    }

    int convert(double length) const {
        double coefficient = std::max(m_halfSize.width(), m_halfSize.height()) * m_ratio;
        return coefficient * length;
    }
    double convert(int length) const {
        double coefficient = std::max(m_halfSize.width(), m_halfSize.height()) * m_ratio;
        return length / coefficient;
    }

    QPoint convert(const PointD& point) const {
        double coefficient = std::max(m_halfSize.width(), m_halfSize.height()) * m_ratio;
        return QPoint(
                coefficient * (point.x - m_origin.x) + m_halfSize.width(),
                -coefficient * (point.y - m_origin.y) + m_halfSize.height());
    }
    PointD convert(const QPoint& point) const {
        double coefficient = std::max(m_halfSize.width(), m_halfSize.height()) * m_ratio;
        return PointD {
                (point.x() - m_halfSize.width()) / coefficient + m_origin.x,
                (point.y() - m_halfSize.height()) / -coefficient + m_origin.y };
    }

private:
    // widget's size's half
    QSize m_halfSize;
    //center coordinate in cartesian coordinates of the widget
    PointD m_origin;
    //
    double m_ratio;

};

} /* namespace geoedit */

#endif /* COORDINATECONVERTER_H_ */
