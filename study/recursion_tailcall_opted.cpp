
#include <iostream>

template<typename T>
void function_1(const int index, T& accum) {
    accum += index;
    if (index > 0) function_1<T>(index - 1, accum);
}


int main(int argc, char* argv[]){
    constexpr int num = 50000000;
    double d = 0.0;
    //function_1(num, d);
    for(int i=num; i> 0; --i){
        d += i;
    }
    
    std::cout << d << std::endl;
}

