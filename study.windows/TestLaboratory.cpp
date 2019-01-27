
#include "windows\awt\Frame.h"
#include "windows\awt\Canvas.h"

#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <windows.h>
//#include <math.h>

#include "windows\research\Laboratory.h"
#include "windows\lang\Math.h"
#include "windows\lang\StringBuffer.h"
#include "windows\_lang.h"



//===========================================================
//===========================================================
class ContourFigure: public Canvas
{
private:
    //int _width;
    //int _height;
    int _numx;
    int _numy;
    double* _data;
    static const int _COLORS[];
    
public:
    ContourFigure(): _data(0)
    {
        //_width  =300;
        //_height =300;
        //setSize(_width, _height);
        //setVisible(true);
        
        _numx =0;
        _numy =0;
        //_data =0;
    }
    void set(int numx, int numy, double data[])
    {
        _numx =numx;
        _numy =numy;
        _data = data;
    }
    virtual void paint(Graphics& g)
    {
        if(!_data){ return; }
        int width  =5;// /num;
        int height =5;//_height /num;
        double max =-1e300;
        double min =1e300;
        for(int i=0; i< _numx *_numy; ++i){
            max = _data[i] > max?
                _data[i]:
                max;
            min = _data[i] < min?
                _data[i]:
                min;
        }
        double unit =8 /(max -min);
        
        for(int i=0; i< _numy; ++i){
            for(int j=0; j< _numx; ++j){
                int index = static_cast<int>(unit *_data[_numx *i +j]);
                g.setColor(Color(_COLORS[index]));
                g.fillRect(width *j, height *i, width, height);
            }
        }
        
        for(int i=0; i< 9; ++i){
            int index = static_cast<int>(unit *i);
            g.setColor(Color(_COLORS[i]));
            g.fillRect(300, 20 *i, 20, 20);
            g.drawString(String(static_cast<double>(1 /unit *i +min)), 330, 20 *i);
        }
        
    }
};
static const int ContourFigure::_COLORS[] = {
    0xFF0000,
    //0xFF3F00,
    0xFF7F00,
    0xFFFF00,
    
    0x7FFF00,
    //0x3FFF00,
    0x00FF00,
    //0x00FF3F,
    0x00FF7F,
    
    0x00FFFF,
    0x007FFF,
    //0x003FFF,
    0x0000FF
};

//===========================================================
//===========================================================
class TemperatureControl: public Laboratory, public Frame, public Thread
{
protected:
    double _hcap;
    double _hconX;
    double _hconY;
    double _hconZ;
    double _tambient;
    
    double _dx;
    double _dy;
    double _dz;
    int _numx;
    int _numy;
    int _numz;
    int _numBounds;
    int* _indexBounds;
    char** _sparseMatrix;
    
    double* _hsource;
    double* _htransfer;
    
    ContourFigure* _cf;
    
public:
    TemperatureControl();
    TemperatureControl(const TemperatureControl&);
    TemperatureControl& operator=(const TemperatureControl&);
    virtual ~TemperatureControl();
    
    void createModel();
    void generateMesh();
    void setIC();
    void setBC();
    
    virtual void next();
    virtual void determineInput();
    virtual const String print();
    
    virtual void run()
    {
        while(1){
            calculate(1);
            _cf->set(_numx, _numy, _state);
            repaint();
//cout << _numx << "  " << _numy << "  " << _state[13] << endl;
            //_cf->repaint();
            sleep(100);
        }
    }
    /*
    virtual void paint(Graphics& g)
    {
        g.setColor(Color(0x00));
        g.drawLine(0, 0, _elapsedTime /_dt, _elapsedTime /_dt);
    }
    */
    
