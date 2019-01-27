

//===========================================================
//===========================================================
#include <iostream>

#include "../base/math/Diffusion.h"
#include "../base/math/Diffusion_cpp.h"
#include "../base/math/Poisson.h"
#include "../base/math/Poisson_cpp.h"

using namespace std;

//===========================================================
//===========================================================
int main()
{
    
    const double DISTANCE =0.001;
    const double LENGTH =0.15;
    const int NUMDIV =150;
    
    const double dl = LENGTH /NUMDIV;
    const double dA = dl *dl;
    
    const int NUMRAD =4;
    const int NUMCON = NUMDIV *NUMDIV;
    const int NUMTOTAL = NUMRAD +NUMCON;
    
    double** CF = new double*[NUMCON];
    for(int i=0; i< NUMCON; ++i){
        CF[i] = new double[NUMRAD];
    }
    
    
    
    
    //===========================================================
    {
        const double X0[] ={0, 0, 0, 0.1};
        const double X1[] ={0.15, 0.15, 0.1, 0.15};
        const double Y0[] ={0.1, 0.05, 0, 0};
        const double Y1[] ={0.15, 0.1, 0.05, 0.05};
        
        double dd = DISTANCE *DISTANCE;
        
        double** r = new double*[NUMDIV];
        for(int i=0; i< NUMDIV; ++i){
            r[i] = new double[i+1];
            
            for(int j=0; j< i+1; ++j){
                double x = (i +0.5) *dl;
                double y = (j +0.5) *dl;
                r[i][j] = 1 /sqrt(x*x + y*y + dd);
                r[i][j] *= r[i][j];
                
                //cout << r[i][j] << " ";
            }
            
            //cout << endl;
        }
        
        
        for(int j=0; j< NUMRAD; ++j){
            int x;
            x = X0[j] /dl;
            cout << x << ", ";
            x = X1[j] /dl;
            cout << x << ", ";
            x = Y0[j] /dl;
            cout << x << ", ";
            x = Y1[j] /dl;
            cout << x << ", ";
            cout << endl;
        }
        
        
        for(int i=0; i< NUMCON; ++i){
            for(int j=0; j< NUMRAD; ++j){
                CF[i][j] =0;
                
                
                for(int x= X0[j] /dl; x< X1[j] /dl; ++x){
                    for(int y= Y0[j] /dl; y< Y1[j] /dl; ++y){
                        //cout << x << ", " << y << endl;
                    }
                }
                
                
                
                
                //cout << r[i][j] << " ";
            }
            
            //cout << endl;
        }
    }
    
    
    
    
    
    
    
    
    
    
    
    /*
    
    double dt = 0.001;
    int numStep =100;
    unsigned int numx[2];
    numx[0] = 16;
    numx[1] = 16;
    double dx[2];
    dx[0] = 0.01;
    dx[1] = 0.01;
    double vars[numx[0] *numx[1]];
    double source[numx[0] *numx[1]];
    for(int i=0; i< numx[0] *numx[1]; ++i){
        vars[i] = 20;
        source[i] = 100;
    }
    
    unsigned int numBCD = 2 *(numx[1] -2);
    unsigned int indexBCD[numBCD];
    int count =0;
    for(int i=0; i< numx[0]; ++i){
        //indexBCD[count] = i;
        //++count;
    }
    for(int i=1; i< numx[1] -1; ++i){
        indexBCD[count] = numx[0] *i;
        ++count;
        indexBCD[count] = numx[0] *(i+1) -1;
        ++count;
    }
    for(int i= numx[0] *(numx[1] -1); i< numx[0] *numx[1]; ++i){
        //indexBCD[count] = i;
        //++count;
    }
    
    double bcD[numBCD];
    for(int i=0; i< numBCD; ++i){
        bcD[i] = 0;
    }
    
    unsigned int numBCN[2];
    numBCN[0] = 0;
    numBCN[1] = 2 *numx[0];
    unsigned int* indexBCN[2];
    indexBCN[0] = new unsigned int[numBCN[0]];
    indexBCN[1] = new unsigned int[numBCN[1]];
    double* bcN[2];
    bcN[0] = new double[numBCN[0]];
    bcN[1] = new double[numBCN[1]];
    for(int i=0; i< numx[0]; ++i){
        indexBCN[1][i] = i;
        indexBCN[1][i+numx[0]] = i+(numx[1]-1)*numx[0];
        bcN[1][i] = 0;
        bcN[1][i+numx[0]] = 0;
    }
    double coefficients[2];
    coefficients[0] =1;
    coefficients[1] =1;
    
    
    unsigned long long time = GetTickCount();
    
    
    for(int k=0; k< 1; ++k){
        for(int i=0; i< numx[0] *numx[1]; ++i){
            //source[i] = (10 -vars[i]);
        }
        Diffusion::fdm_2d(
            dt,
            numStep,
            numx,
            dx,
            vars,
            source,
            numBCD,
            indexBCD,
            bcD,
            numBCN,
            indexBCN,
            bcN,
            coefficients);
    }
    time = GetTickCount() -time;
    
    
    
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    //cout.setf(ios::showpos);
    cout.setf(ios::unitbuf);
    cout.setf(ios::scientific);
    cout.precision(2);
    for(int j=0; j< numx[1]; ++j){
        for(int i=0; i< numx[0]; ++i){
            cout << vars[j*numx[0] +i] << "  ";
        }
        cout << endl;
    }
    cout << time << endl;
    
    */
    
    
    
    return 0;
}
//===========================================================
//===========================================================

