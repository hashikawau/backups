

//===========================================================
//===========================================================
#include <iostream>
#include "../util/Random.h"
#include "../util/Random_cpp.h"
using namespace std;
//===========================================================
//===========================================================
int main()
{
    Random r(1);
    long double d=0;
    for(int i=0; i< 10000; ++i){
        double t = r.nextDouble();
        d += t;
        cout << d/(i+1) << ", " << t << endl;
    }
    
    return 0;
}
//===========================================================
//===========================================================

