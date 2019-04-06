/*
 * Solver.h
 *
 *  Created on: Apr 3, 2015
 *      Author: hashkw
 */

#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include <memory>

namespace illustlogic
{

class Solver;
typedef std::shared_ptr<Solver> SolverPtr;
class BinaryMatrix;
typedef std::shared_ptr<BinaryMatrix> BinaryMatrixPtr;
class HintLineSolver;
typedef std::shared_ptr<HintLineSolver> HintLineSolverPtr;

class Solver
{
public:
    static SolverPtr create(const std::string& inputDataFilePath);
    ~Solver();

    void execute();

    void showResolution();

private:
    Solver(BinaryMatrixPtr binaryMatrix, HintLineSolverPtr hintLineSolver);

    BinaryMatrixPtr    m_binaryMatrix;
    HintLineSolverPtr  m_hintLineSolver;

};

} // namespace illustlogic

#endif // SRC_SOLVER_H_
