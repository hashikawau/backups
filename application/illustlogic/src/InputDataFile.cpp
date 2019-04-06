/*
 * InputDataFile.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: hashkw
 */

#include "InputDataFile.h"

namespace illustlogic
{

//---------------------------------------------------------
//
//---------------------------------------------------------
/**
 *
 */
InputDataFile::~InputDataFile()
{
}

//---------------------------------------------------------
//
//---------------------------------------------------------
/**
 *
 */
InputDataFilePtr CSVInputDataFile::create(const std::string& csvFilePath)
{
    return InputDataFilePtr(new CSVInputDataFile(csvFilePath));
}

/**
 *
 */
CSVInputDataFile::CSVInputDataFile(const std::string& csvFilePath)
{

}

/**
 *
 */
CSVInputDataFile::~CSVInputDataFile()
{
}
int CSVInputDataFile::getNumberOfRows() const
{
    return m_numberOfRows;
}
int CSVInputDataFile::getNumberOfCols() const
{
    return m_numberOfCols;
}
std::vector<std::vector<int>> CSVInputDataFile::getHorizontalHintLine() const
{
    return m_horizontalHinLine;
}
std::vector<std::vector<int>> CSVInputDataFile::getVerticalHintLine() const
{
    return m_verticalHinLine;
}

} // namespace illustlogic
