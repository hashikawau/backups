

#ifndef __Windows_lang_Exception
#define __Windows_lang_Exception


//===========================================================
//===========================================================
class Exception
{
public:
    Exception();
    virtual ~Exception();
};
//===========================================================
//===========================================================
class RuntimeException: public Exception
{
public:
    RuntimeException();
    virtual ~RuntimeException();
};
//===========================================================
//===========================================================
class IllegalArgumentException: public RuntimeException
{
public:
    IllegalArgumentException();
    virtual ~IllegalArgumentException();
};
//===========================================================
//===========================================================
class IndexOutOfBoundsException: public RuntimeException
{
public:
    IndexOutOfBoundsException();
    virtual ~IndexOutOfBoundsException();
};
//===========================================================
//===========================================================
class ArrayIndexOutOfBoundsException: public IndexOutOfBoundsException
{
public:
    ArrayIndexOutOfBoundsException();
    virtual ~ArrayIndexOutOfBoundsException();
};
//===========================================================
//===========================================================
class NegativeArraySizeException: public RuntimeException
{
public:
    NegativeArraySizeException();
    virtual ~NegativeArraySizeException();
};
//===========================================================
//===========================================================
class NullPointerException: public RuntimeException
{
public:
    NullPointerException();
    virtual ~NullPointerException();
};
//===========================================================
//===========================================================
class StringIndexOutOfBoundsException: public IndexOutOfBoundsException
{
public:
    StringIndexOutOfBoundsException();
    virtual ~StringIndexOutOfBoundsException();
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_Exception

