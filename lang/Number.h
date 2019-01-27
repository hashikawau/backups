

#ifndef __Windows_lang_Number
#define __Windows_lang_Number


//===========================================================
//===========================================================
class String;
//===========================================================
//===========================================================
class Number
{
public:
    Number();
    virtual ~Number() =0;
};
//===========================================================
//===========================================================
class Integer: public Number
{
public:
    static const int MAX_VALUE;
    static const int MIN_VALUE;
    static const int SIZE;
    
public:
    Integer();
    virtual ~Integer();
    static int parseInt(const String& str);
    static String toBinaryString(int i);
    static String toHexString(int i);
};
//===========================================================
//===========================================================
class Double: public Number
{
public:
    static const double NaN;
    static const double POSITIVE_INFINITY;
    static const double NEGATIVE_INFINITY;
    
public:
    static double parseDouble(const String& str);
};
//===========================================================
//===========================================================

#endif //ifndef __Windows_lang_Number

