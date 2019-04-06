/*
 * BinaryMatrix.h
 *
 *  Created on: Apr 4, 2015
 *      Author: hashkw
 */

#ifndef SRC_BINARYMATRIX_H_
#define SRC_BINARYMATRIX_H_

#include <vector>

namespace illustlogic
{

class BinaryMatrix
{
public:
    BinaryMatrix();
    ~BinaryMatrix();

    enum BoxState
    : int
    {
        UNKNOWN,
        WHITE,
        BLACK,
    };
    typedef std::vector<BoxState> LineBoxState;

    LineBoxState getHorizontalBoxes(int indexOfLine) const;
    LineBoxState getVerticalBoxes(int indexOfLine) const;

private:
    std::vector<LineBoxState> m_horizontalBoxes;

};

} // namespace illustlogic

#endif // SRC_BINARYMATRIX_H_