    void show(ostream& ofs);
    void showTemp(ostream& ofs);
};
//===========================================================
//===========================================================
TemperatureControl::TemperatureControl(): Frame(String("TestLaboratory"))
{
    _hcap =1;
    _hconX =1;
    _hconY =1;
    _hconZ =1;
    _tambient =0;
    
    _dx =1;
    _dy =1;
    _dz =1;
    _numx =0;
    _numy =0;
    _numz =0;
    _numBounds =0;
    _indexBounds =0;
    _sparseMatrix =0;
    
    _hsource =0;
    _htransfer =0;
    
    createModel();
    generateMesh();
    setIC();
    setBC();
    
    setSize(640, 640);
    setVisible(true);
    _cf = new ContourFigure();
    _cf->setSize(500, 300);
    _cf->setVisible(true);
    add(*_cf);
    
}
TemperatureControl::~TemperatureControl()
{
    for(int i=0; i< _numx *_numy; ++i){
        delete [] _sparseMatrix[i];
    }
    delete [] _sparseMatrix;
    delete [] _hsource;
    delete [] _htransfer;
    delete [] _indexBounds;
}
//===========================================================
//===========================================================
void TemperatureControl::createModel()
{
    _hcap =1;
    _hconX =1;
    _hconY =1;
    _hconZ =1;
    _tambient =0;
}
//===========================================================
//===========================================================
void TemperatureControl::generateMesh()
{
    _dt =0.025;
    _dx =1;
    _dy =1;
    _dz =1;
    _numx =10;
    _numy =8;
    _numz =1;
    int numElem = _numx *_numy;
    
    delete [] _indexBounds;
    _numBounds = 2 * (_numx +_numy -2);
    _indexBounds = new int [_numBounds];
    if(_numBounds == 0){ _indexBounds[0] = -1; }
    for(int i=0, count=0; i< numElem; ++i){
        if((i -_numx) <0){
            _indexBounds[count] = i;
            ++count;
        }else
        if((i +_numx) >= numElem){
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
    
    if(_sparseMatrix){
        for(int i=0; i< numElem; ++i){
            delete [] _sparseMatrix[i];
        }
        delete [] _sparseMatrix;
    }
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
    
    delete [] _hsource;
    delete [] _htransfer;
    _hsource = new double [numElem];
    _htransfer = new double [numElem];
    
    delete [] _state;
    delete [] _input;
    _state = new double [numElem];
    _input = new double [4];
}
//===========================================================
//===========================================================
void TemperatureControl::setIC()
{
    _elapsedTime =0;
    for(int i=0; i< _numx*_numy; ++i){
        _state[i] =0;
        _hsource[i] = 0;
        _htransfer[i] = 0;
    }
    
    for(int i=_numx; i< 2*_numx; ++i){
        _hsource[i] = 0;
    }
}
//===========================================================
//===========================================================
void TemperatureControl::setBC()
{
    /*
    int lastline = (_numy -1) * _numx;
    double tempx = _hconX /_dx /4;
    double tempy = _hconY /_dy /4;
    for(int i=0; i< _numx; ++i){
        _temperature[i] =
            (_temperature[i +_numx] *tempy + _tambient)
            / (tempy + 1);
        _temperature[i +lastline] =
            (_temperature[i +lastline -_numx] *tempy + _tambient)
            / (tempy + 1);
    }
    for(int i=0; i< _numy; ++i){
        _temperature[i *_numx] =
            (_temperature[i *_numx + 1] *tempx + _tambient)
            / (tempx + 1);
        _temperature[(i+1) *_numx - 1] =
            (_temperature[(i+1) *_numx - 2] *tempx + _tambient)
            / (tempx + 1);
    }
    */
    
    for(int i=0; i< _numBounds; ++i){
        _state[_indexBounds[i]] =1;
    }
    for(int i=0; i< _numx; ++i){
        _state[i] =10;
    }
}
//===========================================================
//===========================================================
void TemperatureControl::next()
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
    
    //for(int k=0; k< numstep; ++k){
    setBC();
    rhs[0] =
        (_hsource[0] + _htransfer[0] *_tambient) *2 *hcap
        //+ _sparseMatrix[i][0] *hconY *_state[i-_numx]
        //+ _sparseMatrix[i][1] *hconX *_state[i-1]
        + (_sparseMatrix[0][2] *(hconX + hconY)
            - _htransfer[0] *hcap + 1) *_state[0]
        + _sparseMatrix[0][3] *hconX *_state[0+1]
        + _sparseMatrix[0][4] *hconY *_state[0+_numx];
    rhs[numElem -1] =
        (_hsource[numElem -1] + _htransfer[numElem -1] *_tambient) *2 *hcap
        + _sparseMatrix[numElem -1][0] *hconY *_state[numElem -1-_numx]
        + _sparseMatrix[numElem -1][1] *hconX *_state[numElem -1-1]
        + (_sparseMatrix[numElem -1][2] *(hconX + hconY)
            - _htransfer[numElem -1] *hcap + 1) *_state[numElem -1]
        ;//+ _sparseMatrix[i][3] *hconX *_state[i+1]
        //+ _sparseMatrix[i][4] *hconY *_state[i+_numx];
    for(int i=1; i< _numx; ++i){
        rhs[i] =
            (_hsource[i] + _htransfer[i] *_tambient) *2 *hcap
            //+ _sparseMatrix[i][0] *hconY *_state[i-_numx]
            + _sparseMatrix[i][1] *hconX *_state[i-1]
            + (_sparseMatrix[i][2] *(hconX + hconY)
                - _htransfer[i] *hcap + 1) *_state[i]
            + _sparseMatrix[i][3] *hconX *_state[i+1]
            + _sparseMatrix[i][4] *hconY *_state[i+_numx];
    }
    for(int i=_numx; i< numElem -_numx; ++i){
        rhs[i] =
            (_hsource[i] + _htransfer[i] *_tambient) *2 *hcap
            + _sparseMatrix[i][0] *hconY *_state[i-_numx]
            + _sparseMatrix[i][1] *hconX *_state[i-1]
            + (_sparseMatrix[i][2] *(hconX + hconY)
                - _htransfer[i] *hcap + 1) *_state[i]
            + _sparseMatrix[i][3] *hconX *_state[i+1]
            + _sparseMatrix[i][4] *hconY *_state[i+_numx];
    }
    for(int i=numElem -_numx; i< numElem -1; ++i){
        rhs[i] =
            (_hsource[i] + _htransfer[i] *_tambient) *2 *hcap
            + _sparseMatrix[i][0] *hconY *_state[i-_numx]
            + _sparseMatrix[i][1] *hconX *_state[i-1]
            + (_sparseMatrix[i][2] *(hconX + hconY)
                - _htransfer[i] *hcap + 1) *_state[i]
            + _sparseMatrix[i][3] *hconX *_state[i+1]
            ;//+ _sparseMatrix[i][4] *hconY *_state[i+_numx];
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
    //}
    
    _cf->set(_numx, _numy, _state);
    
    /*
    //cout.setf(ios::scientific, ios::floatfield);
    cout.precision(3);
    cout << "the time is " << _elapsedTime << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            cout << _state[i *_numx + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
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
void TemperatureControl::determineInput()
{
    
    int numElem = _numx *_numy;
    for(int i=0; i< numElem; ++i){
        _hsource[i] =0;
    }
    for(int i=0; i< _numy; ++i){
        _hsource[_numx *i +1] =10;
    }
}
//===========================================================
//===========================================================
const String TemperatureControl::print()
{
    StringBuffer string(100);
    
    string = String("the time is ") +String(_elapsedTime) +String("\n");
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            string += String(_state[i *_numx + j]);
            string += String("  ");
        }
        string += String("\n");
    }
    string += String("\n");
    
    string += String("the heat source is\n");
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            string += String(_hsource[i *_numx + j]);
            string += String("  ");
        }
        string += String("\n");
    }
    string += String("\n");
    
    
    return string.substring(0);
}
//===========================================================
//===========================================================
//int main()

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine,
    int nCmdShow)

{
    ofstream ofs;
    //ofs.open("windows/research/laboratory.txt");
    TemperatureControl test;
    //test.show(ofs);
    
    //String string = test.calculate(1000);
    test.start();
    //test.showTemp(ofs);
    //char str[10];
    //str[0] ='\0';
    //wcstombs(str, string.toCharArray(), string.length() +1);
    //cout << str << endl;
    
    
    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
    
    /*
    int num = 100;
    int elapsedTime = GetTickCount();
    
    for(int i=0; i< num; ++i){
        double d1 = 4;
        double d2 = 5;
        double d3 = d1 *d2;
    }
    cout << "with  "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
    
    
    
    elapsedTime = GetTickCount();
    
    double d1 = 4;
    double d2 = 5;
    double d3 = d1 *d2;
    for(int i=0; i< num; ++i){
        d1 = 4;
        d2 = 5;
        d3 = d1 *d2;
    }
    cout << "without  "
        << GetTickCount() - elapsedTime
        << " [ms]"
        << endl;
    */
    
    /*
    //cout << Math::sqrt(-0.0004) << endl;
    cout << Math::toDegrees(Math::PI/2) << endl;
    cout << Math::toRadians(360) << endl;
    cout << log(200) << endl;
    cout << Math::log(200) << endl;
    cout << exp(500) << endl;
    cout << Math::exp(500) << endl;
    cout << exp(500) << endl;
    cout << Math::exp(500) << endl;
    cout << atan(2) << endl;
    cout << Math::atan(2) << endl;
    */
    
    /*
    cout.precision(19);
    
    double d = 0/(1.-1.);
    cout << d << endl;
    
    cout << endl;
    cout << Double::NaN << endl;
    cout << Double::POSITIVE_INFINITY << endl;
    cout << Math::abs(Double::NEGATIVE_INFINITY) << endl;
    double a =1e10;
    double b =1e10;
    cout << "exp is " << Math::exp(a) << endl;
    if(Math::exp(a) >= 1e300/1e-300) cout << " ad;fj" << endl;
    if(-Math::exp(a) <= -1e300/1e-300) cout << " ad;fj" << endl;
    cout << endl;
    
    //cout << Math::sqrt(0.01) << endl;
    a = -8;
    b = 0.3333;
    cout <<       log(a) << endl;
    cout << Math::log(a) << endl;
    cout << endl;
    
    cout <<       exp(a) << endl;
    cout << Math::exp(a) << endl;
    cout << endl;
    
    cout <<       pow(a, b) << endl;
    cout << Math::pow(a, b) << endl;
    cout << endl;
    
    
    cout << 1 /(1/(1.-1.)) << endl;
    */
    
    
    return 0;
}
//===========================================================
//===========================================================
void TemperatureControl::show(ostream& ofs)
{
    ofs << "TemperatureControl Constructed" << endl;
    
    ofs << "the time is " << _elapsedTime << endl;
    
    ofs << "the sparse matrix is " << endl;
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
    
    ofs << "the heat sourses are" << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _hsource[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
    ofs << endl;
    
    ofs << "the heat transfers are" << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _htransfer[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
    ofs << endl;
    
    ofs << "the temperatures are" << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _state[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
}
void TemperatureControl::showTemp(ostream& ofs)
{
    //cout.setf(ios::scientific, ios::floatfield);
    cout.precision(3);
    ofs << "the time is " << _elapsedTime << endl;
    for(int i=0; i< _numy; ++i){
        for(int j=0; j< _numx; ++j){
            ofs << _state[i *_numx + j] << " ";
        }
        ofs << endl;
    }
    ofs << endl;
}

//===========================================================
//===========================================================

