//========================================
// CoordinateConverter.cpp
//
//  Created on: 2013/12/14
//      Author: you
//========================================

#include "CoordinateConverter.h"

namespace geoedit {

CoordinateConverter::CoordinateConverter(int width, int height, double centerX, double centerY, double ratio)
        : m_halfSize(std::max(width / 2, 1), std::max(height / 2, 1)),
                m_origin(PointD { centerX, centerY }),
                m_ratio(ratio)
{
}

CoordinateConverter::~CoordinateConverter() {
}

} /* namespace geoedit */

