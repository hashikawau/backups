

#ifndef __Windows_lang_String_cpp
#define __Windows_lang_String_cpp


//===========================================================
//===========================================================
#include "String.h"
#include "Object.h"
#include "Exception.h"
#include <iostream>
using namespace std;
//===========================================================
//===========================================================
static unsigned int strlenc(const char* const str);
static unsigned int strlenw(const char* const str);
static char* strcpy(char* s1, const char* const s2);
static char* strcpy(char* s1, const char* const s2);
static char* strcat(char* s1, const char* const s2);
static char* strcat(char* s1, const char* const s2);
//===========================================================
//===========================================================
String::String()
{
    _str = new char[1];
    _str[0] = L'\0';
}
String::String(bool b)
{
    _str = new char[6];
    if(b){
        ::strcpy(_str, L"true");
    }else{
        ::strcpy(_str, L"false");
    }
}
String::String(int ch)
{
    char str[64];
    wsprintfW(str, L"%d", ch);
    _str = new char[::strlenw(str) +1];
    ::strcpy(_str, str);
}
String::String(double ch)
{
    char str[64];
    sprintf(str, "%lf", ch);
    _str = new char[::strlenc(str) +1];
    ::strcpy(_str, str);
}
String::String(char ch)
{
    _str = new char[2];
    _str[0] = static_cast<char>(0x00FF & ch);
    _str[1] = L'\0';
}
String::String(char ch)
{
    _str = new char[2];
    _str[0] = ch;
    _str[1] = L'\0';
}
String::String(const char* const str)
{
    if(!str){
        throw NullPointerException();
    }
    _str = new char[::strlen(str) +1];
    ::strcpy(_str, str);
}
String::String(const char* const str)
{
    if(!str){
        throw NullPointerException();
    }
    _str = new char[::strlenw(str) +1];
    ::strcpy(_str, str);
}
String::String(const char* const str, int offset, int count)
{
    if(!str){
        throw NullPointerException();
    }
    if(offset<0 || count<0 || offset+count>::strlen(str)){
        throw IndexOutOfBoundsException();
    }
    
    _str = new char[count +1];
    for(int i=0; i< count; ++i){
        _str[i] = static_cast<char>(str[i +offset]);
    }
    _str[count] = L'\0';
}
String::String(const char* const str, int offset, int count)
{
    if(!str){
        throw NullPointerException();
    }
    if(offset<0 || count<0 || offset+count>::strlenw(str)){
        throw IndexOutOfBoundsException();
    }
    
    _str = new char[count +1];
    for(int i=0; i< count; ++i){
        _str[i] = str[i +offset];
    }
    _str[count] = L'\0';
}
String::String(const String& string)
{
    if(!&string){
        throw NullPointerException();
    }
    
    _str = new char[string.length() +1];
    ::strcpy(_str, string._str);
}
String::~String()
{
    delete [] _str;
    _str =0;
}
//===========================================================
//===========================================================
Object* String::clone()
{
    return new String(*this);
}
void String::finalize(){}
//===========================================================
//===========================================================
String String::operator+(const String& string) const
{
    if(!&string){
        throw NullPointerException();
    }
    
    char s1[length() + string.length() +1];
    return String(::strcat(::strcpy(s1, _str), string._str));
}
//===========================================================
//===========================================================
String& String::operator=(const String& string)
{
    if(!&string){
        throw NullPointerException();
    }
    
    delete [] _str;
    _str = new char[string.length() +1];
    ::strcpy(_str, string._str);
    return *this;
}
//===========================================================
//===========================================================
String& String::operator+=(const String& string)
{
    if(!&string){
        throw NullPointerException();
    }
    
    char *str = new char[length() +string.length() +1];
    ::strcpy(str, _str);
    ::strcat(str, string._str);
    delete [] _str;
    _str = str;
    
    return *this;
}
//===========================================================
//===========================================================
char& String::operator[](const int index)
{
    if(index<0 || index>=length()){
        throw IndexOutOfBoundsException();
    }
    return _str[index];
}
char String::operator[](const int index) const
{
    if(index<0 || index>=length()){
        throw IndexOutOfBoundsException();
    }
    return _str[index];
}
//===========================================================
//===========================================================
const char* String::toCharArray() const
{
    return _str;
}
//===========================================================
//===========================================================
int String::length() const
{
    return ::strlenw(_str);
}
//===========================================================
//===========================================================

//===========================================================
//===========================================================
static unsigned int strlenc(const char* const str)
{
    char* ch = const_cast<char*>(str);
    int count = 0;
    while(*ch != '\0'){
        ++count;
        ++ch;
    }
    return count;
}
static unsigned int strlenw(const char* const str)
{
    char* ch = const_cast<char*>(str);
    int count = 0;
    while(*ch != L'\0'){
        ++count;
        ++ch;
    }
    return count;
}
static char* strcpy(char* s1, const char* const s2)
{
    char* ch1 = s1;
    char* ch2 = const_cast<char*>(s2);
    while(*ch2 != '\0'){
        *ch1 = static_cast<char>(*ch2);
        ++ch1;
        ++ch2;
    }
    *ch1 = L'\0';
    return s1;
}
static char* strcpy(char* s1, const char* const s2)
{
    char* ch1 = s1;
    char* ch2 = const_cast<char*>(s2);
    while(*ch2 != L'\0'){
        *ch1 = *ch2;
        ++ch1;
        ++ch2;
    }
    *ch1 = L'\0';
    return s1;
}
static char* strcat(char* s1, const char* const s2)
{
    char* ch1 = s1;
    char* ch2 = const_cast<char*>(s2);
    while(*ch1 != L'\0'){
        ++ch1;
    }
    while(*ch2 != '\0'){
        *ch1 = static_cast<char>(*ch2);
        ++ch1;
        ++ch2;
    }
    *ch1 = L'\0';
    return s1;
}
static char* strcat(char* s1, const char* const s2)
{
    char* ch1 = s1;
    char* ch2 = const_cast<char*>(s2);
    while(*ch1 != L'\0'){
        ++ch1;
    }    
    while(*ch2 != L'\0'){
        *ch1 = *ch2;
        ++ch1;
        ++ch2;
    }
    *ch1 = L'\0';
    return s1;
}
//===========================================================
//===========================================================
ostream& operator<<(ostream& stream, const String& string)
{
    char str[string.length() +1];
    char* ch1 = str;
    char* ch2 = const_cast<char*>(string.toCharArray());
    
    while(*ch2 != '\0'){
        *ch1 = static_cast<char>(*ch2);
        ++ch1;
        ++ch2;
    }
    *ch1 = '\0';
    
    stream << str;
    return stream;
}
//===========================================================
//===========================================================


#endif //ifndef __Windows_lang_String_cpp

