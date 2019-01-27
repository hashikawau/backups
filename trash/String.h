

#ifndef __Windows_lang_String
#define __Windows_lang_String


//===========================================================
//===========================================================
#include "Object.h"
//===========================================================
//===========================================================
class String: public Object
{
private:
    char* _str;
    
public:
    String();
    explicit String(bool b);
    explicit String(int ch);
    explicit String(double ch);
    String(char ch);
    String(char ch);
    String(const char* const str);
    String(const char* const str);
    String(const char* const str, int offset, int count);
    String(const char* const str, int offset, int count);
    String(const String& string);
    ~String();
    virtual Object* clone();
    virtual void finalize();
    
    String operator+(const String& string) const;
    String& operator=(const String& string);
    String& operator+=(const String& string);
    char& operator[](const int index);
    char operator[](const int index) const;
    int length() const;
    
    const char* toCharArray() const;
};
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_String

