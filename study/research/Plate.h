

#ifndef __Windows_research_Plate
#define __Windows_research_Plate

/*
#include <iostream.h>
#include <fstream.h>
#include <windows.h>
#include "windows\lang\Math.h"
#include "windows\_lang.h"
*/
#include "Laboratory.h"
#include "windows\lang\Math.h"


//===========================================================
//===========================================================
class Plate: public StateEq
{
private:
    double _dt;
    double _dx;
    double _dy;
    //double _dz;
    int _numx;
    int _numy;
    //int _numz;
    int _countCalc;
    double _omega;
    double _epsilon;
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
    Plate();
    virtual ~Plate();
    
    void init();
    void setBC(Variable& state);
    virtual void calcState(
        int numstep,
        Variable& state,
        Variable& input);
    
    void getnumxy(int& numx, int& numy);
    void setheatsource(const double heatsource[]);
    
    void show(ostream& ofs);
    void showTemp(ostream& ofs);
};
//===========================================================
//===========================================================
Plate::Plate()
{
    constructor();
    init();
    //setBC();
}
Plate::~Plate()
{
    for(int i=0; i< _numx *_numy; ++i){
        delete [] _sparseMatrix[i];
    }
    delete [] _sparseMatrix;
    delete [] _htransfer;
    delete [] _heatSource;
    //delete [] _temperature;
    delete [] _indexBounds;
}
//===========================================================
//===========================================================
void Plate::constructor()
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
void Plate::init()
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
void Plate::setBC(Variable& state)
{
    /*
    int lastline = (_numy -1) * _numx;
    double tempx = _hconX /_dx /4;
    double tempy = _hconY /_dy /4;
    for(int i=0; i< _numx; ++i){
        _temperature[i] =
            (_temperature[i +_numx] *tempy + _ambTemp)
            / (tempy + 1);
        _temperature[i +lastline] =
            (_temperature[i +lastline -_numx] *tempy + _ambTemp)
            / (tempy + 1);
    }
    for(int i=0; i< _numy; ++i){
        _temperature[i *_numx] =
            (_temperature[i *_numx + 1] *tempx + _ambTemp)
            / (tempx + 1);
        _temperature[(i+1) *_numx - 1] =
            (_temperature[(i+1) *_numx - 2] *tempx + _ambTemp)
            / (tempx + 1);
    }
    */
    
    for(int i=0; i< _numBounds; ++i){
        state.array()[_indexBounds[i]] =0;
    }
    for(int i=0; i< _numx; ++i){
        state.array()[i] =10;
    }
}
//===========================================================
//===========================================================
void Plate::calcState(int numstep, Variable& state, Variable& input)
{
    int elapsedTime = GetTickCount();
    
    double hcap = _dt /_hcap /2;
    double hconX = _hconX *_dt /_hcap /_dx /_dx /2;
    double hconY = _hconY *_dt /_hcap /_dy /_dy /2;
    
    int numElem = _numx *_numy;
    if(state.length() != numElem){ state.setLength(numElem); }
    
    double rhs[numElem];
    double emax;
    
    for(int k=0; k< numstep; ++k){
        setBC(state);
        for(int i=0; i< numElem; ++i){
            rhs[i] =
                (_heatSource[i] + _htransfer[i] *_ambTemp) *2 *hcap
                + _sparseMatrix[i][0] *hconY *state.array()[i-_numx]
                + _sparseMatrix[i][1] *hconX *state.array()[i-1]
                + (_sparseMatrix[i][2] *(hconX + hconY)
                    - _htransfer[i] *hcap + 1) *state.array()[i]
                + _sparseMatrix[i][3] *hconX *state.array()[i+1]
                + _sparseMatrix[i][4] *hconY *state.array()[i+_numx];
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
                    + _sparseMatrix[i][0] *hconY *state.array()[i-_numx]
                    + _sparseMatrix[i][1] *hconX *state.array()[i-1]
                    + _sparseMatrix[i][3] *hconX *state.array()[i+1]
                    + _sparseMatrix[i][4] *hconY *state.array()[i+_numx];
                temp /= (
                    _sparseMatrix[i][2] *-(hconX + hconY)
                    +_htransfer[i] *hcap
                    +1);
                temp -= state.array()[i];
                state.array()[i] += _omega *temp;
                emax = Math::max(emax, temp);
            }
        }while(emax > _epsilon);
    }
    _countCalc += numstep;
    
    //cout.setf(ios::scientific, ios::floatfield);
    cout.precision(3);
    cout << "the time is " << _countCalc *_dt << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            cout << state.array()[i *_numx + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    /*
    cout << "Crank-Nicholson, iteration "
        << numCalc
        << "[times], calculation time "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
    */
}
//===========================================================
//===========================================================
void Plate::getnumxy(int& numx, int& numy)
{
    numx = _numx;
    numy = _numy;
}
void Plate::setheatsource(const double heatsource[])
{
    for(int i=0; i< _numx *_numy; ++i){
        _heatSource[i] = heatsource[i];
    }
}
//===========================================================
//===========================================================
/*
void Plate::show(ostream& ofs)
{
    ofs << "Plate Constructed" << endl;
    
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
void Plate::showTemp(ostream& ofs)
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
*/
//===========================================================
//===========================================================


#endif //ifndef __Windows_research_Plate

