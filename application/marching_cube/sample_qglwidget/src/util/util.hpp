//========================================
// util.hpp
//
//  Created on: 2014/05/11
//      Author: you
//========================================

#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <iostream>

struct util{
    template<typename T>
    static void print(const T& value){
        std::cout << "mat = [" << "\n";
        for(int i=0; i< T::row_size(); ++i){
            for(int j=0; j< T::col_size(); ++j){
                if(j > 0)
                    std::cout << ", ";
                else
                    std::cout << "\t";
                std::cout << value[i][j];
            }
            std::cout << "\n";
        }
        std::cout << "]" << std::endl;
    }
};



#endif // UTIL_HPP_
