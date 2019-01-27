

#ifndef _base_math_analysis_calculus_Poisson_cpp
#define _base_math_analysis_calculus_Poisson_cpp


//===========================================================
//===========================================================
#include "Poisson.h"
#include "Function.h"
#include "../../lang/Math.h"
#include "../../lang/Math_cpp.h"
//#include <math.h>

//===========================================================
//===========================================================
void Poisson::fdm_1d(
    int numx,
    double dx,
    double vars[],
    double source[],
    int numBCD,
    int indexBCD[],
    double bcDirichlet[],
    int numBCN,
    int indexBCN[],
    double bcNeumann[])
{
    
    bool matrix[numx][3];
    for(int i=0; i< numx; ++i){
        matrix[i][0] = true;
        matrix[i][1] = true;
        matrix[i][2] = true;
    }
    for(int i=0; i< numBCD; ++i){
        vars[indexBCD[i]] = bcDirichlet[i];
    }
    
    double omega = 1.6;
    double emax = 1;
    double epsilon = 1e-6;
    //int k=0;
    while(emax > epsilon){
        //++k;
        //if(k>300){ break; }
        emax =0;
        
        int ctBCD =0;
        int ctBCN =0;
        
        for(int i=0; i< numx; ++i){
            if(ctBCD < numBCD && i == indexBCD[ctBCD]){
                ++ctBCD;
                continue;
            }else
            if(ctBCN < numBCN && i == indexBCN[ctBCN]){
                vars[i] = i==0?
                    vars[i+2] -2 *dx *bcNeumann[ctBCN]:
                    vars[i-2] +2 *dx *bcNeumann[ctBCN];
                ++ctBCN;
                continue;
            }else{
                
                double diff = (
                        dx *dx *source[i]
                        -matrix[i][0] *vars[i-1]
                        -matrix[i][2] *vars[i+1])
                    *matrix[i][1] *-0.5
                    -vars[i];
                
                vars[i] += omega *diff;
                if(emax < Math::abs(diff)){
                    emax = Math::abs(diff);
                }
            }
        }
    }
    //cout << k << endl;
}
//===========================================================
//===========================================================
void Poisson::fdm_2d(
    int numx[2],
    double dx,
    double vars[],
    double source[],
    int numBCD,
    int indexBCD[],
    double bcDirichlet[],
    int numBCN[2],
    int* indexBCN[2],
    double* bcNeumann[2])
{
    
    bool matrix[numx[0] *numx[1]][5];
    for(int i=0; i< numx[0] *numx[1]; ++i){
        matrix[i][0] = true;
        matrix[i][1] = true;
        matrix[i][2] = true;
        matrix[i][3] = true;
        matrix[i][4] = true;
    }
    
    bool flagBoundary[numx[0] *numx[1]];
    for(int i=0; i< numx[0] *numx[1]; ++i){
        flagBoundary[i] = false;
    }
    for(int i=0; i< numBCD; ++i){
        flagBoundary[indexBCD[i]] = true;
    }
    for(int i=0; i< numBCN[0]; ++i){
        flagBoundary[indexBCN[0][i]] = true;
    }
    for(int i=0; i< numBCN[1]; ++i){
        flagBoundary[indexBCN[1][i]] = true;
    }
    
    for(int i=0; i< numBCD; ++i){
        vars[indexBCD[i]] = bcDirichlet[i];
    }
    
    double omega = 1.6;
    double epsilon = 1e-6;
    double emax = 1;
    int ctBCD =0;
    int ctBCN[2];
    //int k=0;
    while(emax > epsilon){
        //++k;
        //if(k>300){ break; }
        emax =0;
        
        ctBCD =0;
        ctBCN[0] =0;
        ctBCN[1] =0;
        
        for(int i=0; i< numx[0] *numx[1]; ++i){
            //Dirichlet
            if(ctBCD < numBCD && i == indexBCD[ctBCD]){
                ++ctBCD;
                continue;
            }
            
            //Neumann x direction
            if(ctBCN[0] < numBCN[0] && i == indexBCN[0][ctBCN[0]]){
                vars[i] = i %numx[0] == 0 || flagBoundary[i-1]?
                    vars[i+2] -2 *dx *bcNeumann[0][ctBCN[0]]:
                    vars[i-2] +2 *dx *bcNeumann[0][ctBCN[0]];
                ++ctBCN[0];
            }
            //Neumann y direction
            if(ctBCN[1] < numBCN[1] && i == indexBCN[1][ctBCN[1]]){
                vars[i] = i< numx[0] || flagBoundary[i-numx[0]]?
                    vars[i+2*numx[0]] -2 *dx *bcNeumann[1][ctBCN[1]]:
                    vars[i-2*numx[0]] +2 *dx *bcNeumann[1][ctBCN[1]];
                ++ctBCN[1];
            }
            
            //succesive over relaxation
            if(!flagBoundary[i]){
                double diff = (
                        dx *dx *source[i]
                        -matrix[i][0] *vars[i-numx[0]]
                        -matrix[i][1] *vars[i-1]
                        -matrix[i][3] *vars[i+1]
                        -matrix[i][4] *vars[i+numx[0]])
                    *matrix[i][2] *-0.25
                    -vars[i];
                
                vars[i] += omega *diff;
                if(emax < Math::abs(diff)){
                    emax = Math::abs(diff);
                }
            }
        }
    }
}
//===========================================================
//===========================================================
void Poisson::fdm_3d(
    int numx[3],
    double dx,
    double vars[],
    double source[],
    int numBCD,
    int indexBCD[],
    double bcDirichlet[],
    int numBCN[3],
    int* indexBCN[3],
    double* bcNeumann[3])
{
    
    bool flagBoundary[numx[0] *numx[1] *numx[2]];
    for(int i=0; i< numx[0] *numx[1] *numx[2]; ++i){
        flagBoundary[i] = false;
    }
    for(int i=0; i< numBCD; ++i){
        flagBoundary[indexBCD[i]] = true;
    }
    for(int i=0; i< numBCN[0]; ++i){
        flagBoundary[indexBCN[0][i]] = true;
    }
    for(int i=0; i< numBCN[1]; ++i){
        flagBoundary[indexBCN[1][i]] = true;
    }
    for(int i=0; i< numBCN[2]; ++i){
        flagBoundary[indexBCN[2][i]] = true;
    }
    
    for(int i=0; i< numBCD; ++i){
        vars[indexBCD[i]] = bcDirichlet[i];
    }
    
//cout << numBCD << endl;
//for(int k=0; k< numx[2]; ++k){
//    for(int j=0; j< numx[1]; ++j){
//        for(int i=0; i< numx[0]; ++i){
//            cout << flagBoundary[k*numx[0]*numx[1] +j*numx[0] +i] << "";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
    double omega = 1.6;
    double epsilon = 1e-6;
    double emax = 1;
    int ctBCD =0;
    int ctBCN[3];
    //int k=0;
    while(emax > epsilon){
        //++k;
        //if(k>300){ break; }
        emax =0;
        
        ctBCD =0;
        ctBCN[0] =0;
        ctBCN[1] =0;
        ctBCN[2] =0;
        
        for(int i=0; i< numx[0] *numx[1] *numx[2]; ++i){
            //Dirichlet
            if(ctBCD < numBCD && i == indexBCD[ctBCD]){
                ++ctBCD;
                continue;
            }
            
            //Neumann x direction
            if(ctBCN[0] < numBCN[0] && i == indexBCN[0][ctBCN[0]]){
                vars[i] = i %numx[0] == 0
                    || flagBoundary[i-1]?
                    vars[i+2] -2 *dx *bcNeumann[0][ctBCN[0]]:
                    vars[i-2] +2 *dx *bcNeumann[0][ctBCN[0]];
                ++ctBCN[0];
            }
            //Neumann y direction
            if(ctBCN[1] < numBCN[1] && i == indexBCN[1][ctBCN[1]]){
                vars[i] = i %(numx[0]*numx[1]) == 0
                    || flagBoundary[i-numx[0]]?
                    vars[i+2*numx[0]] -2 *dx *bcNeumann[1][ctBCN[1]]:
                    vars[i-2*numx[0]] +2 *dx *bcNeumann[1][ctBCN[1]];
                ++ctBCN[1];
            }
            //Neumann z direction
            if(ctBCN[2] < numBCN[2] && i == indexBCN[2][ctBCN[2]]){
                vars[i] = i< numx[0]*numx[1]
                    || flagBoundary[i-numx[0]*numx[1]]?
                    vars[i+2*numx[0]*numx[1]] -2 *dx *bcNeumann[2][ctBCN[2]]:
                    vars[i-2*numx[0]*numx[1]] +2 *dx *bcNeumann[2][ctBCN[2]];
                ++ctBCN[2];
            }
            
            //succesive over relaxation
            if(!flagBoundary[i]){
                double diff = (
                        dx *dx *source[i]
                        -vars[i-numx[0]*numx[1]]
                        -vars[i-numx[0]]
                        -vars[i-1]
                        -vars[i+1]
                        -vars[i+numx[0]]
                        -vars[i+numx[0]*numx[1]])
                    /-6
                    -vars[i];
                
                vars[i] += omega *diff;
                if(emax < Math::abs(diff)){
                    emax = Math::abs(diff);
                }
            }
        }
    }
}
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_Poisson_cpp

