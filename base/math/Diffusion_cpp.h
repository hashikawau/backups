

#ifndef _base_math_analysis_calculus_Diffusion_cpp
#define _base_math_analysis_calculus_Diffusion_cpp


//===========================================================
//===========================================================
#include "Diffusion.h"
#include "Function.h"
#include "../../lang/Math.h"
#include "../../lang/Math_cpp.h"
//#include <math.h>

//===========================================================
//===========================================================
void Diffusion::fdm_1d(
    double dt,
    int numStep,
    unsigned int numx,
    double dx,
    double vars[],
    double source[],
    unsigned int numBCD,
    unsigned int indexBCD[],
    double bcDirichlet[],
    unsigned int numBCN,
    unsigned int indexBCN[],
    double bcNeumann[],
    double coefficients)
{
    unsigned long long numTotal = numx;
    
    double altCoe[3];
    altCoe[0] = 0.5 *dt *coefficients /(dx *dx);
    double altCoeMinus = 1 -2 *altCoe[0];
    double altCoePlus = 1 +2 *altCoe[0];
    altCoeMinus /= altCoePlus;
    altCoe[0] /= altCoePlus;
    
    bool* flagBC = new bool[numTotal];
    for(int i=0; i< numTotal; ++i){
        flagBC[i] = false;
    }
    for(int i=0; i< numBCD; ++i){
        vars[indexBCD[i]] = bcDirichlet[i];
        flagBC[indexBCD[i]] = true;
    }
    for(int i=0; i< numBCN; ++i){
        flagBC[indexBCN[i]] = true;
    }
//cout << numBCD << endl;
//for(int k=0; k< numx[2]; ++k){
//    for(int j=0; j< numx[1]; ++j){
//        for(int i=0; i< numx[0]; ++i){
//            cout << flagBC[k*numx[0]*numx[1] +j*numx[0] +i] << "";
//        }
//        cout << endl;
//    }
//    cout << endl;
//}
    
    double omega = 1.6;
    double epsilon = 1e-6;
    double emax;
    int ctBCD;
    int ctBCN[3];
    double diff;
    double* rhs = new double[numTotal];
    for(int k=0; k< numStep; ++k){
        for(int i=0; i< numTotal; ++i){
            if(!flagBC[i]){
                rhs[i] = dt *source[i] /altCoePlus;
                rhs[i] += altCoeMinus *vars[i];
                rhs[i] += altCoe[0] *(vars[i+1] +vars[i-1]);
            }
        }
        
        emax =1;
        while(emax > epsilon){
            emax =0;
            
            ctBCD =0;
            ctBCN[0] =0;
            for(int i=0; i< numTotal; ++i){
                //Dirichlet
                if(ctBCD < numBCD && i == indexBCD[ctBCD]){
                    ++ctBCD;
                }
                
                //Neumann x direction
                if(ctBCN[0] < numBCN && i == indexBCN[ctBCN[0]]){
                    vars[i] = i==0?
                        vars[i+2] -2 *dx *bcNeumann[ctBCN[0]]:
                        vars[i-2] +2 *dx *bcNeumann[ctBCN[0]];
                    ++ctBCN[0];
                }
                
                //succesive over relaxation
                if(!flagBC[i]){
                    diff = rhs[i];
                    diff += altCoe[0] *(vars[i+1] +vars[i-1]);
                    
                    diff -= vars[i];
                    vars[i] += omega *diff;
                    emax = Math::max(emax, Math::abs(diff));
                }
            }
        }
    }
    
    delete [] flagBC;
    delete [] rhs;
}
//===========================================================
//===========================================================
void Diffusion::fdm_2d(
    double dt,
    int numStep,
    unsigned int numx[2],
    double dx[2],
    double vars[],
    double source[],
    unsigned int numBCD,
    unsigned int indexBCD[],
    double bcDirichlet[],
    unsigned int numBCN[2],
    unsigned int* indexBCN[2],
    double* bcNeumann[2],
    double coefficients[2])
{
    int numDim =2;
    unsigned long long numTotal =1;
    double altCoe[numDim];
    for(int i=0; i< numDim; ++i){
        numTotal *= numx[i];
        altCoe[i] = 0.5 *dt *coefficients[i] /(dx[i] *dx[i]);
    }
    double altCoeMinus =1;
    double altCoePlus =1;
    for(int i=0; i< numDim; ++i){
        altCoeMinus += -2 *altCoe[i];
        altCoePlus += 2 *altCoe[i];
    }
    for(int i=0; i< numDim; ++i){
        altCoe[i] /= altCoePlus;
    }
    altCoeMinus /= altCoePlus;
    
    bool* flagBC = new bool[numTotal];
    for(int i=0; i< numTotal; ++i){
        flagBC[i] = false;
    }
    for(int i=0; i< numBCD; ++i){
        vars[indexBCD[i]] = bcDirichlet[i];
        flagBC[indexBCD[i]] = true;
    }
    for(int i=0; i< numBCN[0]; ++i){
        flagBC[indexBCN[0][i]] = true;
    }
    for(int i=0; i< numBCN[1]; ++i){
        flagBC[indexBCN[1][i]] = true;
    }
    
    double omega = 1.6;
    double epsilon = 1e-6;
    double emax;
    int ctBCD;
    int ctBCN[numDim];
    double diff;
    double* rhs = new double[numTotal];
    for(int k=0; k< numStep; ++k){
        for(int i=0; i< numTotal; ++i){
            if(!flagBC[i]){
                rhs[i] = dt *source[i] /altCoePlus;
                rhs[i] += altCoeMinus *vars[i];
                rhs[i] += altCoe[0] *(vars[i+1] +vars[i-1]);
                rhs[i] += altCoe[1] *(vars[i+numx[0]] +vars[i-numx[0]]);
            }
        }
        
        emax =1;
        while(emax > epsilon){
            emax =0;
            
            ctBCD =0;
            for(int i=0; i< numDim; ++i){
                ctBCN[i] =0;
            }
            for(int i=0; i< numTotal; ++i){
                //Dirichlet
                if(ctBCD < numBCD && i == indexBCD[ctBCD]){
                    ++ctBCD;
                }
                
                //Neumann x direction
                if(ctBCN[0] < numBCN[0] && i == indexBCN[0][ctBCN[0]]){
                    vars[i] = i %numx[0] == 0 || flagBC[i-1]?
                        vars[i+2] -2 *dx[0] *bcNeumann[0][ctBCN[0]]:
                        vars[i-2] +2 *dx[0] *bcNeumann[0][ctBCN[0]];
                    ++ctBCN[0];
                }
                //Neumann y direction
                if(ctBCN[1] < numBCN[1] && i == indexBCN[1][ctBCN[1]]){
                    vars[i] = i< numx[0] || flagBC[i-numx[0]]?
                        vars[i+2*numx[0]] -2 *dx[1] *bcNeumann[1][ctBCN[1]]:
                        vars[i-2*numx[0]] +2 *dx[1] *bcNeumann[1][ctBCN[1]];
                    ++ctBCN[1];
                }
                
                //succesive over relaxation
                if(!flagBC[i]){
                    diff = rhs[i];
                    diff += altCoe[0] *(vars[i+1] +vars[i-1]);
                    diff += altCoe[1] *(vars[i+numx[0]] +vars[i-numx[0]]);
                    
                    diff -= vars[i];
                    vars[i] += omega *diff;
                    emax = Math::max(emax, Math::abs(diff));
                }
            }
        }
    }
    
    delete [] flagBC;
    delete [] rhs;
}
//===========================================================
//===========================================================
/*
void Diffusion::fdm_2d(
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
    
    
    
    
    
    
    
    
    
    
    const double OMEGA   =1.6;
    const double EPSILON =1e-4;
    
    double hcap = _dt /_hcap /2;
    double hconX = _hconX *_dt /_hcap /_dx /_dx /2;
    double hconY = _hconY *_dt /_hcap /_dy /_dy /2;
    
    int numElem = _numx *_numy;
    
    double rhs[numElem];
    double emax;
    
    for(int k=0; k< numstep; ++k){
        setBC();
        for(int i=0; i< numElem; ++i){
            rhs[i] =
                (_heatSource[i] + _htransfer[i] *_ambTemp) *2 *hcap
                + _sparseMatrix[i][0] *hconY *_state[i-_numx]
                + _sparseMatrix[i][1] *hconX *_state[i-1]
                + (_sparseMatrix[i][2] *(hconX + hconY)
                    - _htransfer[i] *hcap + 1) *_state[i]
                + _sparseMatrix[i][3] *hconX *_state[i+1]
                + _sparseMatrix[i][4] *hconY *_state[i+_numx];
        }
        do{
            emax =0;
            for(int i=0, count=0; i< numElem; ++i){
                if(i >= _indexBounds[count]){
                    do{
                        ++count;
                    }while(i >= _indexBounds[count]);
                    continue;
                }
                double temp =
                    rhs[i]
                    + _sparseMatrix[i][0] *hconY *_state[i-_numx]
                    + _sparseMatrix[i][1] *hconX *_state[i-1]
                    + _sparseMatrix[i][3] *hconX *_state[i+1]
                    + _sparseMatrix[i][4] *hconY *_state[i+_numx];
                temp /= (
                    _sparseMatrix[i][2] *-(hconX + hconY)
                    +_htransfer[i] *hcap
                    +1);
                temp -= _state[i];
                _state[i] += OMEGA *temp;
                emax = Math::max(emax, temp);
            }
        }while(emax > EPSILON);
    }
}
//===========================================================
//===========================================================
void Diffusion::fdm_3d(
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

//===========================================================
//===========================================================
class TemperatureControl: public Laboratory
{
private:
    double _dt;
    double _dx;
    double _dy;
    double _dz;
    int _numx;
    int _numy;
    int _numz;
    int _countCalc;
    double _ambTemp;
    
    double _hcap;
    double _hconX;
    double _hconY;
    //double _hconZ;
    
    //double* _temperature;
    double* _heatSource;
    double* _htransfer;
    char** _sparseMatrix;
    
    int _numBounds;
    int* _indexBounds;
    
    void constructor();
    
public:
    TemperatureControl();
    virtual ~TemperatureControl();
    
    void init();
    void setBC(Variable& state);
    virtual void calcState(int numstep);
    
    
    
    void show(ostream& ofs);
    void showTemp(ostream& ofs);
};
//===========================================================
//===========================================================
TemperatureControl::TemperatureControl()
{
    constructor();
    init();
    //setBC();
}
TemperatureControl::~TemperatureControl()
{
    for(int i=0; i< _numx *_numy; ++i){
        delete [] _sparseMatrix[i];
    }
    delete [] _sparseMatrix;
    delete [] _htransfer;
    delete [] _indexBounds;
}
//===========================================================
//===========================================================
void TemperatureControl::constructor()
{
    _dt =0.025;
    _dx =1;
    _dy =1;
    //_dz =1;
    _numx =6;
    _numy =10;
    //_numz =1;
    _countCalc =0;
    _omega =1.6;
    _epsilon =1e-4;
    _ambTemp =0;
    
    _hcap =1;
    _hconX =1;
    _hconY =1;
    //_hconZ =1;
    
    int numElem = _numx *_numy;
    //_temperature = new double [numElem];
    _heatSource = new double [numElem];
    _htransfer = new double [numElem];
    
    _sparseMatrix = new char* [numElem];
    for(int i=0; i< numElem; ++i){
        _sparseMatrix[i] = new char [5];
        _sparseMatrix[i][0] = 1;
        _sparseMatrix[i][1] = 1;
        _sparseMatrix[i][2] = -2;
        _sparseMatrix[i][3] = 1;
        _sparseMatrix[i][4] = 1;
    }
    for(int i=0; i< _numx; ++i){
        _sparseMatrix[i][0] = 0;
        _sparseMatrix[numElem -1 -i][4] = 0;
    }
    for(int i=0; i< _numy; ++i){
        _sparseMatrix[i *_numx][1] = 0;
        _sparseMatrix[(i+1) *_numx -1][3] = 0;
    }
    
    _numBounds =0;
    _indexBounds =0;
}
//===========================================================
//===========================================================
void TemperatureControl::init()
{
    _countCalc =0;
    _ambTemp = 0;
    for(int i=0; i< _numx*_numy; ++i){
        //_temperature[i] =0;
        _heatSource[i] = 0;
        _htransfer[i] = 0;
    }
    
    delete [] _indexBounds;
    _numBounds = 2 * (_numx +_numy -2);
    _indexBounds = new int [_numBounds];
    if(_numBounds == 0){ _indexBounds[0] = -1; }
    for(int i=0, count=0; i< _numx *_numy; ++i){
        if((i -_numx) <0){
            _indexBounds[count] = i;
            ++count;
        }else
        if((i +_numx) >= _numx *_numy){
            _indexBounds[count] = i;
            ++count;
        }else
        if((i %_numx) ==0){
            _indexBounds[count] = i;
            ++count;
        }else
        if((i %_numx +1) ==_numx){
            _indexBounds[count] = i;
            ++count;
        }
    }
    
    for(int i=_numx; i< 2*_numx; ++i){
        _heatSource[i] = 0;
    }
}
//===========================================================
//===========================================================
void TemperatureControl::setBC(Variable& state)
{
    
    for(int i=0; i< _numBounds; ++i){
        _state[_indexBounds[i]] =0;
    }
    for(int i=0; i< _numx; ++i){
        _state[i] =10;
    }
}
//===========================================================
//===========================================================
void TemperatureControl::calcState(int numstep, Variable& state, Variable& input)
{
    int elapsedTime = GetTickCount();
    
    const double OMEGA   =1.6;
    const double EPSILON =1e-4;
    
    double hcap = _dt /_hcap /2;
    double hconX = _hconX *_dt /_hcap /_dx /_dx /2;
    double hconY = _hconY *_dt /_hcap /_dy /_dy /2;
    
    int numElem = _numx *_numy;
    
    double rhs[numElem];
    double emax;
    
    for(int k=0; k< numstep; ++k){
        setBC();
        for(int i=0; i< numElem; ++i){
            rhs[i] =
                (_heatSource[i] + _htransfer[i] *_ambTemp) *2 *hcap
                + _sparseMatrix[i][0] *hconY *_state[i-_numx]
                + _sparseMatrix[i][1] *hconX *_state[i-1]
                + (_sparseMatrix[i][2] *(hconX + hconY)
                    - _htransfer[i] *hcap + 1) *_state[i]
                + _sparseMatrix[i][3] *hconX *_state[i+1]
                + _sparseMatrix[i][4] *hconY *_state[i+_numx];
        }
        do{
            emax =0;
            for(int i=0, count=0; i< numElem; ++i){
                if(i >= _indexBounds[count]){
                    do{
                        ++count;
                    }while(i >= _indexBounds[count]);
                    continue;
                }
                double temp =
                    rhs[i]
                    + _sparseMatrix[i][0] *hconY *_state[i-_numx]
                    + _sparseMatrix[i][1] *hconX *_state[i-1]
                    + _sparseMatrix[i][3] *hconX *_state[i+1]
                    + _sparseMatrix[i][4] *hconY *_state[i+_numx];
                temp /= (
                    _sparseMatrix[i][2] *-(hconX + hconY)
                    +_htransfer[i] *hcap
                    +1);
                temp -= _state[i];
                _state[i] += OMEGA *temp;
                emax = Math::max(emax, temp);
            }
        }while(emax > EPSILON);
    }
    _countCalc += numstep;
    
    //cout.setf(ios::scientific, ios::floatfield);
    cout.precision(3);
    cout << "the time is " << _countCalc *_dt << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            cout << _state[i *_numx + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
//===========================================================
//===========================================================
void TemperatureControl::show(ostream& ofs)
{
    ofs << "TemperatureControl Constructed" << endl;
    
    ofs << "the sparse matrix is " << _countCalc *_dt << endl;
    for(int i=0; i< _numx*_numy; ++i){
        for(int j=0; j< 5; ++j){
            ofs << (int)_sparseMatrix[i][j] << " ";
        }
        ofs << endl;
        if(i%_numx+1==_numx){ ofs << endl; }
    }
    
    ofs << "_indexBounds[]" << endl;
    for(int i=0; i< _numBounds; ++i){
        ofs << _indexBounds[i] << " ";
    }
    ofs << endl;
    ofs << endl;
    
    ofs << "the temperatures are" << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _temperature[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
}
void TemperatureControl::showTemp(ostream& ofs)
{
    ofs << "the time is " << _countCalc *_dt << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _temperature[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
}
//===========================================================
//===========================================================
int main()
{
    ofstream ofs;
    ofs.open("windows/research/laboratory.txt");
    TemperatureControl test;
    test.putForward(10000);
    
    //ofs << "fdh";
    
    
    return 0;
}
*/
//===========================================================
//===========================================================


#endif //ifndef _base_math_analysis_calculus_Diffusion_cpp

