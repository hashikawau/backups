/*
 * InputDataFile.h
 *
 *  Created on: Apr 3, 2015
 *      Author: hashkw
 */

#ifndef SRC_INPUTDATAFILE_H_
#define SRC_INPUTDATAFILE_H_

#include <vector>
#include <memory>

namespace illustlogic
{

class InputDataFile;
typedef std::shared_ptr<InputDataFile> InputDataFilePtr;

/**
 *
 */
class InputDataFile
{
public:
    virtual ~InputDataFile() =0;
    virtual int getNumberOfRows() const =0;
    virtual int getNumberOfCols() const =0;
    virtual std::vector<std::vector<int>> getHorizontalHintLine() const =0;
    virtual std::vector<std::vector<int>> getVerticalHintLine() const =0;

protected:
    InputDataFile() = default;

    InputDataFile(const InputDataFile&) = delete;
    InputDataFile& operator=(const InputDataFile&) = delete;
    InputDataFile(InputDataFile&&) = delete;
    InputDataFile& operator=(InputDataFile&&) = delete;

};

/**
 *
 */
class CSVInputDataFile: public InputDataFile
{
public:
    static InputDataFilePtr create(const std::string& csvFilePath);

    virtual ~CSVInputDataFile();
    virtual int getNumberOfRows() const;
    virtual int getNumberOfCols() const;
    virtual std::vector<std::vector<int>> getHorizontalHintLine() const;
    virtual std::vector<std::vector<int>> getVerticalHintLine() const;

private:
    CSVInputDataFile(const std::string& csvFilePath);

    int m_numberOfRows;
    int m_numberOfCols;
    std::vector<std::vector<int>> m_horizontalHinLine;
    std::vector<std::vector<int>> m_verticalHinLine;

};

} // namespace illustlogic

#endif // SRC_INPUTDATAFILE_H_
