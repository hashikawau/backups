

#ifndef __Windows_lang_Number_cpp
#define __Windows_lang_Number_cpp


//===========================================================
//===========================================================
#include "Number.h"
#include "String.h"
//===========================================================
//===========================================================
Number::Number(){}
Number::~Number(){}
//===========================================================
//===========================================================
const int Integer::MAX_VALUE =0x7FFFFFFF;
const int Integer::MIN_VALUE =0x80000000;
const int Integer::SIZE      =32;
//===========================================================
//===========================================================
Integer::Integer(){}
Integer::~Integer(){}
//===========================================================
//===========================================================
int Integer::parseInt(const String& str)
{
    char c[256];
    int i;
    for(i=0; i< str.length(); ++i)
    {
        c[i] = static_cast<char>(str[i]);
    }
    c[i] = L'\0';
    
    return atoi(c);
}
String Integer::toBinaryString(int i)
{
    int size = 8 *sizeof(i);
    char ch[size +1];
    for(int n=size -1; n>=0 ; --n){
        int m = i %2;
        i /= 2;
        ch[n] =48 +m;
    }
    ch[size] ='\0';
    
    return String(ch);
}
String Integer::toHexString(int i)
{
    int size = 2 *sizeof(i);
    char ch[size +1];
    for(int n=size -1; n>=0 ; --n){
        int m = i %16;
        i /= 16;
        if(m <10){
            ch[n] =48 +m;
        }else{
            ch[n] =48 +7 +m;
        }
    }
    ch[size] ='\0';
    
    return String(ch);
}
//===========================================================
//===========================================================
const double Double::NaN               =0/(1.-1.);
const double Double::POSITIVE_INFINITY =1e300/1e-300;
const double Double::NEGATIVE_INFINITY =-1e300/1e-300;
//===========================================================
//===========================================================
double Double::parseDouble(const String& str)
{
    char c[256];
    int i;
    for(i=0; i< str.length(); ++i)
    {
        c[i] = static_cast<char>(str[i]);
    }
    c[i] = L'\0';
    
    return atof(c);
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Number_cpp

