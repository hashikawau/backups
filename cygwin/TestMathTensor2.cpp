






//===========================================================
//===========================================================
#include <iostream>
using namespace std;

#include "../lang/Math.h"
#include "../base/math/MathTensor2_cpp.h"
typedef MathTensor2 Matrix;
//===========================================================
//===========================================================
int main(int argc, char* argv[])
{
    ifstream stream;
    //===========================================================
    if(argc < 2){
        cout << "enter the file path" << endl;
        return 1;
    }
    
    stream.open(argv[1]);
    //===========================================================
    if(!stream){
        cout << "no such file" << endl;
        return 1;
    }
    
    Matrix temp(1, 2);
    temp.read(stream);
    int numX = temp[0][0];
    int numU = temp[0][1];
    
    Matrix A(numX, numX);
    A.read(stream);
    A.show();
    
    String s1 = String("1\n2\n3");
    Matrix mt201(4, 4);
    Matrix mt202(mt201);//(4, s1);
    
    //cout << mt101.toString() << endl;
    //cout << mt101[0] << endl;
    
    //mt101[2] = 99;
    //cout << mt101[2] << endl;
    
    return 0;
}
//===========================================================
//===========================================================

