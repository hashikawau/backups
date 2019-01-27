

//===========================================================
//===========================================================
#include <iostream>
#include "../base/math/MathFunction.h"
#include "../base/math/MathFunction_cpp.h"
//#include <windows.h>
//===========================================================
//===========================================================
int main()
{
    /*
    MathConstant mc0;
    cout << mc0.getSymbol() << " = ";
    cout << mc0.getValue() << endl;
    
    MathConstant mc1(String("A0"), 3);
    cout << mc1.getSymbol() << " = ";
    cout << mc1.getValue() << endl;
    
    MathConstant mc2(String("A1"));
    cout << mc2.getSymbol() << " = ";
    cout << mc2.getValue() << endl;
    
    MathConstant mc3(9.8);
    cout << mc3.getSymbol() << " = ";
    cout << mc3.getValue() << endl;
    */
    
    
    PointerObject<MathVariable> vars;
    vars.addLast(new MathVariable(String("x0")));
    vars.addLast(new MathVariable(String("x1")));
    vars.addLast(new MathVariable(String("x2")));
    
    cout << (*vars[0]).getSymbol() << " =" << endl;
    for(int i=0; i< 11; ++i){
        cout << "  " << (*vars[0]).getValue() << endl;
        (*vars[0]).setValue((*vars[0]).getValue() +0.1);
    }
    cout << endl << endl;
    
    
    
    PointerObject<MathFunction> sums;
    sums.addLast(new MathSummation);
    (*sums[0]).MathSummation::set(*vars[0]);
    (*sums[0]).MathSummation::set(*vars[1]);
    (*sums[0]).MathSummation::set(*vars[2]);
    
    sums.addLast(new MathSummation);
    (*sums[1]).MathSummation::set(*vars[0]);
    (*sums[1]).MathSummation::set(*vars[1]);
    (*sums[1]).MathSummation::set(*vars[2]);
    //(*sums[1]) = (*sums[0]);
    
    (*sums[0]).MathSummation::set(*sums[1]);
    cout << (*sums[0]).getSymbol() << endl;
    cout << (*sums[1]).getSymbol() << endl;
    cout << endl << endl;
    
    
    
    PointerObject<MathFunction> pros;
    pros.addLast(new MathProduct);
    (*pros[0]).MathProduct::set(*vars[0]);
    (*pros[0]).MathProduct::set(*vars[1]);
    (*pros[0]).MathProduct::set(*vars[2]);
    
    pros.addLast(new MathProduct);
    (*pros[1]).MathProduct::set(*vars[0]);
    (*pros[1]).MathProduct::set(*vars[1]);
    (*pros[1]).MathProduct::set(*vars[2]);
    //(*pros[1]) = (*pros[0]);
    
    (*pros[0]).MathProduct::set(*sums[1]);
    cout << (*pros[0]).getSymbol() << endl;
    cout << (*pros[1]).getSymbol() << endl;
    cout << endl << endl;
    
    
    
    PointerObject<MathExponent> exps;
    exps.addLast(new MathExponent);
    (*exps[0]).MathExponent::set(*sums[0], *pros[1]);
    cout << (*exps[0]).getSymbol() << endl;
    cout << endl << endl;
    
    
    
    
    
    while(char ch =1){
        cout << "e: exit" << endl;
        cout << "v: varible" << endl;
        cout << "f: " << endl;
        cout << ": " << endl;
        
        cin >> ch;
        if(ch = 'e') break;
    }
    
    
    return 0;
}
//===========================================================
//===========================================================


