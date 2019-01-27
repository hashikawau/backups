

//===========================================================
//===========================================================
//#include <iostream>
//using namespace std;

#include <iostream.h>
#include <fstream.h>
#include <math.h>
#include "Matrix.h"
//===========================================================
//===========================================================

//===========================================================
//===========================================================
int main(int argc, char* argv[])
{
    //===========================================================
    ifstream stream;
    if(argc < 2){
        cout << "error1" << endl;
        return 1;
    }
    
    stream.open(argv[1]);
    cout << (bool)stream << endl;
    if(!stream){
        cout << "error2" << endl;
        return 1;
    }
    /*
    char ch;
    char str[10];
    LinkedList<int> list;
    int count =0;
    while(stream.get(ch)){
        if(ch == '\n'){
            if(count){
                str[count] = '\0';
                list.addLast(Integer::parseInt(String(str)));
            }
            list.addLast(0);
            count =0;
        }else
        if(ch == ' '){
            str[count] = '\0';
            list.addLast(Integer::parseInt(String(str)));
            count =0;
        }else{
            str[count] = ch;
            ++count;
        }
    }
    if(count){
        str[count] = '\0';
        list.addLast(Integer::parseInt(String(str)));
    }
    list.addLast(0);
    */
    stream.close();
    //===========================================================
    
    
    return 0;
}
//===========================================================
//===========================================================


