

#include <iostream>

using namespace std;





int main()
{
    
    int numControlled =4;
    double xc[] ={0, 0, 0, 0.075};
    double yc[] ={0.1, 0.05, 0, 0};
    double zc[] ={-0.005, -0.005, -0.005, -0.005};
    double wc[] ={0.15, 0.15, 0.075, 0.075};
    double hc[] ={0.05, 0.05, 0.05, 0.05};
    double tc[] ={0.005, 0.005, 0.005, 0.005};
    
    int numOperating =4;
    double xo[] ={0, 0, 0, 0.1};
    double yo[] ={0.1, 0.05, 0, 0};
    double zo[] ={0.005, 0.005, 0.005, 0.005};
    double wo[] ={0.15, 0.15, 0.1, 0.05};
    double ho[] ={0.05, 0.05, 0.05, 0.05};
    double to[] ={0.00002, 0.00002, 0.00002, 0.00002};
    
    double dx =0.001;
    
    
    /*
    int numControlled =1;
    double xc[] ={0};
    double yc[] ={0};
    double zc[] ={0};
    double wc[] ={1};
    double hc[] ={1};
    double tc[] ={1};
    
    int numOperating =1;
    double xo[] ={0};
    double yo[] ={0};
    double zo[] ={1};
    double wo[] ={1};
    double ho[] ={1};
    double to[] ={1};
    
    double dx =0.1;
    */
    
    double F[numControlled *numOperating];
    double tempx;
    double tempy;
    double tempz;
    for(int i=0; i< numControlled; ++i){
        for(int j=0; j< numOperating; ++j){
            
            F[i *numOperating +j] =0;
            tempz = (zc[i] -zo[j]);
            tempz *= tempz;
//cout << tempz << endl;
            for(int nxi =0; nxi <wc[i] /dx; ++nxi){
                for(int nyi =0; nyi <hc[i] /dx; ++nyi){
                    
                    for(int nxj =0; nxj <wo[j] /dx; ++nxj){
                        for(int nyj =0; nyj <ho[j] /dx; ++nyj){
/*
cout
    << nxi << " "
    << nyi << " "
    << nxj << " "
    << nyj << " "
    << endl;
*/
                            tempx =  xc[i] +(nxi +0.5) *dx;
                            tempx -= xo[j] +(nxj +0.5) *dx;
                            tempx *= tempx;
//cout << tempx << endl;
                            tempy =  yc[i] +(nyi +0.5) *dx;
                            tempy -= yo[j] +(nyj +0.5) *dx;
                            tempy *= tempy;
//cout << tempy << endl;
                            F[i *numOperating +j] +=
                                dx*dx*dx*dx
                                /(tempx +tempy +tempz)
                                /(tempx +tempy +tempz);
                        }
                    }
                }
            }
            F[i *numOperating +j] *= tempz / 3.1415926535;
        }
    }
    
    for(int i=0; i< numControlled; ++i){
        for(int j=0; j< numOperating; ++j){
            cout << F[i *numOperating +j];
            cout << "  ";
        }
        cout << endl;
    }
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
