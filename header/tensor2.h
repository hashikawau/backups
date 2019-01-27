#ifndef __TENSOR2
#define __TENSOR2

#include <fstream.h>
#include <math.h>
#include <time.h>
#include <new.h>
#include <typeinfo.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "storage.h"
using namespace std;

const double ACCURACY = 1e-9; // tensor2_calculator.h - iszero()
const int ACCURACY2 = 1e3; // tensor2_calculator.h - sin(), cos(), exp(), etc
const int ACCURACY3 = 1e6; // tensor2_calculator.h - atan();
template<class typeT> class Tensor2;


class tens2
{
public:
    enum spec
    {
        origin    = 0x01,
        reference = 0x02,
        dynamic   = 0x10,
        stable    = 0x20
    };
    
};

template<class typeT> class Tensor2 :public tens2
{
    typeT** pptypeT;
    int numRow;
    int numCol;
    int rank;
    int state;
    
public:
    // tensor2_base.h
    Tensor2( int row=0, int col=0,
             int stateTemp = tens2::origin | tens2::dynamic
           );
    Tensor2( char *c, int row =0, int col =0,
             int stateTemp = tens2::origin | tens2::dynamic
           );
    ~Tensor2();
    void newTensor2( int row, int col );
    void delTensor2();
    Tensor2<typeT>& readTensor2( char *fileName, int row=0, int col=0 );
    Tensor2<typeT>& zeros( int row=0, int col=0 );
    Tensor2<typeT>& ident(int direction =1);
    Tensor2<typeT>& ident( int row, int col );
    Tensor2<typeT>& trans();
    
    //====================
    int& getRow(){ return numRow; }
    int& getCol(){ return numCol; }
    int& getRank(){ return rank; }
    void show();
    
    // tens2_operator.h
    Tensor2<typeT>& operator[]( int row );
    Tensor2<typeT>& operator()( int col );
    typeT&         operator()(  int row, int col );
    Tensor2<typeT>& operator()( int rowBeg, int colBeg,
                                int rowEnd, int colEnd
                              );
                               
    Tensor2<typeT>& operator=( Tensor2<typeT>& tempTensor2 );
    
    template<class typeT1, class typeT2>
    friend Tensor2<typeT1>& operator=( Tensor2<typeT1>& tempTensor21,
                                       Tensor2<typeT2>& tempTensor22
                                     );
    
    Tensor2<typeT>& operator=( typeT tVal );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator=( Tensor2<typeT>& tempTensor2,
                                      typeT2 t2Val
                                    );
                                    
    // tens2_operator1.h
    Tensor2<typeT>& operator+( typeT tVal );
    Tensor2<typeT>& operator+=( typeT tVal );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator+( Tensor2<typeT>&, typeT2 );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator+( typeT2, Tensor2<typeT>& );
    
    Tensor2<typeT>& operator-();
    Tensor2<typeT>& operator-( typeT );
    Tensor2<typeT>& operator-=( typeT );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator-( Tensor2<typeT>& , typeT2 );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator-( typeT2 , Tensor2<typeT>& );
    
    Tensor2<typeT>& operator*( typeT );
    Tensor2<typeT>& operator*=( typeT );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator*=( Tensor2<typeT>& , typeT2 );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator*( Tensor2<typeT>& , typeT2 );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator*( typeT2 , Tensor2<typeT>& );
    
    Tensor2<typeT>& operator/( typeT );
    Tensor2<typeT>& operator/=( typeT );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator/( Tensor2<typeT>& , typeT2 );
    template<class typeT, class typeT2>
    friend Tensor2<typeT>& operator/( typeT2 , Tensor2<typeT>& );
    
    Tensor2<typeT>& operator%( typeT );
    Tensor2<typeT>& operator%=( typeT );
    
    // tens2_operator2.h
    Tensor2<typeT>& operator+( Tensor2<typeT>& );
    Tensor2<typeT>& operator+=( Tensor2<typeT>& );
    Tensor2<typeT>& operator-( Tensor2<typeT>& );
    Tensor2<typeT>& operator-=( Tensor2<typeT>& );
    Tensor2<typeT>& operator*( Tensor2<typeT>& );  // dot product
    Tensor2<typeT>& operator*=( Tensor2<typeT>& );
    Tensor2<typeT>& operator/( Tensor2<typeT>& );  // divide each element
    Tensor2<typeT>& operator/=( Tensor2<typeT>& );
    
    Tensor2<typeT>& operator>( int power );        // each element power
    Tensor2<typeT>& operator>=( int power );
    Tensor2<typeT>& operator>( Tensor2<typeT>& );  // multiple each element
    Tensor2<typeT>& operator>=( Tensor2<typeT>& );
    Tensor2<typeT>& operator^( int power );        
    Tensor2<typeT>& operator^=( int power );
    Tensor2<typeT>& operator&( Tensor2<typeT>& );  //concatnate B under A
    Tensor2<typeT>& operator&=( Tensor2<typeT>& );
    Tensor2<typeT>& operator|( Tensor2<typeT>& );  //concatnate B ritht of A
    Tensor2<typeT>& operator|=( Tensor2<typeT>& );
    
    // tens2_calculator.h
    Tensor2<typeT>& operator~();                   // gause-seidel
    Tensor2<typeT>& operator!();                   // inverse
    template<class typeT>
    friend Tensor2<typeT>& sin( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& cos( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& tan( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& exp( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& log( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& ln( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& asin( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& acos( Tensor2<typeT>& );
    template<class typeT>
    friend Tensor2<typeT>& atan( Tensor2<typeT>& );
    // cosh, sinh, tanh
    
};

class Tensor2Storage
{
    Storage<Tensor2<int>* >    tens2int;
    Storage<Tensor2<double>* > tens2double;
    
public:
    ~Tensor2Storage()
    {
        clear();
    }
    
    int operator=( Tensor2<int>* ptensor2 )
    {
        tens2int = ptensor2;
        
        return 0;
    }
    
    int operator=( Tensor2<double>* ptensor2 )
    {
        tens2double = ptensor2;
        
        return 0;
    }
    
    void clear()
    {
        for( int i=0; i< (int)tens2int; i++ )
        {
            delete tens2int[i];
        }
        
        for( int i=0; i< (int)tens2double; i++ )
        {
            delete tens2double[i];
        }
        
        tens2int.newStorage();
        tens2double.newStorage();
    }
};

static Tensor2Storage storTensor2;

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
template<class typeT>
inline ostream& operator<<( ostream& stream, Tensor2<typeT>& tensor2 )
{
    cout << endl;
    cout << "row "      << tensor2.getRow();
    cout << "  column " << tensor2.getCol();
    cout << "  rank "   << tensor2.getRank()  ;
    cout << endl;
    
    for( int i=0; i< tensor2.getRow(); i++ )
    {
        for( int j=0; j< tensor2.getCol(); j++ )
        {
            cout << tensor2(i, j) << " ";
        }
        cout << endl;
    }
    
    return stream;
}

/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
const int numbuf = 1024;
const int numval = 16;

template<class typeT>
inline void Tensor2<typeT>::show()
{
    char buf[numbuf];
    char valtens[numval];
    
    //=================== origin or reference
    if( state & tens2::origin )
    {
        strcat(buf, "origin\n");
    }
    else
    if( state & tens2::reference )
    {
        strcat(buf, "reference\n");
    }
    
    //================ dynamic or stable
    if( state & tens2::dynamic )
    {
        strcat(buf, "dynamic\n\n");
    }
    else
    if( state & tens2::stable )
    {
        strcat(buf, "stable\n\n");
    }
    
    strcat(buf, "numRow ");
    sprintf(valtens, "%d\n", numRow);
    strcat(buf, valtens);
    
    strcat(buf, "numCol ");
    sprintf(valtens, "%d\n", numCol);
    strcat(buf, valtens);
    
    strcat(buf, "rank ");
    sprintf(valtens, "%d\n\n", rank);
    strcat(buf, valtens);
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            sprintf(valtens, "%d  ", pptypeT[i][j]);
            strcat(buf, valtens);
        }
        strcat(buf, "\n");
    }
    
    MessageBox(NULL,TEXT(buf),TEXT("Message"),MB_OK | MB_ICONINFORMATION);
    
}

template<>
inline void Tensor2<double>::show()
{
    char buf[numbuf];
    char valtens[numval];
    
    //=================== origin or reference
    if( state & tens2::origin )
    {
        strcat(buf, "origin\n");
    }
    else
    if( state & tens2::reference )
    {
        strcat(buf, "reference\n");
    }
    
    //================ dynamic or stable
    if( state & tens2::dynamic )
    {
        strcat(buf, "dynamic\n\n");
    }
    else
    if( state & tens2::stable )
    {
        strcat(buf, "stable\n\n");
    }
    
    strcat(buf, "numRow ");
    sprintf(valtens, "%d\n", numRow);
    strcat(buf, valtens);
    
    strcat(buf, "numCol ");
    sprintf(valtens, "%d\n", numCol);
    strcat(buf, valtens);
    
    strcat(buf, "rank ");
    sprintf(valtens, "%d\n\n", rank);
    strcat(buf, valtens);
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            sprintf(valtens, "%g  ", pptypeT[i][j]);
            strcat(buf, valtens);
        }
        strcat(buf, "\n");
    }
    
    MessageBox(NULL,TEXT(buf),TEXT("Message"),MB_OK | MB_ICONINFORMATION);
    
}

template<>
inline void Tensor2<char>::show()
{
    char buf[numbuf];
    char valtens[numval];
    
    //=================== origin or reference
    if( state & tens2::origin )
    {
        strcat(buf, "origin\n");
    }
    else
    if( state & tens2::reference )
    {
        strcat(buf, "reference\n");
    }
    
    //================ dynamic or stable
    if( state & tens2::dynamic )
    {
        strcat(buf, "dynamic\n\n");
    }
    else
    if( state & tens2::stable )
    {
        strcat(buf, "stable\n\n");
    }
    
    strcat(buf, "numRow ");
    sprintf(valtens, "%d\n", numRow);
    strcat(buf, valtens);
    
    strcat(buf, "numCol ");
    sprintf(valtens, "%d\n", numCol);
    strcat(buf, valtens);
    
    strcat(buf, "rank ");
    sprintf(valtens, "%d\n\n", rank);
    strcat(buf, valtens);
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            sprintf(valtens, "%c  ", pptypeT[i][j]);
            strcat(buf, valtens);
        }
        strcat(buf, "\n");
    }
    
    MessageBox(NULL,TEXT(buf),TEXT("Message"),MB_OK | MB_ICONINFORMATION);
    
}
template<>
inline void Tensor2<char*>::show()
{
    char buf[numbuf];
    char valtens[numval];
    
    //=================== origin or reference
    if( state & tens2::origin )
    {
        strcat(buf, "origin\n");
    }
    else
    if( state & tens2::reference )
    {
        strcat(buf, "reference\n");
    }
    
    //================ dynamic or stable
    if( state & tens2::dynamic )
    {
        strcat(buf, "dynamic\n\n");
    }
    else
    if( state & tens2::stable )
    {
        strcat(buf, "stable\n\n");
    }
    
    strcat(buf, "numRow ");
    sprintf(valtens, "%d\n", numRow);
    strcat(buf, valtens);
    
    strcat(buf, "numCol ");
    sprintf(valtens, "%d\n", numCol);
    strcat(buf, valtens);
    
    strcat(buf, "rank ");
    sprintf(valtens, "%d\n\n", rank);
    strcat(buf, valtens);
    
    for( int i=0; i< numRow; i++ )
    {
        for( int j=0; j< numCol; j++ )
        {
            sprintf(valtens, "%s  ", pptypeT[i][j]);
            strcat(buf, valtens);
        }
        strcat(buf, "\n");
    }
    
    MessageBox(NULL,TEXT(buf),TEXT("Message"),MB_OK | MB_ICONINFORMATION);
    
}

#endif
#include "tensor2_base.h"
#include "tensor2_operator.h"
#include "tensor2_operator1.h"
#include "tensor2_operator2.h"
#include "tensor2_calculator.h"
