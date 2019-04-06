/*
 * BinaryMatrix.cpp
 *
 *  Created on: Apr 4, 2015
 *      Author: hashkw
 */

#include "BinaryMatrix.h"

namespace illustlogic
{

BinaryMatrix::BinaryMatrix()
{
}

BinaryMatrix::~BinaryMatrix()
{
}

BinaryMatrix::LineBoxState BinaryMatrix::getHorizontalBoxes(int indexOfLine) const
{
    return m_horizontalBoxes.at(indexOfLine);
}

BinaryMatrix::LineBoxState BinaryMatrix::getVerticalBoxes(int indexOfLine) const
{
    BinaryMatrix::LineBoxState result;
    for(std::size_t i=0; i< m_horizontalBoxes.size(); ++i)
    {
        result.push_back(m_horizontalBoxes.at(i).at(indexOfLine));
    }

    return result;
}

} // namespace illustlogic
