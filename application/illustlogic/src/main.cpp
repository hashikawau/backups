#include <iostream>
#include <vector>

#include <fstream>

#include <memory>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
//#include <boost/algorithm/string.hpp>

#include "Solver.h"

/**
 *
 */
int main(int argc, char* argv[])
{
    //-----------------------------------------------------
    // arguments check
    //
    // argument:
    //   arg[0]
    //     input data file path
    //-----------------------------------------------------
    if (argc != 2)
    {
        std::cerr << "usage: file-path" << std::endl;
        return 1;
    }

    try
    {
        using namespace illustlogic;
        std::string inputDataFilePath = argv[1];
        SolverPtr solver = Solver::create(inputDataFilePath);

        solver->execute();

        solver->showResolution();
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}

