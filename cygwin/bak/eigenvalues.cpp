

//===========================================================
//===========================================================
//#include <iostream>
//using namespace std;

#include <iostream.h>
#include <fstream.h>
#include <math.h>
#include <stdlib.h>
#include "Matrix.h"
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int main(int argc, char* argv[])
{
    //===========================================================
    
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
    
    char ch;
    char str[20];
    int count =0;
    int size =0;
    //===========================================================
    while(stream.get(ch)){
        if(ch == '\n'){
            if(count){
                str[count] = '\0';
                size = atoi(str);
            }
            count =0;
            break;
        //}else
        //if(ch == ' '){
        //    str[count] = '\0';
        //    count =0;
        }else{
            str[count] = ch;
            ++count;
        }
    }
    cout << "matrix size = " << size << endl;
    
    Matrix A(size, size);
    int countrow =0;
    int countcol =0;
    count =0;
    while(stream.get(ch)){
        if(ch == '\n'){
            if(count){
                if(countrow < size && countcol < size){
                    str[count] = '\0';
                    A[countrow][countcol] = atof(str);
                }
                ++countrow;
            }
            count =0;
            countcol =0;
        }else
        if(ch == ' ' || ch == '\t'){
            if(count){
                if(countrow < size && countcol < size){
                    str[count] = '\0';
                    A[countrow][countcol] = atof(str);
                }
                ++countcol;
            }
            count =0;
        }else{
            str[count] = ch;
            ++count;
        }
    }
    if(count){
        str[count] = '\0';
        //list.addLast(Integer::parseInt(String(str)));
    }
    
    stream.close();
    //===========================================================
    
    A.show();
    Matrix eigA =A;
    Matrix Q = eigA.eigenvalue();
    Q.show();
    eigA.show();
    
    Matrix I(size, size);
    I.identity();
    cout << endl;
    for(int i=0; i< size; ++i){
        Matrix T = A + -eigA[i][0] *I;
        double det = T.determinant();
        if(det > 1e-3){
            Matrix Tinverse =T;
            Tinverse.inverse();
            det = (T + eigA[i][1]*eigA[i][1] *Tinverse).determinant();
        }
        cout << det << ", ";
    }
    cout << endl;
    
    Matrix Qt = Q;
    Qt.transpose();
    (Qt*A*Q).show();
    
    return 0;
}
//===========================================================
//===========================================================


