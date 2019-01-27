

#include <iostream.h>
#include <windows.h>
#include "lang\Math.h"
#include "windows\_lang.h"



//===========================================================
//===========================================================
class FDM
{
private:
public:
    double _dt;
    double _dx;
    double _dy;
    double _dz;
    int _numx;
    int _numy;
    int _numz;
    int _countCalc;
    double _ambTemp;
    double _omega;
    double _epsilon;
    
    double _hcap;
    double _hconX;
    double _hconY;
    double _hconZ;
    
    double* _temperature;
    double* _heatSource;
    double* _htransfer;
    char** _sparseMatrix;
    
    int _numBounds;
    int _numInside;
    int* _indexBounds;
    int* _indexInside;
    
public:
    FDM();
    ~FDM();
    void init();
    void setBC();
    void show();
    void explicitMethod(int numCalc);
    void implicitMethod(int numCalc);
    void cnMethod(int numCalc);
};
//===========================================================
//===========================================================
FDM::FDM()
{
    _dt = 0.025;
    _dx = 1;
    _dy = 1;
    _dz = 1;
    _numx = 6;
    _numy = 10;
    _numz = 1;
    _countCalc = 0;
    _omega = 1.6;
    _epsilon =1e-4;
    
    _hcap = 1;
    _hconX = 1;
    _hconY = 1;
    _hconZ = 1;
    
    int numElem = _numx *_numy;
    _temperature = new double [numElem];
    _heatSource = new double [numElem];
    _htransfer = new double [numElem];
    _indexBounds = 0;
    _indexInside = 0;
    init();
    
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
    
    /*
    cout << "the sparse matrix is " << _countCalc *_dt << endl;
    for(int i=0; i< numElem; ++i){
        for(int j=0; j< 5; ++j){
            cout << _sparseMatrix[i][j] << " ";
        }
        cout << endl;
        if(i%_numx+1==_numx){ cout << endl; }
    }
    cout << endl;
    
    cout << "the temperatures are" << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            cout << _temperature[i *_numx + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
    
}
//===========================================================
//===========================================================
FDM::~FDM()
{
    for(int i=0; i< _numx *_numy; ++i){
        delete [] _sparseMatrix[i];
    }
    delete [] _sparseMatrix;
    delete [] _htransfer;
    delete [] _heatSource;
    delete [] _temperature;
    delete [] _indexBounds;
    delete [] _indexInside;
}
//===========================================================
//===========================================================
void FDM::init()
{
    _countCalc =0;
    _ambTemp = 0;
    for(int i=0; i< _numx*_numy; ++i){
        _temperature[i] =0;
        _heatSource[i] = 0;
        _htransfer[i] = 4;
    }
    
    _numBounds = 0;//2 * (_numx +_numy -2);
    delete [] _indexBounds;
    _indexBounds = new int [_numBounds];
    if(_numBounds == 0){ _indexBounds[0] = -1; }
    for(int i=0, count=0; i< _numx *_numy; ++i){
        if((i -_numx) <0){
            //_indexBounds[count] = i;
            //++count;
        }else
        if((i +_numx) >= _numx *_numy){
            //_indexBounds[count] = i;
            //++count;
        }else
        if((i %_numx) ==0){
            //_indexBounds[count] = i;
            //++count;
        }else
        if((i %_numx +1) ==_numx){
            //_indexBounds[count] = i;
            //++count;
        }
    }
    
    setBC();
    
    for(int i=_numx; i< 2*_numx; ++i){
        _heatSource[i] = 10;
    }
}
//===========================================================
//===========================================================
void FDM::setBC()
{
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
    /*
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
}
//===========================================================
//===========================================================
void FDM::show()
{
    cout << "the time is " << _countCalc *_dt << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            cout << _temperature[i *_numx + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
//===========================================================
//===========================================================
void FDM::explicitMethod(int numCalc)
{
    int elapsedTime = GetTickCount();
    
    double hcap = _dt /_hcap;
    double hconX = _hconX *_dt /_hcap /_dx /_dx;
    double hconY = _hconY *_dt /_hcap /_dy /_dy;
    for(int k=0; k< numCalc; ++k){
        setBC();
        int count;
        for(int i=0, count=0; i< _numx *_numy; ++i){
            if(i >= _indexBounds[count]){
                do{
                    ++count;
                }while(i >= _indexBounds[count]);
                continue;
            }
            _temperature[i] =
                (_heatSource[i] + _htransfer[i] *_ambTemp) *hcap
                + _sparseMatrix[i][0] *hconY *_temperature[i-_numx]
                + _sparseMatrix[i][1] *hconX *_temperature[i-1]
                + (_sparseMatrix[i][2] *(hconX + hconY)
                    - _htransfer[i] *hcap + 1) *_temperature[i]
                + _sparseMatrix[i][3] *hconX *_temperature[i+1]
                + _sparseMatrix[i][4] *hconY *_temperature[i+_numx];
        }
    }
    _countCalc += numCalc;
    
    cout << "explicit, iteration "
        << numCalc
        << "[times], calculation time "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
}
//===========================================================
//===========================================================
void FDM::implicitMethod(int numCalc)
{
    int elapsedTime = GetTickCount();
    
    double hcap = _dt /_hcap;
    double hconX = _hconX *_dt /_hcap /_dx /_dx;
    double hconY = _hconY *_dt /_hcap /_dy /_dy;
    
    int numElem = _numx *_numy;
    double rhs[numElem];
    double emax;
    
    for(int k=0; k< numCalc; ++k){
        setBC();
        for(int i=0; i< numElem; ++i){
            rhs[i] =
                _temperature[i]
                + (_heatSource[i] + _htransfer[i] *_ambTemp) *hcap;
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
                    + _sparseMatrix[i][0] *hconY *_temperature[i-_numx]
                    + _sparseMatrix[i][1] *hconX *_temperature[i-1]
                    + _sparseMatrix[i][3] *hconX *_temperature[i+1]
                    + _sparseMatrix[i][4] *hconY *_temperature[i+_numx];
                temp /= (
                    _sparseMatrix[i][2] *-(hconX + hconY)
                    +_htransfer[i] *hcap
                    +1);
                temp -= _temperature[i];
                _temperature[i] += _omega *temp;
                emax = Math::max(emax, temp);
            }
        }while(emax > _epsilon);
    }
    _countCalc += numCalc;
    
    cout << "implicit, iteration "
        << numCalc
        << "[times], calculation time "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
}
//===========================================================
//===========================================================
void FDM::cnMethod(int numCalc)
{
    int elapsedTime = GetTickCount();
    
    double hcap = _dt /_hcap /2;
    double hconX = _hconX *_dt /_hcap /_dx /_dx /2;
    double hconY = _hconY *_dt /_hcap /_dy /_dy /2;
    
    int numElem = _numx *_numy;
    double rhs[numElem];
    double emax;
    
    for(int k=0; k< numCalc; ++k){
        setBC();
        for(int i=0; i< numElem; ++i){
            rhs[i] =
                (_heatSource[i] + _htransfer[i] *_ambTemp) *2 *hcap
                + _sparseMatrix[i][0] *hconY *_temperature[i-_numx]
                + _sparseMatrix[i][1] *hconX *_temperature[i-1]
                + (_sparseMatrix[i][2] *(hconX + hconY)
                    - _htransfer[i] *hcap + 1) *_temperature[i]
                + _sparseMatrix[i][3] *hconX *_temperature[i+1]
                + _sparseMatrix[i][4] *hconY *_temperature[i+_numx];
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
                    + _sparseMatrix[i][0] *hconY *_temperature[i-_numx]
                    + _sparseMatrix[i][1] *hconX *_temperature[i-1]
                    + _sparseMatrix[i][3] *hconX *_temperature[i+1]
                    + _sparseMatrix[i][4] *hconY *_temperature[i+_numx];
                temp /= (
                    _sparseMatrix[i][2] *-(hconX + hconY)
                    +_htransfer[i] *hcap
                    +1);
                temp -= _temperature[i];
                _temperature[i] += _omega *temp;
                emax = Math::max(emax, temp);
            }
        }while(emax > _epsilon);
    }
    _countCalc += numCalc;
    
    cout << "Crank-Nicholson, iteration "
        << numCalc
        << "[times], calculation time "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
}
//===========================================================
//===========================================================
int main()
{
    FDM fdm;
    
    fdm.init();
    fdm.show();
    for(int i=0; i< 1; ++i){
        //fdm.explicitMethod(2000);
        //fdm.show();
    }
    fdm.init();
    for(int i=0; i< 1; ++i){
        //fdm.implicitMethod(2000);
        //fdm.show();
    }
    fdm.init();
    for(int i=0; i< 10; ++i){
        //fdm.cnMethod(1);
        //fdm.show();
    }
    
    char str[65];
    wcstombs(str, Integer::toBinaryString(-1).toCharArray(), 33);
    cout << str << endl;
    wcstombs(str, Integer::toHexString(-1).toCharArray(), 9);
    cout << str << endl;
    
    
    return 0;
}
//===========================================================
//===========================================================


