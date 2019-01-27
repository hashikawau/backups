

#include <iostream>
using namespace std;

int main()
{
    int numControlled =6;
    double xc0[] ={
        0,
        0, 0.05,
        0, 0.05, 0.1};
    double xc1[] ={
        0.05,
        0.05, 0.1,
        0.05, 0.1, 0.15};
    double yc0[] ={
        0,
        0.05, 0.05,
        0.1, 0.1, 0.1};
    double yc1[] ={
        0.05,
        0.1, 0.1,
        0.15, 0.15, 0.15};
    
    int numOperating =1;
    double xo0[] ={
        0};
    double xo1[] ={
        0.05};
    double yo0[] ={
        0};
    double yo1[] ={
        0.05};
    
    double distance =0.01;
    
    int numxc =110;
    int numxo =110;
    int numyc =110;
    int numyo =110;
    
    
    double F[numControlled *numOperating];
    double tempf;
    double tempx;
    double tempy;
    for(int i=0; i< numControlled; ++i){
        double dxc = (xc1[i] -xc0[i]) /numxc;
        double dyc = (yc1[i] -yc0[i]) /numyc;
        
        for(int j=0; j< numOperating; ++j){
            double dxo = (xo1[j] -xo0[j]) /numxo;
            double dyo = (yo1[j] -yo0[j]) /numyo;
            
            F[i *numOperating +j] =0;
            for(int ixc =0; ixc <numxc; ++ixc){
                for(int iyc =0; iyc <numyc; ++iyc){
                    
                    for(int jxo =0; jxo <numxo; ++jxo){
                        for(int jyo =0; jyo <numyo; ++jyo){
                            
                            tempx =  xc0[i] +(ixc +0.5) *dxc;
                            tempx -= xo0[j] +(jxo +0.5) *dxo;
                            tempx /= distance;
                            tempx *= tempx;
                            
                            tempy =  yc0[i] +(iyc +0.5) *dyc;
                            tempy -= yo0[j] +(jyo +0.5) *dyo;
                            tempy /= distance;
                            tempy *= tempy;
                            
                            tempf = 1 /(tempx +tempy +1);
                            F[i *numOperating +j] += tempf *tempf;
                        }
                    }
                }
            }
            F[i *numOperating +j] *=
                dxc *dyc *dxo *dyo
                /(3.1415926535 *distance *distance);
            cout << " F[" << i << "][" << j;
            cout << "]= " << F[i *numOperating +j] << endl;
        }
    }
    
    /*
    for(int i=0; i< numControlled; ++i){
        for(int j=0; j< numOperating; ++j){
            cout << F[i *numOperating +j];
            cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
    */
    
    cout << 2 *(F[0]+F[1]+F[3]) +(F[1]+F[0]+F[1]) << "  ";
    cout << 2 *(F[1]+F[2]+F[4]) +(F[2]+F[1]+F[2]) << "  ";
    cout << (F[3]+F[4]) +(F[4]+F[3]) +(F[4]+F[5]) << "  ";
    cout << (F[5]) +(F[4]) +(F[3]) << endl;
    
    cout << 2 *(F[1]+F[2]+F[4]) +(F[2]+F[1]+F[2]) << "  ";
    cout << 2 *(F[0]+F[1]+F[3]) +(F[1]+F[0]+F[1]) << "  ";
    cout << (F[1]+F[2]) +(F[2]+F[1]) +(F[4]+F[2]) << "  ";
    cout << (F[4]) +(F[2]) +(F[1]) << endl;
    
    cout << (F[3]+F[4]) +(F[4]+F[3]) +(F[5]+F[4]) << "  ";
    cout << (F[1]+F[2]) +(F[2]+F[1]) +(F[4]+F[2]) << "  ";
    cout << (F[0]+F[1]) +(F[1]+F[0]) << "  ";
    cout << (F[3]) +(F[1]) << endl;
    
    cout << (F[5]) +(F[4]) +(F[3]) << "  ";
    cout << (F[4]) +(F[2]) +(F[1]) << "  ";
    cout << (F[3]) +(F[1]) << "  ";
    cout << (F[0]) << endl;
    
    cout << endl;
    cout << endl;
    
    cout << (F[0]+F[1]+F[3]) << "  ";
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[3]+F[4]) << "  ";
    cout << (F[5]) << "  ";
    cout << endl;
    cout << (F[1]+F[0]+F[1]) << "  ";
    cout << (F[2]+F[1]+F[2]) << "  ";
    cout << (F[4]+F[3]) << "  ";
    cout << (F[4]) << "  ";
    cout << endl;
    cout << (F[0]+F[1]+F[3]) << "  ";
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[4]+F[5]) << "  ";
    cout << (F[3]) << "  ";
    cout << endl;
    
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[0]+F[1]+F[3]) << "  ";
    cout << (F[1]+F[2]) << "  ";
    cout << (F[4]) << "  ";
    cout << endl;
    cout << (F[2]+F[1]+F[2]) << "  ";
    cout << (F[1]+F[0]+F[1]) << "  ";
    cout << (F[1]+F[2]) << "  ";
    cout << (F[2]) << "  ";
    cout << endl;
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[0]+F[1]+F[3]) << "  ";
    cout << (F[2]+F[4]) << "  ";
    cout << (F[1]) << "  ";
    cout << endl;
    
    cout << (F[3]+F[4]+F[5]) << "  ";
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[0]+F[1]) << "  ";
    cout << (F[3]) << "  ";
    cout << endl;
    cout << (F[4]+F[3]+F[4]) << "  ";
    cout << (F[2]+F[1]+F[2]) << "  ";
    cout << (F[0]+F[1]) << "  ";
    cout << (F[1]) << "  ";
    cout << endl;
    cout << (F[3]+F[4]+F[5]) << "  ";
    cout << (F[1]+F[2]+F[4]) << "  ";
    cout << (F[1]+F[3]) << "  ";
    cout << (F[0]) << "  ";
    cout << endl;
    
    
    
    return 0;
}

/*
Intensity of radiation[W/m^2] = sigma * T1^4 / PI
Solid angle (projected) = A2 /r^2 *cos(a2)
Radiation = I *S *(A1 *cos(a1))
          = sigma * T1^4 *A1 *F,1->2

F'ij = Ai *F,i->j = Aj *F,j->i


dx = 0.01
0.00764312  0.00160863  2.11026e-05  9.75995e-06
0.00160863  0.00764312  0.00119992  0.000551495
1.49156e-05  0.00086101  0.00407676  2.39104e-05
1.4458e-05  0.000802012  0.00181139  0.00272966


dx = 0.001
0.00595623  0.000651629  1.20243e-05  5.44399e-06
0.000651629  0.00595623  0.000447525  0.000211049
8.63083e-06  0.000325814  0.00296601  1.30845e-05
8.63083e-06  0.000325814  0.00109974  0.00193903


dx = 0.0005
0.00588583  0.000614361  1.16343e-05  5.25714e-06
0.000614361  0.00588583  0.00041987  0.000197791
8.39537e-06  0.00030718  0.00293055  1.28552e-05
8.39537e-06  0.00030718  0.00106651  0.00190664

*/
