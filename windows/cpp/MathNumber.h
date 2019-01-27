

#ifndef __Windows_cpp_MathNumber
#define __Windows_cpp_MathNumber


#include "windows\cpp\PointerObject.h"
#include "windows\lang\Math.h"
#include "windows\lang\String.h"

#include "windows\util\LinkedList.h"




//===========================================================
//===========================================================
template<class T>
class MemoryViewer
{
private:
    union 
    {
        T _data;
        class Bytes
        {
        public:
            char _byte[sizeof(T)];
        }_bytes;
    }_number;
    String _string;
    
public:
    MemoryViewer(const T number);
    const String get();
};
template<class T>
MemoryViewer<T>::MemoryViewer(const T number)
{
    _number._data = number;
    
    char string[256];
    char* c = string;
    for(int i=sizeof(double) -1; i>= 0; --i){
        int mask = 0x80;
        for(int j=0; j< 8; ++j){
            //_string[i*(8 +1) +j] = _number._bytes._byte[i] & mask?
            *c = _number._bytes._byte[i] & mask?
                '1':
                '0';
            mask >>= 1;
            ++c;
        }
        *c = '\n';
        ++c;
    }
    *c = '\0';
    _string = String(string);
}
template<class T>
const String MemoryViewer<T>::get()
{
    return _string;
}
//===========================================================
//===========================================================
class MathFunctionException: public RuntimeException
{
public:
    MathFunctionException();
    virtual ~MathFunctionException();
};
MathFunctionException::MathFunctionException(){}
MathFunctionException::~MathFunctionException(){}
//===========================================================
//===========================================================
class MathNumber
{
public:
    MathNumber();
    virtual ~MathNumber() =0;
    virtual const String getNumber() const =0;
};
MathNumber::MathNumber(){}
MathNumber::~MathNumber(){}
//===========================================================
//===========================================================


#endif //ifndef __Windows_cpp_MathNumber


