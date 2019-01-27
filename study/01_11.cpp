//#include <iostream.h>
#include "01_11.h"

int main()
{
    C1<int>  ci;
    C1<char> cc;
    C1<float>     c;
    
    cout << f(999) << endl;
    
    ci.swap(ci);
    ci.show();
    cc.show();
    
    cc.show2();
    cc.show2(3);
    cc.show3();
    cc.show3(5);
    
    double iii = 43529454.350;
    int ii = (int)iii;
    cout << ii;
    
    
    //cc.show();

    return 0;
}
