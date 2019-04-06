/*
 * _main.cpp
 *
 *  Created on: 2013/03/22
 *      Author: you
 */

#include <omp.h>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {

    std::cout << _OPENMP << std::endl;

    int count = 0;
    int num = 100000000;
#pragma omp parallel
    {
        std::cout << "thread num = " << omp_get_thread_num();
        std::cout << ", num procs = " << omp_get_num_procs();
        std::cout << ", num threads = " << omp_get_num_threads();
        std::cout << std::endl;

#pragma omp for reduction (+:count)
        for (int i = 0; i < num; ++i) {
            ++count;
        }
    }
    std::cout << count << std::endl;

    return 0;
}

