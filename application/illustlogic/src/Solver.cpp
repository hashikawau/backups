/*
 * Solver.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: hashkw
 */

#include "Solver.h"
#include "InputDataFile.h"
#include "BinaryMatrix.h"
#include "HintLineSolver.h"

#include <system_error>
#include <boost/filesystem/operations.hpp>

namespace illustlogic
{

SolverPtr Solver::create(const std::string& inputDataFilePath)
{
    //-----------------------------------------------------
    // read input data file
    //
    // input data file format:
    //   space separated values
    //     number-of-rows number-of-columns
    //
    //     row[0]
    //       :
    //
    //     column[0]
    //       :
    //
    //   csv
    //
    //   xml
    //
    //   png
    //     scanned image
    //-----------------------------------------------------
    if(!boost::filesystem::exists(inputDataFilePath))
    {
        throw std::system_error(std::make_error_code(std::errc::no_such_file_or_directory), "");
    }
    InputDataFilePtr inputData = CSVInputDataFile::create(inputDataFilePath);

    BinaryMatrixPtr    binaryMatrix   = std::make_shared<BinaryMatrix>();
    HintLineSolverPtr  hintLineSolver = std::make_shared<HintLineSolver>();


    SolverPtr result = SolverPtr(new Solver(
            binaryMatrix,
            hintLineSolver));

    return result;
}

Solver::Solver(BinaryMatrixPtr binaryMatrix, HintLineSolverPtr hintLineSolver)
: m_binaryMatrix(binaryMatrix)
, m_hintLineSolver(hintLineSolver)
{
}

Solver::~Solver()
{
}
void Solver::execute()
{
    // TODO: not implement
    //
}

void Solver::showResolution()
{

}

} // namespace illustlogic
